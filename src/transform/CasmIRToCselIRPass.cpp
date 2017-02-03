//
//  Copyright (c) 2015-2017 CASM Organization
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

#include "libcasm-rt.h"

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
        = (libcasm_ir::Specification*)pr.result< libcasm_ir::CasmIRDumpPass >();
    assert( value );

    m_module = 0;

    value->iterate( libcasm_ir::Traversal::PREORDER, this );

    pr.setResult< CasmIRToCselIRPass >( m_module );
    pr.setResult< libcsel_ir::CselIRDumpPass >( m_module );

    return true;
}

libcsel_ir::Module* CasmIRToCselIRPass::module( void ) const
{
    assert( m_module );
    return m_module;
}

#define DUMP_PREFIX                                                            \
    printf( "%-14s: %p, %s", __FUNCTION__, &value, value.name() )
#define DUMP_POSTFIX printf( " [TODO]\n" );

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::Specification& value, libcasm_ir::Context& )
{
    m_module = new libcsel_ir::Module( value.name() );

    assert( !" PPA: TODO!!! " );

    // m_module->add( libcasm_rt::UpdateSet::create() );

    // m_module->add( libcasm_rt::Boolean::create() );
    // m_module->add( libcasm_rt::Integer::create() );
    // m_module->add( libcasm_rt::RulePtr::create() );
    // m_module->add( libcasm_rt::Update::create() );

    // m_module->add( libcasm_rt::HashImplementation::create() );

    // m_module->add( libcasm_rt::State::create() );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::Specification& value, libcasm_ir::Context& )
{
    std::unordered_map< libcasm_ir::Function*, libcsel_ir::Reference* >
        function2linkage;

    assert( !" PPA: TODO!!! " );

    // // CASM RT KERNEL
    // libcsel_ir::Type* kernel_ty
    //     = libcsel_ir::Type::Relation( libcsel_ir::Type::Bit( 1 ), {} );

    // libcsel_ir::Function* kernel
    //     = new libcsel_ir::Function( value.name(), kernel_ty );
    // assert( kernel );
    // m_module->add( kernel );

    // libcsel_ir::SequentialScope* scope = new libcsel_ir::SequentialScope();
    // assert( scope );
    // kernel->setContext( scope );

    // libcsel_ir::Reference* program = 0;

    // for( auto e : value.get< libcasm_ir::Function >() )
    // {
    //     libcasm_ir::Value* function = e.second;

    //     assert(
    //         function and libcasm_ir::isa< libcasm_ir::Function >( function )
    //         );
    //     libcasm_ir::Function* f = (libcasm_ir::Function*)function;
    //     libcsel_ir::Variable* v = libcasm_rt::FunctionState::create( *f );

    //     libcsel_ir::Reference* ref = new libcsel_ir::Reference(
    //         ( (libcsel_ir::Variable*)v )->getIdent(), v->type(), kernel,
    //         libcsel_ir::Reference::LINKAGE );
    //     assert( ref );
    //     ref->setRef< libcsel_ir::Variable >( v );
    //     v->setRef< libcsel_ir::Reference >( ref );

    //     if( v == libcasm_rt::ProgramFunctionState::create() )
    //     {
    //         assert( !program && " only one program variable is allowed! " );
    //         program = ref;
    //     }

    //     function2linkage[ f ] = ref;

    //     libcasm_rt::State::create()->add( v );
    // }
    // assert( program );

    // libcsel_ir::Reference* uset = 0;
    // if( m_module->has< libcsel_ir::Memory >() )
    // {
    //     for( auto mem : m_module->get< libcsel_ir::Memory >() )
    //     {
    //         assert( libcsel_ir::isa< libcsel_ir::Memory >( mem ) );

    //         libcsel_ir::Reference* ref = new libcsel_ir::Reference( "uset",
    //             mem->type(), kernel, libcsel_ir::Reference::LINKAGE );
    //         assert( ref );
    //         ref->setRef< libcsel_ir::Memory >( mem );
    //         mem->setRef< libcsel_ir::Reference >( ref );

    //         uset = ref;
    //     }
    // }

    // libcsel_ir::Reference* ic_ref = new libcsel_ir::Reference(
    // "interconnect",
    //     libcasm_rt::State::create()->type(), kernel,
    //     libcsel_ir::Reference::LINKAGE );
    // ic_ref->setRef< libcsel_ir::Interconnect >( libcasm_rt::State::create()
    // );
    // libcasm_rt::State::create()->setRef< libcsel_ir::Reference >( ic_ref );

    // // TODO: FIXME: this agent->rule->init_rule detection should be created
    // // directly in the AST to IR transf.
    // //              so that it is a direct property of an Agent!!!
    // assert( value.has< libcasm_ir::Agent >() );
    // assert( value.get< libcasm_ir::Agent >().size() == 1 );

    // libcasm_ir::Value* agent_ptr
    //     = value.get< libcasm_ir::Agent >().begin()->second;
    // assert( libcasm_ir::isa< libcasm_ir::Agent >( agent_ptr ) );
    // libcasm_ir::Agent* agent = (libcasm_ir::Agent*)agent_ptr;

    // libcasm_ir::Rule* init_rule = agent->initRule();

    // libcsel_ir::Value* init_rule_func_val = reference[ init_rule ];
    // assert( init_rule_func_val );
    // assert( libcsel_ir::isa< libcsel_ir::Function >( init_rule_func_val ) );
    // libcsel_ir::Function* init_rule_func
    //     = (libcsel_ir::Function*)init_rule_func_val;

    // libcsel_ir::TrivialStatement* prolog
    //     = new libcsel_ir::TrivialStatement( scope );
    // libcsel_ir::Value* pv = new libcsel_ir::ExtractInstruction(
    //     program, program->structure()->get( 0 ) );
    // libcsel_ir::IdInstruction* id
    //     = new libcsel_ir::IdInstruction( init_rule_func );
    // assert( id );
    // libcsel_ir::Value* lpv = new libcsel_ir::StoreInstruction( id, pv );
    // prolog->add( lpv );

    // libcsel_ir::Value* pd = new libcsel_ir::ExtractInstruction(
    //     program, program->structure()->get( 1 ) );
    // libcsel_ir::Value* c = libcsel_ir::Constant::Bit(
    //     libcsel_ir::Type::Bit( pd->type().bitsize() ), 1 );
    // assert( c );
    // m_module->add( c );
    // libcsel_ir::Value* lpd = new libcsel_ir::StoreInstruction( c, pd );
    // prolog->add( lpd );

    // libcsel_ir::LoopStatement* loop = new libcsel_ir::LoopStatement( scope );
    // pd = new libcsel_ir::ExtractInstruction(
    //     program, program->structure()->get( 1 ) );
    // lpd = new libcsel_ir::LoadInstruction( pd );
    // c = libcsel_ir::Constant::Bit(
    //     libcsel_ir::Type::Bit( pd->type().bitsize() ), 0 );
    // assert( c );
    // m_module->add( c );
    // libcsel_ir::Value* check = new libcsel_ir::NeqInstruction( lpd, c
    // );
    // loop->add( check );

    // libcsel_ir::SequentialScope* loop_true = new
    // libcsel_ir::SequentialScope();
    // loop->addScope( loop_true );
    // libcsel_ir::TrivialStatement* execute
    //     = new libcsel_ir::TrivialStatement( loop_true );
    // pv = new libcsel_ir::ExtractInstruction(
    //     program, program->structure()->get( 0 ) );
    // lpv = new libcsel_ir::LoadInstruction( pv );

    // // libcsel_ir::CastInstruction* cast = new libcsel_ir::CastInstruction(
    // // libcasm_rt::ProgramRuleSignature::create(), lpv );
    // // libcsel_ir::CallInstruction* run_rule = new
    // libcsel_ir::CallInstruction(
    // // cast
    // // );

    // libcsel_ir::IdCallInstruction* run_rule = new
    // libcsel_ir::IdCallInstruction(
    //     libcasm_rt::ProgramRuleSignature::create(), lpv );
    // run_rule->add( ic_ref );
    // run_rule->add( uset );

    // run_rule->setRef< libcsel_ir::Module >( m_module );

    // execute->add( run_rule );

    // for( auto e : value.get< libcasm_ir::Function >() )
    // {
    //     libcasm_ir::Value* function = e.second;

    //     assert(
    //         function and libcasm_ir::isa< libcasm_ir::Function >( function )
    //         );
    //     libcasm_ir::Function* f = (libcasm_ir::Function*)function;
    //     libcsel_ir::Variable* v = libcasm_rt::FunctionState::create( *f );

    //     libcsel_ir::BranchStatement* branch
    //         = new libcsel_ir::BranchStatement( loop_true );

    //     libcsel_ir::Instruction* v_id = new libcsel_ir::IdInstruction( v );
    //     libcsel_ir::Instruction* el = new libcsel_ir::ExtractInstruction(
    //         uset, v_id ); // PPA: HACK!!! should be through hash!!!

    //     libcsel_ir::Structure* update_type = libcasm_rt::Update::create();
    //     libcsel_ir::Instruction* ca
    //         = new libcsel_ir::CastInstruction( update_type, el );
    //     libcsel_ir::Instruction* u_bra
    //         = new libcsel_ir::ExtractInstruction( ca, update_type->get( 0 )
    //         );
    //     libcsel_ir::Instruction* l_bra
    //         = new libcsel_ir::LoadInstruction( u_bra );
    //     branch->add( new libcsel_ir::NeqInstruction( l_bra, c ) );

    //     libcsel_ir::SequentialScope* branch_apply
    //         = new libcsel_ir::SequentialScope();
    //     branch->addScope( branch_apply );
    //     libcsel_ir::TrivialStatement* stmt_apply
    //         = new libcsel_ir::TrivialStatement( branch_apply );

    //     // PPA: HACK!!! should be through hash!!!
    //     // libcsel_ir::Instruction* u_el = new
    //     libcsel_ir::ExtractInstruction(
    //     // uset,
    //     // new libcsel_ir::IdInstruction( v ) );
    //     // libcsel_ir::Instruction* u_ca = new libcsel_ir::CastInstruction(
    //     // update_type, u_el );
    //     // libcsel_ir::Instruction* u_loc = new
    //     libcsel_ir::ExtractInstruction(
    //     // u_ca, update_type->get(1) );
    //     libcsel_ir::Instruction* u_val
    //         = new libcsel_ir::ExtractInstruction( ca, update_type->get( 2 )
    //         );
    //     libcsel_ir::Instruction* u_def
    //         = new libcsel_ir::ExtractInstruction( ca, update_type->get( 3 )
    //         );

    //     libcsel_ir::Reference* f_ref = function2linkage[ f ];
    //     libcsel_ir::Instruction* f_val = new libcsel_ir::ExtractInstruction(
    //         f_ref, f_ref->structure()->get( 0 ) );
    //     libcsel_ir::Instruction* f_def = new libcsel_ir::ExtractInstruction(
    //         f_ref, f_ref->structure()->get( 1 ) );

    //     libcsel_ir::Instruction* l_val
    //         = new libcsel_ir::LoadInstruction( u_val );
    //     libcsel_ir::Instruction* t_val
    //         = new libcsel_ir::TruncationInstruction( l_val, f_val->type()
    //         );

    //     libcsel_ir::Instruction* st_val
    //         = new libcsel_ir::StoreInstruction( t_val, f_val );
    //     libcsel_ir::Instruction* st_def
    //         = new libcsel_ir::StoreInstruction( u_def, f_def );

    //     stmt_apply->add( st_val );
    //     stmt_apply->add( st_def );
    // }

    // // libcsel_ir::TrivialStatement* epilog = new
    // libcsel_ir::TrivialStatement(
    // // scope );
    // // for( auto var : m_module->get< libcsel_ir::Variable >() )
    // // {
    // // 	libcsel_ir::StreamInstruction* output = new
    // // libcsel_ir::StreamInstruction(
    // // libcsel_ir::StreamInstruction::OUTPUT );
    // // 	assert( output );
    // // 	output->add( var );
    // // 	output->add( &libcsel_ir::StringConstant::LF );
    // // 	epilog->add( output );
    // // }

    // // generation of 'stand-alone' kernel function which is the main function
    // of
    // // all target domains!
    // libcsel_ir::Function* func = new libcsel_ir::Function( "main",
    //     libcsel_ir::Type::Relation( libcsel_ir::Type::Bit( 32 ), {} )
    //     );
    // assert( func );
    // m_module->add( func );
    // libcsel_ir::SequentialScope* func_scope = new
    // libcsel_ir::SequentialScope();
    // assert( func_scope );
    // func->setContext( func_scope );
    // libcsel_ir::TrivialStatement* stmt
    //     = new libcsel_ir::TrivialStatement( func_scope );
    // stmt->add( new libcsel_ir::CallInstruction( kernel ) );
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::Agent& value, libcasm_ir::Context& )
{
    // PPA: agent generation currently not implemented due to single agent
    // execution behavior!
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::Agent& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::Builtin& value, libcasm_ir::Context& )
{
    assert( !" TODO " );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::Builtin& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::Function& value, libcasm_ir::Context& )
{
    assert( !" PPA: TODO!!! " );

    // // TODO: FIXME: implement a Memory access if it is not a 0-ary function!
    // // libcsel_ir::Memory* mem = new libcsel_ir::Memory( factory(
    // // value.type() ),
    // // 1 );

    // libcsel_ir::Variable* state = libcasm_rt::FunctionState::create( value );
    // m_module->add( state );

    // libcsel_ir::CallableUnit* location
    //     = libcasm_rt::FunctionLocation::create( value );
    // m_module->add( location );
    // reference[&value ] = location;

    // // TODO: FIXME: PPA: the following line should be removed in the near
    // future
    // //                   after a clean 'self' and Agent implementation!
    // if( strcmp( value.name(), "program" ) == 0 )
    // {
    //     return;
    // }

    // assert( value.type().getID() == libcasm_ir::Type::RELATION );
    // libcasm_ir::RelationType* ftype
    //     = static_cast< libcasm_ir::RelationType* >( value.type() );

    // if( ftype->getArguments().size() != 0 )
    // {
    //     assert( !" unimplemented transformation for n-ary functions!" );
    // }

    // // printf( "%s:%i: '%s'\n", __FILE__, __LINE__,
    // value.type().name()
    // // );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::Function& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::Derived& value, libcasm_ir::Context& )
{
    assert( !" TODO! " );
}
void CasmIRToCselIRPass::visit_interlog(
    libcasm_ir::Derived& value, libcasm_ir::Context& )
{
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::Derived& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::Rule& value, libcasm_ir::Context& )
{
    assert( !" PPA: TODO!!! " );

    const char* name = libstdhl::Allocator::string(
        "casm_rule_" + std::string( value.name() ) );

    if( m_reference.count( &value ) > 0 )
    {
        libcsel_ir::Value* ptr = m_reference[&value ];
        assert( ptr and strcmp( ptr->name(), name ) == 0 );
        return;
    }

    libcsel_ir::Function* obj = new libcsel_ir::Function(
        name, &libcasm_rt::Type::get( value.type() ) );
    assert( obj );
    m_module->add( obj );

    // /*libcsel_ir::Value* refs = */ obj->in(
    //     "refs", libcasm_rt::State::create()->type() );
    // /*libcsel_ir::Value* uset = */ obj->in(
    //     "uset", libcasm_rt::UpdateSet::create()->type() );

    m_reference[&value ] = obj;
}
void CasmIRToCselIRPass::visit_interlog(
    libcasm_ir::Rule& value, libcasm_ir::Context& )
{
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::Rule& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::ParallelBlock& value, libcasm_ir::Context& )
{
    libcsel_ir::ParallelScope* scope = new libcsel_ir::ParallelScope();
    assert( scope );

    libcasm_ir::ExecutionSemanticsBlock* parent_scope = value.scope();
    if( !parent_scope )
    {
        libcasm_ir::Rule* rule = value.bound();

        libcsel_ir::Function* comp
            = (libcsel_ir::Function*)( m_reference[ rule ] );
        comp->setContext( scope );
    }
    else
    {
        libcasm_ir::Value* parent = value.parent();
        assert( parent );
        assert( m_reference[ parent ] );

        libcsel_ir::Scope* upper_scope
            = static_cast< libcsel_ir::Scope* >( m_reference[ parent ] );
        upper_scope->add( scope );
        scope->setParent( upper_scope );
    }

    m_reference[&value ] = scope;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::ParallelBlock& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::SequentialBlock& value, libcasm_ir::Context& )
{
    libcsel_ir::SequentialScope* scope = new libcsel_ir::SequentialScope();
    assert( scope );

    libcasm_ir::ExecutionSemanticsBlock* parent_scope = value.scope();
    if( !parent_scope )
    {
        libcasm_ir::Rule* rule = value.bound();

        libcsel_ir::Function* comp
            = (libcsel_ir::Function*)( m_reference[ rule ] );
        comp->setContext( scope );
    }
    else
    {
        libcasm_ir::Value* parent = value.parent();
        assert( parent );
        assert( m_reference[ parent ] );

        libcsel_ir::Scope* upper_scope
            = static_cast< libcsel_ir::Scope* >( m_reference[ parent ] );
        upper_scope->add( scope );
        scope->setParent( upper_scope );
    }

    m_reference[&value ] = scope;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::SequentialBlock& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::TrivialStatement& value, libcasm_ir::Context& )
{
    libcasm_ir::ExecutionSemanticsBlock* parent = value.scope();
    assert( parent );

    libcsel_ir::TrivialStatement* stmt
        = new libcsel_ir::TrivialStatement( m_reference[ parent ] );
    assert( stmt );

    m_reference[&value ] = stmt;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::TrivialStatement& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::BranchStatement& value, libcasm_ir::Context& )
{
    libcasm_ir::ExecutionSemanticsBlock* parent = value.scope();
    assert( parent );

    libcsel_ir::BranchStatement* stmt
        = new libcsel_ir::BranchStatement( m_reference[ parent ] );
    assert( stmt );

    m_reference[&value ] = stmt;
}
void CasmIRToCselIRPass::visit_interlog(
    libcasm_ir::BranchStatement& value, libcasm_ir::Context& )
{
    libcsel_ir::BranchStatement* stmt
        = (libcsel_ir::BranchStatement*)m_reference[&value ];

    libcsel_ir::Value* last = stmt->instructions().back();

    assert( libcsel_ir::isa< libcsel_ir::CallInstruction >( last ) );
    libcsel_ir::CallInstruction* last_call = (libcsel_ir::CallInstruction*)last;

    assert(
        libcsel_ir::isa< libcsel_ir::CallableUnit >( last_call->value( 0 ) ) );
    libcsel_ir::CallableUnit* last_func
        = (libcsel_ir::CallableUnit*)( last_call->value( 0 ) );
    libcsel_ir::Reference* result
        = (libcsel_ir::Reference*)last_func->outParameters()[ 0 ];

    libcsel_ir::Instruction* reg
        = (libcsel_ir::Instruction*)( last_call->values().back() );

    assert( strcmp( result->structure()->name(), "Boolean" ) == 0 );

    libcsel_ir::Instruction* rv = new libcsel_ir::ExtractInstruction(
        reg, result->structure()->at( 0 ) );
    libcsel_ir::Instruction* rd = new libcsel_ir::ExtractInstruction(
        reg, result->structure()->at( 1 ) );

    libcsel_ir::Instruction* lv = new libcsel_ir::LoadInstruction( rv );
    libcsel_ir::Instruction* ld = new libcsel_ir::LoadInstruction( rd );

    libcsel_ir::Instruction* rt = new libcsel_ir::EquInstruction( lv, ld );

    stmt->add( rt );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::BranchStatement& value, libcasm_ir::Context& )
{
    libcsel_ir::BranchStatement* stmt
        = (libcsel_ir::BranchStatement*)m_reference[&value ];

    for( auto b : value.blocks() )
    {
        libcsel_ir::Value* scope = m_reference[ b ];
        assert( scope && libcsel_ir::isa< libcsel_ir::Scope >( scope ) );

        stmt->addScope( (libcsel_ir::Scope*)scope );
    }

    m_reference[&value ] = 0;
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::LocalInstruction& value, libcasm_ir::Context& )
{
    assert( !" TODO " );
    // printf( ">>>>>>>>>>>>>>>>>>>>>>>>> %p\n", &value );

    // libcsel_ir::Structure* local_type = libcasm_rt::Type::create(
    //     static_cast< libcasm_ir::Value& >( value ) );

    // libcsel_ir::AllocInstruction* local
    //     = new libcsel_ir::AllocInstruction( local_type->type() );
    // assert( local );

    // libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    // assert( parent );
    // libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)m_reference[ parent
    // ];
    // assert( stmt );
    // stmt->add( local );

    // m_reference[&value ] = local;
}

void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::LocalInstruction& value, libcasm_ir::Context& )
{
    m_reference[&value ] = 0;
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::AssertInstruction& value, libcasm_ir::Context& )
{
    assert( !" TODO " );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::AssertInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::SelectInstruction& value, libcasm_ir::Context& )
{
    assert( !" TODO " );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::SelectInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::SkipInstruction& value, libcasm_ir::Context& )
{
    assert( !" not implemented !!! " );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::SkipInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::ForkInstruction& value, libcasm_ir::Context& )
{
    assert( !" not implemented !!! " );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::ForkInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::MergeInstruction& value, libcasm_ir::Context& )
{
    assert( !" not implemented !!! " );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::MergeInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::LocationInstruction& value, libcasm_ir::Context& )
{
    assert( value.values().size() >= 1 );

    libcasm_ir::Value* src = value.value( 0 );
    assert( libcasm_ir::isa< libcasm_ir::Function >( src ) );

    libcsel_ir::Value* location_src = m_reference[ src ];
    assert( location_src );

    libcsel_ir::CallInstruction* call
        = new libcsel_ir::CallInstruction( location_src );
    assert( call );

    assert( libcsel_ir::isa< libcsel_ir::Intrinsic >( location_src ) );
    libcsel_ir::Intrinsic* location_src_ptr
        = (libcsel_ir::Intrinsic*)location_src;

    assert( location_src_ptr->outParameters().size() == 1 );

    libcsel_ir::AllocInstruction* alloc = new libcsel_ir::AllocInstruction(
        &location_src_ptr->outParameters()[ 0 ]->type() );
    assert( alloc );
    call->add( alloc );

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.statement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)m_reference[ parent ];
    assert( stmt );
    stmt->add( call );

    m_reference[&value ] = alloc;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::LocationInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::LookupInstruction& value, libcasm_ir::Context& )
{
    assert( !" PPA: TODO!!! " );

    // libcsel_ir::CallableUnit* lup
    //     = libcasm_rt::LookupImplementation::create( value, m_module );

    // assert( value.values().size() == 1 );

    // libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    // assert( parent );
    // libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)m_reference[ parent
    // ];
    // assert( stmt );

    // // TODO: FIXME: PPA: the following code block can be reused and can be
    // // provided in a generic way!!!
    // libcsel_ir::Value* context = stmt;
    // while( not libcsel_ir::isa< libcsel_ir::CallableUnit >( context ) )
    // {
    //     assert( libcsel_ir::isa< libcsel_ir::Block >( context ) );
    //     context
    //         = (libcsel_ir::Value*)( (libcsel_ir::Block*)context
    //         )->getParent();
    // }
    // assert( libcsel_ir::isa< libcsel_ir::CallableUnit >( context ) );
    // libcsel_ir::CallableUnit* caller = (libcsel_ir::CallableUnit*)context;

    // libcasm_ir::Value* src = value.get();
    // assert( libcasm_ir::isa< libcasm_ir::LocationInstruction >( src ) );

    // libcsel_ir::Value* lookup_src = m_reference[ src ];
    // assert( lookup_src );

    // libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( lup
    // );
    // assert( call );
    // call->add( caller->inParameters()[ 0 ] );
    // call->add( caller->inParameters()[ 1 ] );
    // call->add( lookup_src );

    // libcsel_ir::AllocInstruction* alloc = new libcsel_ir::AllocInstruction(
    //     libcasm_rt::Integer::create()->type() );
    // assert( alloc );
    // call->add( alloc );

    // stmt->add( call );

    // m_reference[&value ] = alloc;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::LookupInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::UpdateInstruction& value, libcasm_ir::Context& )
{
    assert( !" PPA: TODO!!! " );

    // libcsel_ir::CallableUnit* upd
    //     = libcasm_rt::UpdateImplementation::create( value, m_module );

    // assert( value.values().size() == 2 );

    // libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
    // assert( parent );
    // libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)m_reference[ parent
    // ];
    // assert( stmt );

    // // TODO: FIXME: PPA: the following code block can be reused and can be
    // // provided in a generic way!!!
    // libcsel_ir::Value* context = stmt;
    // while( not libcsel_ir::isa< libcsel_ir::CallableUnit >( context ) )
    // {
    //     assert( libcsel_ir::isa< libcsel_ir::Block >( context ) );
    //     context
    //         = (libcsel_ir::Value*)( (libcsel_ir::Block*)context
    //         )->getParent();
    // }
    // assert( libcsel_ir::isa< libcsel_ir::CallableUnit >( context ) );
    // libcsel_ir::CallableUnit* caller = (libcsel_ir::CallableUnit*)context;

    // libcasm_ir::Value* src = value.value( 0 );
    // assert( libcasm_ir::isa< libcasm_ir::LocationInstruction >( src ) );
    // libcsel_ir::Value* update_src = m_reference[ src ];
    // assert( update_src );

    // libcasm_ir::Value* val = value.value( 1 );
    // assert( libcasm_ir::isa< libcasm_ir::Instruction >( val )
    //         or libcasm_ir::isa< libcasm_ir::Constant >( val ) );
    // libcsel_ir::Value* update_val = m_reference[ val ];
    // assert( update_val );

    // libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( upd
    // );
    // assert( call );

    // call->add( caller->inParameters()[ 1 ] );
    // call->add( update_src );
    // call->add( update_val );

    // stmt->add( call );

    // m_reference[&value ] = call;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::UpdateInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::CallInstruction& value, libcasm_ir::Context& )
{
    assert( !" TODO " );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::CallInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::PrintInstruction& value, libcasm_ir::Context& )
{
    static libcsel_ir::Value* undef = 0;
    if( not undef )
    {
        undef = libcsel_ir::Constant::String( "undef" );
        m_module->add( undef );
    }

    libcsel_ir::StreamInstruction* obj = new libcsel_ir::StreamInstruction(
        libcsel_ir::StreamInstruction::OUTPUT );
    assert( obj );

    // for( libcasm_ir::Value* v : value.values() )
    // {
    //     libcsel_ir::Value* e = m_reference[ v ];
    //     libcsel_ir::Structure* s = libcasm_rt::Type::create( *v );

    //     // if( libcasm_ir::isa< libcasm_ir::StringConstant >( v ) )
    //     // {
    //     //     assert(
    //     //         libcsel_ir::isa< libcsel_ir::StructureConstant >( e
    //     ) );
    //     //     libcsel_ir::StructureConstant* c
    //     //         = (libcsel_ir::StructureConstant*)e;

    //     //     assert( libcsel_ir::isa< libcsel_ir::BitConstant >(
    //     //         c->getElements()[ 1 ] ) );
    //     //     libcsel_ir::BitConstant* def
    //     //         = (libcsel_ir::BitConstant*)c->getElements()[ 1 ];
    //     //     if( def->value()[ 0 ] == 0 )
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

    // PPA: TODO: HERE!!!!
    // obj->add( &libcsel_ir::StringConstant::LF );

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.statement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)m_reference[ parent ];
    assert( stmt );

    stmt->add( obj );

    m_reference[&value ] = obj;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::PrintInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::AddInstruction& value, libcasm_ir::Context& )
{
    libcsel_ir::CallableUnit* obj
        = libcasm_rt::Instruction::create( value, m_module );
    libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( obj );
    assert( call );

    libcsel_ir::Value* lhs = m_reference[ &value.lhs() ];
    assert( lhs );
    call->add( lhs );

    libcsel_ir::Value* rhs = m_reference[ &value.rhs() ];
    assert( rhs );
    call->add( rhs );

    libcsel_ir::AllocInstruction* result = new libcsel_ir::AllocInstruction(
        &obj->outParameters()[ 0 ]->type() );
    assert( result );
    call->add( result );
    m_reference[&value ] = result;

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.statement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)m_reference[ parent ];
    assert( stmt );
    stmt->add( call );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::AddInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::SubInstruction& value, libcasm_ir::Context& )
{
    DUMP_PREFIX;
    DUMP_POSTFIX;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::SubInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::MulInstruction& value, libcasm_ir::Context& )
{
    DUMP_PREFIX;
    DUMP_POSTFIX;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::MulInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::ModInstruction& value, libcasm_ir::Context& )
{
    DUMP_PREFIX;
    DUMP_POSTFIX;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::ModInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::DivInstruction& value, libcasm_ir::Context& )
{
    libcsel_ir::CallableUnit* obj
        = libcasm_rt::Instruction::create( value, m_module );
    libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( obj );
    assert( call );

    libcsel_ir::Value* lhs = m_reference[ &value.lhs() ];
    assert( lhs );
    call->add( lhs );

    libcsel_ir::Value* rhs = m_reference[ &value.rhs() ];
    assert( rhs );
    call->add( rhs );

    libcsel_ir::AllocInstruction* result = new libcsel_ir::AllocInstruction(
        &obj->outParameters()[ 0 ]->type() );
    assert( result );
    call->add( result );
    m_reference[&value ] = result;

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.statement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)m_reference[ parent ];
    assert( stmt );
    stmt->add( call );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::DivInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::AndInstruction& value, libcasm_ir::Context& )
{
    DUMP_PREFIX;
    DUMP_POSTFIX;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::AndInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::XorInstruction& value, libcasm_ir::Context& )
{
    DUMP_PREFIX;
    DUMP_POSTFIX;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::XorInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::OrInstruction& value, libcasm_ir::Context& )
{
    DUMP_PREFIX;
    DUMP_POSTFIX;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::OrInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::EquInstruction& value, libcasm_ir::Context& )
{
    libcsel_ir::CallableUnit* obj
        = libcasm_rt::Instruction::create( value, m_module );
    libcsel_ir::CallInstruction* call = new libcsel_ir::CallInstruction( obj );
    assert( call );

    libcsel_ir::Value* lhs = m_reference[ &value.lhs() ];
    assert( lhs );
    call->add( lhs );

    libcsel_ir::Value* rhs = m_reference[ &value.rhs() ];
    assert( rhs );
    call->add( rhs );

    libcsel_ir::AllocInstruction* result = new libcsel_ir::AllocInstruction(
        &obj->outParameters()[ 0 ]->type() );
    assert( result );
    call->add( result );
    m_reference[&value ] = result;

    libcasm_ir::Value* parent = (libcasm_ir::Value*)value.statement();
    assert( parent );
    libcsel_ir::Statement* stmt = (libcsel_ir::Statement*)m_reference[ parent ];
    assert( stmt );
    stmt->add( call );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::EquInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::NeqInstruction& value, libcasm_ir::Context& )
{
    DUMP_PREFIX;
    DUMP_POSTFIX;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::NeqInstruction& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::LthInstruction& value, libcasm_ir::Context& )
{
    DUMP_PREFIX;
    DUMP_POSTFIX;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::LthInstruction& value, libcasm_ir::Context& )
{
}

