//
//  Copyright (c) 2015-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                https://github.com/casm-lang/libcasm-be
//
//  This file is part of libcasm-be.
//
//  libcasm-be is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libcasm-be is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libcasm-be. If not, see <http://www.gnu.org/licenses/>.
//

#include "CasmIRToCselIRPass.h"

using namespace libcasm_be;

char CasmIRToCselIRPass::id = 0;

static libpass::PassRegistration< CasmIRToCselIRPass > PASS(
    "CASM IR to CSEL IR",
    "translates the CASM IR to the CSEL intermeditate representation",
    "ir2el",
    0 );

bool CasmIRToCselIRPass::run( libpass::PassResult& pr )
{
    libcasm_ir::Specification* value
        = (libcasm_ir::Specification*)
              pr.getResult< libcasm_ir::CasmIRDumpPass >();
    assert( value );

    module = 0;

    value->iterate( libcasm_ir::Traversal::PREORDER, this );

    pr.setResult< CasmIRToCselIRPass >( module );
    pr.setResult< libcsel_ir::CselIRDumpPass >( module );

    return true;
}

libcsel_ir::Module* CasmIRToCselIRPass::getModule( void ) const
{
    assert( module );
    return module;
}

#define DUMP_PREFIX                                                            \
    printf( "%-14s: %p, %s", __FUNCTION__, &value, value.getName() )
#define DUMP_POSTFIX printf( " [TODO]\n" );

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::Specification& value )
{
    module = new libcsel_ir::Module( value.getName() );

    module->add( libcasm_rt::UpdateSet::create() );

    module->add( libcasm_rt::Boolean::create() );
    module->add( libcasm_rt::Integer::create() );
    module->add( libcasm_rt::RulePtr::create() );
    module->add( libcasm_rt::Update::create() );

    module->add( libcasm_rt::HashImplementation::create() );

    module->add( libcasm_rt::State::create() );
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::Specification& value )
{
    std::unordered_map< libcasm_ir::Function*, libcsel_ir::Reference* >
        function2linkage;

    // CASM RT KERNEL
    libcsel_ir::Function* kernel = new libcsel_ir::Function( value.getName() );
    assert( kernel );
    module->add( kernel );

    libcsel_ir::SequentialScope* scope = new libcsel_ir::SequentialScope();
    assert( scope );
    kernel->setContext( scope );

    libcsel_ir::Reference* program = 0;

    for( auto function : value.get< libcasm_ir::Function >() )
    {
        assert( function and libcasm_ir::Value::isa< libcasm_ir::Function >(
                                 function ) );
        libcasm_ir::Function* f = (libcasm_ir::Function*)function;
        libcsel_ir::Variable* v = libcasm_rt::FunctionState::create( *f );

        libcsel_ir::Reference* ref = new libcsel_ir::Reference(
            ( (libcsel_ir::Variable*)v )->getIdent(), v->getType(), kernel,
            libcsel_ir::Reference::LINKAGE );
        assert( ref );
        ref->setRef< libcsel_ir::Variable >( v );
        v->setRef< libcsel_ir::Reference >( ref );

        if( v == libcasm_rt::ProgramFunctionState::create() )
        {
            assert( !program && " only one program variable is allowed! " );
            program = ref;
        }

        function2linkage[ f ] = ref;

        libcasm_rt::State::create()->add( v );
    }
    assert( program );

    libcsel_ir::Reference* uset = 0;
    if( module->has< libcsel_ir::Memory >() )
    {
        for( auto mem : module->get< libcsel_ir::Memory >() )
        {
            assert( libcsel_ir::Value::isa< libcsel_ir::Memory >( mem ) );

            libcsel_ir::Reference* ref = new libcsel_ir::Reference( "uset",
                mem->getType(), kernel, libcsel_ir::Reference::LINKAGE );
            assert( ref );
            ref->setRef< libcsel_ir::Memory >( mem );
            mem->setRef< libcsel_ir::Reference >( ref );

            uset = ref;
        }
    }

    libcsel_ir::Reference* ic_ref = new libcsel_ir::Reference( "interconnect",
        libcasm_rt::State::create()->getType(), kernel,
        libcsel_ir::Reference::LINKAGE );
    ic_ref->setRef< libcsel_ir::Interconnect >( libcasm_rt::State::create() );
    libcasm_rt::State::create()->setRef< libcsel_ir::Reference >( ic_ref );

    // TODO: FIXME: this agent->rule->init_rule detection should be created
    // directly in the AST to IR transf.
    //              so that it is a direct property of an Agent!!!
    assert( value.has< libcasm_ir::Agent >() );
    assert( value.get< libcasm_ir::Agent >().size() == 1 );
    libcasm_ir::Value* agent_ptr = value.get< libcasm_ir::Agent >()[ 0 ];
    assert( libcasm_ir::Value::isa< libcasm_ir::Agent >( agent_ptr ) );
    libcasm_ir::Agent* agent = (libcasm_ir::Agent*)agent_ptr;
    libcasm_ir::Rule* init_rule = agent->getInitRuleReference()->getValue();
    libcsel_ir::Value* init_rule_func_val = reference[ init_rule ];
    assert( init_rule_func_val );
    assert(
        libcsel_ir::Value::isa< libcsel_ir::Function >( init_rule_func_val ) );
    libcsel_ir::Function* init_rule_func
        = (libcsel_ir::Function*)init_rule_func_val;

    libcsel_ir::TrivialStatement* prolog
        = new libcsel_ir::TrivialStatement( scope );
    libcsel_ir::Value* pv = new libcsel_ir::ExtractInstruction(
        program, program->getStructure()->get( 0 ) );
    libcsel_ir::IdInstruction* id
        = new libcsel_ir::IdInstruction( init_rule_func );
    assert( id );
    libcsel_ir::Value* lpv = new libcsel_ir::StoreInstruction( id, pv );
    prolog->add( lpv );

    libcsel_ir::Value* pd = new libcsel_ir::ExtractInstruction(
        program, program->getStructure()->get( 1 ) );
    libcsel_ir::BitConstant* c
        = libcsel_ir::BitConstant::create( 1, pd->getType()->getBitsize() );
    assert( c );
    module->add( c );
    libcsel_ir::Value* lpd = new libcsel_ir::StoreInstruction( c, pd );
    prolog->add( lpd );

    libcsel_ir::LoopStatement* loop = new libcsel_ir::LoopStatement( scope );
    pd = new libcsel_ir::ExtractInstruction(
        program, program->getStructure()->get( 1 ) );
    lpd = new libcsel_ir::LoadInstruction( pd );
    c = libcsel_ir::BitConstant::create( 0, pd->getType()->getBitsize() );
    assert( c );
    module->add( c );
    libcsel_ir::Value* check = new libcsel_ir::NeqUnsignedInstruction( lpd, c );
    loop->add( check );

    libcsel_ir::SequentialScope* loop_true = new libcsel_ir::SequentialScope();
    loop->addScope( loop_true );
    libcsel_ir::TrivialStatement* execute
        = new libcsel_ir::TrivialStatement( loop_true );
    pv = new libcsel_ir::ExtractInstruction(
        program, program->getStructure()->get( 0 ) );
    lpv = new libcsel_ir::LoadInstruction( pv );

    // libcsel_ir::CastInstruction* cast = new libcsel_ir::CastInstruction(
    // libcasm_rt::ProgramRuleSignature::create(), lpv );
    // libcsel_ir::CallInstruction* run_rule = new libcsel_ir::CallInstruction(
    // cast
    // );

    libcsel_ir::IdCallInstruction* run_rule = new libcsel_ir::IdCallInstruction(
        libcasm_rt::ProgramRuleSignature::create(), lpv );
    run_rule->add( ic_ref );
    run_rule->add( uset );

    run_rule->setRef< libcsel_ir::Module >( module );

    execute->add( run_rule );

    for( auto function : value.get< libcasm_ir::Function >() )
    {
        assert( function and libcasm_ir::Value::isa< libcasm_ir::Function >(
                                 function ) );
        libcasm_ir::Function* f = (libcasm_ir::Function*)function;
        libcsel_ir::Variable* v = libcasm_rt::FunctionState::create( *f );

        libcsel_ir::BranchStatement* branch
            = new libcsel_ir::BranchStatement( loop_true );

        libcsel_ir::Instruction* v_id = new libcsel_ir::IdInstruction( v );
        libcsel_ir::Instruction* el = new libcsel_ir::ExtractInstruction(
            uset, v_id ); // PPA: HACK!!! should be through hash!!!

        libcsel_ir::Structure* update_type = libcasm_rt::Update::create();
        libcsel_ir::Instruction* ca
            = new libcsel_ir::CastInstruction( update_type, el );
        libcsel_ir::Instruction* u_bra
            = new libcsel_ir::ExtractInstruction( ca, update_type->get( 0 ) );
        libcsel_ir::Instruction* l_bra
            = new libcsel_ir::LoadInstruction( u_bra );
        branch->add( new libcsel_ir::NeqUnsignedInstruction( l_bra, c ) );

        libcsel_ir::SequentialScope* branch_apply
            = new libcsel_ir::SequentialScope();
        branch->addScope( branch_apply );
        libcsel_ir::TrivialStatement* stmt_apply
            = new libcsel_ir::TrivialStatement( branch_apply );

        // PPA: HACK!!! should be through hash!!!
        // libcsel_ir::Instruction* u_el = new libcsel_ir::ExtractInstruction(
        // uset,
        // new libcsel_ir::IdInstruction( v ) );
        // libcsel_ir::Instruction* u_ca = new libcsel_ir::CastInstruction(
        // update_type, u_el );
        // libcsel_ir::Instruction* u_loc = new libcsel_ir::ExtractInstruction(
        // u_ca, update_type->get(1) );
        libcsel_ir::Instruction* u_val
            = new libcsel_ir::ExtractInstruction( ca, update_type->get( 2 ) );
        libcsel_ir::Instruction* u_def
            = new libcsel_ir::ExtractInstruction( ca, update_type->get( 3 ) );

        libcsel_ir::Reference* f_ref = function2linkage[ f ];
        libcsel_ir::Instruction* f_val = new libcsel_ir::ExtractInstruction(
            f_ref, f_ref->getStructure()->get( 0 ) );
        libcsel_ir::Instruction* f_def = new libcsel_ir::ExtractInstruction(
            f_ref, f_ref->getStructure()->get( 1 ) );

        libcsel_ir::Instruction* l_val
            = new libcsel_ir::LoadInstruction( u_val );
        libcsel_ir::Instruction* t_val
            = new libcsel_ir::TruncationInstruction( l_val, f_val->getType() );

        libcsel_ir::Instruction* st_val
            = new libcsel_ir::StoreInstruction( t_val, f_val );
        libcsel_ir::Instruction* st_def
            = new libcsel_ir::StoreInstruction( u_def, f_def );

        stmt_apply->add( st_val );
        stmt_apply->add( st_def );
    }

    // libcsel_ir::TrivialStatement* epilog = new libcsel_ir::TrivialStatement(
    // scope );
    // for( auto var : module->get< libcsel_ir::Variable >() )
    // {
    // 	libcsel_ir::StreamInstruction* output = new
    // libcsel_ir::StreamInstruction(
    // libcsel_ir::StreamInstruction::OUTPUT );
    // 	assert( output );
    // 	output->add( var );
    // 	output->add( &libcsel_ir::StringConstant::LF );
    // 	epilog->add( output );
    // }

    // generation of 'stand-alone' kernel function which is the main function of
    // all target domains!
    libcsel_ir::Function* func = new libcsel_ir::Function( "main" );
    assert( func );
    module->add( func );
    libcsel_ir::SequentialScope* func_scope = new libcsel_ir::SequentialScope();
    assert( func_scope );
    func->setContext( func_scope );
    libcsel_ir::TrivialStatement* stmt
        = new libcsel_ir::TrivialStatement( func_scope );
    stmt->add( new libcsel_ir::CallInstruction( kernel ) );
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::Agent& value )
{
    // PPA: agent generation currently not implemented due to single agent
    // execution behavior!
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::Agent& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::Function& value )
{
    // TODO: FIXME: implement a Memory access if it is not a 0-ary function!
    // libcsel_ir::Memory* mem = new libcsel_ir::Memory( factory(
    // value.getType() ),
    // 1 );

    libcsel_ir::Variable* state = libcasm_rt::FunctionState::create( value );
    module->add( state );

    libcsel_ir::CallableUnit* location
        = libcasm_rt::FunctionLocation::create( value );
    module->add( location );
    reference[&value ] = location;

    // TODO: FIXME: PPA: the following line should be removed in the near future
    //                   after a clean 'self' and Agent implementation!
    if( strcmp( value.getName(), "program" ) == 0 )
    {
        return;
    }

    assert( value.getType()->getID() == libcasm_ir::Type::RELATION );
    libcasm_ir::RelationType* ftype
        = static_cast< libcasm_ir::RelationType* >( value.getType() );

    if( ftype->getArguments().size() != 0 )
    {
        assert( !" unimplemented transformation for n-ary functions!" );
    }

    // printf( "%s:%i: '%s'\n", __FILE__, __LINE__, value.getType()->getName()
    // );
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::Function& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::Rule& value )
{
    const char* name = libstdhl::Allocator::string(
        "casm_rule_" + string( value.getName() ) );

    if( reference.count( &value ) > 0 )
    {
        libcsel_ir::Value* ptr = reference[&value ];
        assert( ptr and strcmp( ptr->getName(), name ) == 0 );
        return;
    }

    libcsel_ir::Function* obj = new libcsel_ir::Function( name );
    assert( obj );
    module->add( obj );

    /*libcsel_ir::Value* refs = */ obj->in(
        "refs", libcasm_rt::State::create()->getType() );
    /*libcsel_ir::Value* uset = */ obj->in(
        "uset", libcasm_rt::UpdateSet::create()->getType() );

    reference[&value ] = obj;
}
void CasmIRToCselIRPass::visit_interlog( libcasm_ir::Rule& value )
{
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::Rule& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::ParallelBlock& value )
{
    libcsel_ir::ParallelScope* scope = new libcsel_ir::ParallelScope();
    assert( scope );

    libcasm_ir::ExecutionSemanticsBlock* parent_scope = value.getScope();
    if( !parent_scope )
    {
        libcasm_ir::Rule* rule = value.getBound();

        libcsel_ir::Function* comp
            = (libcsel_ir::Function*)( reference[ rule ] );
        comp->setContext( scope );
    }
    else
    {
        libcasm_ir::Value* parent = value.getParent();
        assert( parent );
        assert( reference[ parent ] );

        libcsel_ir::Scope* upper_scope
            = static_cast< libcsel_ir::Scope* >( reference[ parent ] );
        upper_scope->add( scope );
        scope->setParent( upper_scope );
    }

    reference[&value ] = scope;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::ParallelBlock& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::SequentialBlock& value )
{
    libcsel_ir::SequentialScope* scope = new libcsel_ir::SequentialScope();
    assert( scope );

    libcasm_ir::ExecutionSemanticsBlock* parent_scope = value.getScope();
    if( !parent_scope )
    {
        libcasm_ir::Rule* rule = value.getBound();

        libcsel_ir::Function* comp
            = (libcsel_ir::Function*)( reference[ rule ] );
        comp->setContext( scope );
    }
    else
    {
        libcasm_ir::Value* parent = value.getParent();
        assert( parent );
        assert( reference[ parent ] );

        libcsel_ir::Scope* upper_scope
            = static_cast< libcsel_ir::Scope* >( reference[ parent ] );
        upper_scope->add( scope );
        scope->setParent( upper_scope );
    }

    reference[&value ] = scope;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::SequentialBlock& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::TrivialStatement& value )
{
    libcasm_ir::ExecutionSemanticsBlock* parent = value.getScope();
    assert( parent );

    libcsel_ir::TrivialStatement* stmt
        = new libcsel_ir::TrivialStatement( reference[ parent ] );
    assert( stmt );

    reference[&value ] = stmt;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::TrivialStatement& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::BranchStatement& value )
{
    libcasm_ir::ExecutionSemanticsBlock* parent = value.getScope();
    assert( parent );

    libcsel_ir::BranchStatement* stmt
        = new libcsel_ir::BranchStatement( reference[ parent ] );
    assert( stmt );

    reference[&value ] = stmt;
}
void CasmIRToCselIRPass::visit_interlog( libcasm_ir::BranchStatement& value )
{
    libcsel_ir::BranchStatement* stmt
        = (libcsel_ir::BranchStatement*)reference[&value ];

    libcsel_ir::Value* last = stmt->getInstructions().back();

    assert( libcsel_ir::Value::isa< libcsel_ir::CallInstruction >( last ) );
    libcsel_ir::CallInstruction* last_call = (libcsel_ir::CallInstruction*)last;

    assert( libcsel_ir::Value::isa< libcsel_ir::CallableUnit >(
        last_call->getValue( 0 ) ) );
    libcsel_ir::CallableUnit* last_func
        = (libcsel_ir::CallableUnit*)( last_call->getValue( 0 ) );
    libcsel_ir::Reference* result
        = (libcsel_ir::Reference*)last_func->getOutParameters()[ 0 ];

    libcsel_ir::Instruction* reg
        = (libcsel_ir::Instruction*)( last_call->getValues().back() );

    assert( strcmp( result->getStructure()->getName(), "Boolean" ) == 0 );

    libcsel_ir::Instruction* rv = new libcsel_ir::ExtractInstruction(
        reg, result->getStructure()->get( 0 ) );
    libcsel_ir::Instruction* rd = new libcsel_ir::ExtractInstruction(
        reg, result->getStructure()->get( 1 ) );

    libcsel_ir::Instruction* lv = new libcsel_ir::LoadInstruction( rv );
    libcsel_ir::Instruction* ld = new libcsel_ir::LoadInstruction( rd );

    libcsel_ir::Instruction* rt
        = new libcsel_ir::EquUnsignedInstruction( lv, ld );

    stmt->add( rt );
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::BranchStatement& value )
{
    libcsel_ir::BranchStatement* stmt
        = (libcsel_ir::BranchStatement*)reference[&value ];

    for( auto b : value.getBlocks() )
    {
        libcsel_ir::Value* scope = reference[ b ];
        assert( scope && libcsel_ir::Value::isa< libcsel_ir::Scope >( scope ) );

        stmt->addScope( (libcsel_ir::Scope*)scope );
    }

    reference[&value ] = 0;
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::LocalInstruction& value )
{
    printf( ">>>>>>>>>>>>>>>>>>>>>>>>> %p\n", &value );

    libcsel_ir::Structure* local_type = libcasm_rt::Type::create(
        static_cast< libcasm_ir::Value& >( value ) );

    libcsel_ir::AllocInstruction* local
        = new libcsel_ir::AllocInstruction( local_type->getType() );
    assert( local );

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)reference[ parent ];
    assert( stmt );
    stmt->add( local );

    reference[&value ] = local;
}