//
// Constants
//

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::AgentConstant& value, libcasm_ir::Context& )
{
    // TODO: FIXME: PPA: this is obsolete for now!!!
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::AgentConstant& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::RuleReferenceConstant& value, libcasm_ir::Context& )
{
    assert( !" TODO " );

    // libcsel_ir::Value* def = value.isDefined() ? libcsel_ir::Constant::TRUE()
    //                                            :
    //                                            libcsel_ir::Constant::FALSE();

    // libcsel_ir::Value* val = libcsel_ir::Constant::NIL();

    // libcasm_ir::Value* rule = value.value();
    // if( rule )
    // {
    //     assert( libcasm_ir::isa< libcasm_ir::Rule >( rule ) );
    //     if( m_reference.count( rule ) == 0 )
    //     {
    //         // pre-visit only for CallableUnit pointer creation!
    //         visit_prolog( *( (libcasm_ir::Rule*)rule ) );
    //     }
    //     assert( m_reference.count( rule ) != 0 );
    //     libcsel_ir::Value* c = m_reference[ rule ];

    //     assert( libcsel_ir::isa< libcsel_ir::CallableUnit >( c ) );
    //     libcsel_ir::CallableUnit* callable = (libcsel_ir::CallableUnit*)c;
    //     val = callable->getAllocationID();
    // }

    // assert( val );
    // assert( def );

    // libcsel_ir::Value* const_rule = 0;
    //     // = libcsel_ir::StructureConstant::create(
    //     // libcasm_rt::RulePtr::create(), { val, def } );

    // m_module->add( const_rule );
    // m_reference[&value ] = const_rule;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::RuleReferenceConstant& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::BooleanConstant& value, libcasm_ir::Context& )
{
    assert( !" TODO " );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::BooleanConstant& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::IntegerConstant& value, libcasm_ir::Context& )
{
    assert( !" TODO " );

    // libcsel_ir::Value* val = libcsel_ir::BitConstant::create(
    // value.value(),
    //     libcasm_rt::Integer::create()->get( 0 )->type().getBitsize() );
    // libcsel_ir::Value* def = libcsel_ir::BitConstant::create(
    // value.isDefined(),
    //     libcasm_rt::Integer::create()->get( 1 )->type().getBitsize() );
    // assert( val );
    // assert( def );

    // libcsel_ir::Value* const_int = libcsel_ir::StructureConstant::create(
    //     libcasm_rt::Integer::create(), { val, def } );

    // m_module->add( const_int );
    // m_reference[&value ] = const_int;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::IntegerConstant& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::BitConstant& value, libcasm_ir::Context& )
{
    assert( !" TODO " );
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::BitConstant& value, libcasm_ir::Context& )
{
}

void CasmIRToCselIRPass::visit_prolog(
    libcasm_ir::StringConstant& value, libcasm_ir::Context& )
{
    assert( !" TODO " );
    // printf( "%s:%i: '%s'\n", __FILE__, __LINE__, value.value() );

    // libcsel_ir::Structure* type = libcasm_rt::String::create( value );

    // m_module->add( type );

    // libcsel_ir::Value* val
    //     = libcsel_ir::StringConstant::create( value.value() );
    // libcsel_ir::Value* def = libcsel_ir::BitConstant::create(
    //     value.isDefined(), type->get( 1 )->type().getBitsize() );
    // assert( val );
    // assert( def );

    // libcsel_ir::Value* const_string
    //     = libcsel_ir::StructureConstant::create( type, { val, def } );

    // m_module->add( const_string );
    // m_reference[&value ] = const_string;
}
void CasmIRToCselIRPass::visit_epilog(
    libcasm_ir::StringConstant& value, libcasm_ir::Context& )
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