void CasmIRToCselIRPass::visit_epilog( libcasm_ir::LocalInstruction& value )
{
    reference[&value ] = 0;
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::SkipInstruction& value )
{
    assert( !" not implemented !!! " );
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::SkipInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::ForkInstruction& value )
{
    assert( !" not implemented !!! " );
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::ForkInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::MergeInstruction& value )
{
    assert( !" not implemented !!! " );
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::MergeInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::LocationInstruction& value )
{
    assert( value.getValues().size() >= 1 );

    libcasm_ir::Value* src = value.getValue( 0 );
    assert( libcasm_ir::Value::isa< libcasm_ir::Function >( src ) );

    libcsel_ir::Value* location_src = reference[ src ];
    assert( location_src );

    libcsel_ir::CallInstruction* call
        = new libcsel_ir::CallInstruction( location_src );
    assert( call );

    assert( libcsel_ir::Value::isa< libcsel_ir::Intrinsic >( location_src ) );
    libcsel_ir::Intrinsic* location_src_ptr
        = (libcsel_ir::Intrinsic*)location_src;

    assert( location_src_ptr->getOutParameters().size() == 1 );

    libcsel_ir::AllocInstruction* alloc = new libcsel_ir::AllocInstruction(
        location_src_ptr->getOutParameters()[ 0 ]->getType() );
    assert( alloc );
    call->add( alloc );

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)reference[ parent ];
    assert( stmt );
    stmt->add( call );

    reference[&value ] = alloc;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::LocationInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::LookupInstruction& value )
{
    libcsel_ir::CallableUnit* lup
        = libcasm_rt::LookupImplementation::create( value, module );

    assert( value.getValues().size() == 1 );

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)reference[ parent ];
    assert( stmt );

    // TODO: FIXME: PPA: the following code block can be reused and can be
    // provided in a generic way!!!
    libcsel_ir::Value* context = stmt;
    while( not libcsel_ir::Value::isa< libcsel_ir::CallableUnit >( context ) )
    {
        assert( libcsel_ir::Value::isa< libcsel_ir::Block >( context ) );
        context
            = (libcsel_ir::Value*)( (libcsel_ir::Block*)context )->getParent();
    }
    assert( libcsel_ir::Value::isa< libcsel_ir::CallableUnit >( context ) );
    libcsel_ir::CallableUnit* caller = (libcsel_ir::CallableUnit*)context;

    libcasm_ir::Value* src = value.get();
    assert( libcasm_ir::Value::isa< libcasm_ir::LocationInstruction >( src ) );

    libcsel_ir::Value* lookup_src = reference[ src ];
    assert( lookup_src );

    libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( lup );
    assert( call );
    call->add( caller->getInParameters()[ 0 ] );
    call->add( caller->getInParameters()[ 1 ] );
    call->add( lookup_src );

    libcsel_ir::AllocInstruction* alloc = new libcsel_ir::AllocInstruction(
        libcasm_rt::Integer::create()->getType() );
    assert( alloc );
    call->add( alloc );

    stmt->add( call );

    reference[&value ] = alloc;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::LookupInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::UpdateInstruction& value )
{
    libcsel_ir::CallableUnit* upd
        = libcasm_rt::UpdateImplementation::create( value, module );

    assert( value.getValues().size() == 2 );

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)reference[ parent ];
    assert( stmt );

    // TODO: FIXME: PPA: the following code block can be reused and can be
    // provided in a generic way!!!
    libcsel_ir::Value* context = stmt;
    while( not libcsel_ir::Value::isa< libcsel_ir::CallableUnit >( context ) )
    {
        assert( libcsel_ir::Value::isa< libcsel_ir::Block >( context ) );
        context
            = (libcsel_ir::Value*)( (libcsel_ir::Block*)context )->getParent();
    }
    assert( libcsel_ir::Value::isa< libcsel_ir::CallableUnit >( context ) );
    libcsel_ir::CallableUnit* caller = (libcsel_ir::CallableUnit*)context;

    libcasm_ir::Value* src = value.getValue( 0 );
    assert( libcasm_ir::Value::isa< libcasm_ir::LocationInstruction >( src ) );
    libcsel_ir::Value* update_src = reference[ src ];
    assert( update_src );

    libcasm_ir::Value* val = value.getValue( 1 );
    assert( libcasm_ir::Value::isa< libcasm_ir::Instruction >( val )
            or libcasm_ir::Value::isa< libcasm_ir::ConstantValue >( val ) );
    libcsel_ir::Value* update_val = reference[ val ];
    assert( update_val );

    libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( upd );
    assert( call );

    call->add( caller->getInParameters()[ 1 ] );
    call->add( update_src );
    call->add( update_val );

    stmt->add( call );

    reference[&value ] = call;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::UpdateInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::PrintInstruction& value )
{
    static libcsel_ir::StringConstant* undef = 0;
    if( not undef )
    {
        undef = libcsel_ir::StringConstant::create( "undef" );
        module->add( undef );
    }

    libcsel_ir::StreamInstruction* obj = new libcsel_ir::StreamInstruction(
        libcsel_ir::StreamInstruction::OUTPUT );
    assert( obj );

    // for( libcasm_ir::Value* v : value.getValues() )
    // {
    //     libcsel_ir::Value* e = reference[ v ];
    //     libcsel_ir::Structure* s = libcasm_rt::Type::create( *v );

    //     // if( libcasm_ir::Value::isa< libcasm_ir::StringConstant >( v ) )
    //     // {
    //     //     assert(
    //     //         libcsel_ir::Value::isa< libcsel_ir::StructureConstant >( e
    //     ) );
    //     //     libcsel_ir::StructureConstant* c
    //     //         = (libcsel_ir::StructureConstant*)e;

    //     //     assert( libcsel_ir::Value::isa< libcsel_ir::BitConstant >(
    //     //         c->getElements()[ 1 ] ) );
    //     //     libcsel_ir::BitConstant* def
    //     //         = (libcsel_ir::BitConstant*)c->getElements()[ 1 ];
    //     //     if( def->getValue()[ 0 ] == 0 )
    //     //     {
    //     //         e = undef;
    //     //     }
    //     //     else
    //     //     {
    //     //         e = c->getElements()[ 0 ];
    //     //     }
    //     // }
    //     // else
    //     // {
    //     //     assert( !" unsupported/unimplemented print instr argument! "
    //     );
    //     // }

    //     obj->add( e );
    // }
    obj->add( &libcsel_ir::StringConstant::LF );

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)reference[ parent ];
    assert( stmt );

    stmt->add( obj );

    reference[&value ] = obj;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::PrintInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::AddInstruction& value )
{
    libcsel_ir::CallableUnit* obj
        = libcasm_rt::Instruction::create( value, module );
    libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( obj );
    assert( call );

    libcsel_ir::Value* lhs = reference[ value.getLHS() ];
    assert( lhs );
    call->add( lhs );

    libcsel_ir::Value* rhs = reference[ value.getRHS() ];
    assert( rhs );
    call->add( rhs );

    libcsel_ir::AllocInstruction* result = new libcsel_ir::AllocInstruction(
        obj->getOutParameters()[ 0 ]->getType() );
    assert( result );
    call->add( result );
    reference[&value ] = result;

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)reference[ parent ];
    assert( stmt );
    stmt->add( call );
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::AddInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::DivInstruction& value )
{
    libcsel_ir::CallableUnit* obj
        = libcasm_rt::Instruction::create( value, module );
    libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( obj );
    assert( call );

    libcsel_ir::Value* lhs = reference[ value.getLHS() ];
    assert( lhs );
    call->add( lhs );

    libcsel_ir::Value* rhs = reference[ value.getRHS() ];
    assert( rhs );
    call->add( rhs );

    libcsel_ir::AllocInstruction* result = new libcsel_ir::AllocInstruction(
        obj->getOutParameters()[ 0 ]->getType() );
    assert( result );
    call->add( result );
    reference[&value ] = result;

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)reference[ parent ];
    assert( stmt );
    stmt->add( call );
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::DivInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::AndInstruction& value )
{
    DUMP_PREFIX;
    DUMP_POSTFIX;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::AndInstruction& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::EquInstruction& value )
{
    libcsel_ir::CallableUnit* obj
        = libcasm_rt::Instruction::create( value, module );
    libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( obj );
    assert( call );

    libcsel_ir::Value* lhs = reference[ value.getLHS() ];
    assert( lhs );
    call->add( lhs );

    libcsel_ir::Value* rhs = reference[ value.getRHS() ];
    assert( rhs );
    call->add( rhs );

    libcsel_ir::AllocInstruction* result = new libcsel_ir::AllocInstruction(
        obj->getOutParameters()[ 0 ]->getType() );
    assert( result );
    call->add( result );
    reference[&value ] = result;

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)reference[ parent ];
    assert( stmt );
    stmt->add( call );
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::EquInstruction& value )
{
}

// CONSTANTS

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::IntegerConstant& value )
{
    libcsel_ir::Value* val = libcsel_ir::BitConstant::create( value.getValue(),
        libcasm_rt::Integer::create()->get( 0 )->getType()->getBitsize() );
    libcsel_ir::Value* def = libcsel_ir::BitConstant::create( value.isDefined(),
        libcasm_rt::Integer::create()->get( 1 )->getType()->getBitsize() );
    assert( val );
    assert( def );

    libcsel_ir::Value* const_int = libcsel_ir::StructureConstant::create(
        libcasm_rt::Integer::create(), { val, def } );

    module->add( const_int );
    reference[&value ] = const_int;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::IntegerConstant& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::StringConstant& value )
{
    printf( "%s:%i: '%s'\n", __FILE__, __LINE__, value.getValue() );

    libcsel_ir::Structure* type = libcasm_rt::String::create( value );

    module->add( type );

    libcsel_ir::Value* val
        = libcsel_ir::StringConstant::create( value.getValue() );
    libcsel_ir::Value* def = libcsel_ir::BitConstant::create(
        value.isDefined(), type->get( 1 )->getType()->getBitsize() );
    assert( val );
    assert( def );

    libcsel_ir::Value* const_string
        = libcsel_ir::StructureConstant::create( type, { val, def } );

    module->add( const_string );
    reference[&value ] = const_string;
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::StringConstant& value )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::RuleReferenceConstant& value )
{
    libcsel_ir::Value* def = value.isDefined()
                                 ? &libcsel_ir::BitConstant::TRUE
                                 : &libcsel_ir::BitConstant::FALSE;
    libcsel_ir::Value* val = &libcsel_ir::BitConstant::NIL;

    libcasm_ir::Value* rule = value.getValue();
    if( rule )
    {
        assert( libcasm_ir::Value::isa< libcasm_ir::Rule >( rule ) );
        if( reference.count( rule ) == 0 )
        {
            // pre-visit only for CallableUnit pointer creation!
            visit_prolog( *( (libcasm_ir::Rule*)rule ) );
        }
        assert( reference.count( rule ) != 0 );
        libcsel_ir::Value* c = reference[ rule ];

        assert( libcsel_ir::Value::isa< libcsel_ir::CallableUnit >( c ) );
        libcsel_ir::CallableUnit* callable = (libcsel_ir::CallableUnit*)c;
        val = callable->getAllocationID();
    }

    assert( val );
    assert( def );

    libcsel_ir::Value* const_rule = libcsel_ir::StructureConstant::create(
        libcasm_rt::RulePtr::create(), { val, def } );

    module->add( const_rule );
    reference[&value ] = const_rule;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::RuleReferenceConstant& value )
{
}

void CasmIRToCselIRPass::visit_prolog( libcasm_ir::AgentConstant& value )
{
    // TODO: FIXME: PPA: this is obsolete for now!!!
}
void CasmIRToCselIRPass::visit_epilog( libcasm_ir::AgentConstant& value )
{
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
