//
//  Copyright (C) 2015-2024 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-be/graphs/contributors>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-be is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-be
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-be. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-be give you permission to link libcasm-be
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-be. If you modify libcasm-be, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "CasmIRToCjelIRPass.h"

#include <libpass/PassRegistry>

using namespace libcasm_be;

char CasmIRToCjelIRPass::id = 0;

static libpass::PassRegistration< CasmIRToCjelIRPass > PASS(
    "CASM IR to CJEL IR",
    "translates the CASM IR to the CJEL intermeditate representation",
    "ir2el",
    0 );

void CasmIRToCjelIRPass::usage( libpass::PassUsage& pu )
{
    pu.require< libcasm_ir::ConsistencyCheckPass >();
}

u1 CasmIRToCjelIRPass::run( libpass::PassResult& pr )
{
    // const auto data = pr.result< libcasm_ir::ConsistencyCheckPass >();
    // const auto specification = data->specification();

    // // specification->iterate( libcasm_ir::Traversal::PREORDER, this );

    // // pr.setResult< CasmIRToCjelIRPass >( m_module );
    // // pr.setResult< libcjel_ir::CjelIRDumpPass >( m_module );

    // assert( 0 );  // TODO

    return true;
}

// libcjel_ir::Module* CasmIRToCjelIRPass::module( void ) const
// {
//     assert( m_module );
//     return m_module;
// }

// #define DUMP_PREFIX                                                            \
//     printf( "%-14s: %p, %s", __FUNCTION__, &value, value.name() )
// #define DUMP_POSTFIX printf( " [TODO]\n" );

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::Specification& value, libcasm_ir::Context& )
// {
//     m_module = new libcjel_ir::Module( value.name() );

//     assert( !" PPA: TODO!!! " );

//     // m_module->add( libcasm_rt::UpdateSet::create() );

//     // m_module->add( libcasm_rt::Boolean::create() );
//     // m_module->add( libcasm_rt::Integer::create() );
//     // m_module->add( libcasm_rt::RulePtr::create() );
//     // m_module->add( libcasm_rt::Update::create() );

//     // m_module->add( libcasm_rt::HashImplementation::create() );

//     // m_module->add( libcasm_rt::State::create() );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::Specification& value, libcasm_ir::Context& )
// {
//     std::unordered_map< libcasm_ir::Function*, libcjel_ir::Reference* >
//         function2linkage;

//     assert( !" PPA: TODO!!! " );

//     // // CASM RT KERNEL
//     // libcjel_ir::Type* kernel_ty
//     //     = libcjel_ir::Type::Relation( libcjel_ir::Type::Bit( 1 ), {} );

//     // libcjel_ir::Function* kernel
//     //     = new libcjel_ir::Function( value.name(), kernel_ty );
//     // assert( kernel );
//     // m_module->add( kernel );

//     // libcjel_ir::SequentialScope* scope = new
//     libcjel_ir::SequentialScope();
//     // assert( scope );
//     // kernel->setContext( scope );

//     // libcjel_ir::Reference* program = 0;

//     // for( auto e : value.get< libcasm_ir::Function >() )
//     // {
//     //     libcasm_ir::Value* function = e.second;

//     //     assert(
//     //         function and libcasm_ir::isa< libcasm_ir::Function >( function
//     )
//     //         );
//     //     libcasm_ir::Function* f = (libcasm_ir::Function*)function;
//     //     libcjel_ir::Variable* v = libcasm_rt::FunctionState::create( *f );

//     //     libcjel_ir::Reference* ref = new libcjel_ir::Reference(
//     //         ( (libcjel_ir::Variable*)v )->getIdent(), v->type(), kernel,
//     //         libcjel_ir::Reference::LINKAGE );
//     //     assert( ref );
//     //     ref->setRef< libcjel_ir::Variable >( v );
//     //     v->setRef< libcjel_ir::Reference >( ref );

//     //     if( v == libcasm_rt::ProgramFunctionState::create() )
//     //     {
//     //         assert( !program && " only one program variable is allowed! "
//     );
//     //         program = ref;
//     //     }

//     //     function2linkage[ f ] = ref;

//     //     libcasm_rt::State::create()->add( v );
//     // }
//     // assert( program );

//     // libcjel_ir::Reference* uset = 0;
//     // if( m_module->has< libcjel_ir::Memory >() )
//     // {
//     //     for( auto mem : m_module->get< libcjel_ir::Memory >() )
//     //     {
//     //         assert( libcjel_ir::isa< libcjel_ir::Memory >( mem ) );

//     //         libcjel_ir::Reference* ref = new libcjel_ir::Reference(
//     "uset",
//     //             mem->type(), kernel, libcjel_ir::Reference::LINKAGE );
//     //         assert( ref );
//     //         ref->setRef< libcjel_ir::Memory >( mem );
//     //         mem->setRef< libcjel_ir::Reference >( ref );

//     //         uset = ref;
//     //     }
//     // }

//     // libcjel_ir::Reference* ic_ref = new libcjel_ir::Reference(
//     // "interconnect",
//     //     libcasm_rt::State::create()->type(), kernel,
//     //     libcjel_ir::Reference::LINKAGE );
//     // ic_ref->setRef< libcjel_ir::Interconnect >(
//     libcasm_rt::State::create()
//     // );
//     // libcasm_rt::State::create()->setRef< libcjel_ir::Reference >( ic_ref
//     );

//     // // TODO: FIXME: this agent->rule->init_rule detection should be
//     created
//     // // directly in the AST to IR transf.
//     // //              so that it is a direct property of an Agent!!!
//     // assert( value.has< libcasm_ir::Agent >() );
//     // assert( value.get< libcasm_ir::Agent >().size() == 1 );

//     // libcasm_ir::Value* agent_ptr
//     //     = value.get< libcasm_ir::Agent >().begin()->second;
//     // assert( libcasm_ir::isa< libcasm_ir::Agent >( agent_ptr ) );
//     // libcasm_ir::Agent* agent = (libcasm_ir::Agent*)agent_ptr;

//     // libcasm_ir::Rule* init_rule = agent->initRule();

//     // libcjel_ir::Value* init_rule_func_val = reference[ init_rule ];
//     // assert( init_rule_func_val );
//     // assert( libcjel_ir::isa< libcjel_ir::Function >( init_rule_func_val )
//     );
//     // libcjel_ir::Function* init_rule_func
//     //     = (libcjel_ir::Function*)init_rule_func_val;

//     // libcjel_ir::TrivialStatement* prolog
//     //     = new libcjel_ir::TrivialStatement( scope );
//     // libcjel_ir::Value* pv = new libcjel_ir::ExtractInstruction(
//     //     program, program->structure()->get( 0 ) );
//     // libcjel_ir::IdInstruction* id
//     //     = new libcjel_ir::IdInstruction( init_rule_func );
//     // assert( id );
//     // libcjel_ir::Value* lpv = new libcjel_ir::StoreInstruction( id, pv );
//     // prolog->add( lpv );

//     // libcjel_ir::Value* pd = new libcjel_ir::ExtractInstruction(
//     //     program, program->structure()->get( 1 ) );
//     // libcjel_ir::Value* c = libcjel_ir::Constant::Bit(
//     //     libcjel_ir::Type::Bit( pd->type().bitsize() ), 1 );
//     // assert( c );
//     // m_module->add( c );
//     // libcjel_ir::Value* lpd = new libcjel_ir::StoreInstruction( c, pd );
//     // prolog->add( lpd );

//     // libcjel_ir::LoopStatement* loop = new libcjel_ir::LoopStatement( scope
//     );
//     // pd = new libcjel_ir::ExtractInstruction(
//     //     program, program->structure()->get( 1 ) );
//     // lpd = new libcjel_ir::LoadInstruction( pd );
//     // c = libcjel_ir::Constant::Bit(
//     //     libcjel_ir::Type::Bit( pd->type().bitsize() ), 0 );
//     // assert( c );
//     // m_module->add( c );
//     // libcjel_ir::Value* check = new libcjel_ir::NeqInstruction( lpd, c
//     // );
//     // loop->add( check );

//     // libcjel_ir::SequentialScope* loop_true = new
//     // libcjel_ir::SequentialScope();
//     // loop->addScope( loop_true );
//     // libcjel_ir::TrivialStatement* execute
//     //     = new libcjel_ir::TrivialStatement( loop_true );
//     // pv = new libcjel_ir::ExtractInstruction(
//     //     program, program->structure()->get( 0 ) );
//     // lpv = new libcjel_ir::LoadInstruction( pv );

//     // // libcjel_ir::CastInstruction* cast = new
//     libcjel_ir::CastInstruction(
//     // // libcasm_rt::ProgramRuleSignature::create(), lpv );
//     // // libcjel_ir::CallInstruction* run_rule = new
//     // libcjel_ir::CallInstruction(
//     // // cast
//     // // );

//     // libcjel_ir::IdCallInstruction* run_rule = new
//     // libcjel_ir::IdCallInstruction(
//     //     libcasm_rt::ProgramRuleSignature::create(), lpv );
//     // run_rule->add( ic_ref );
//     // run_rule->add( uset );

//     // run_rule->setRef< libcjel_ir::Module >( m_module );

//     // execute->add( run_rule );

//     // for( auto e : value.get< libcasm_ir::Function >() )
//     // {
//     //     libcasm_ir::Value* function = e.second;

//     //     assert(
//     //         function and libcasm_ir::isa< libcasm_ir::Function >( function
//     )
//     //         );
//     //     libcasm_ir::Function* f = (libcasm_ir::Function*)function;
//     //     libcjel_ir::Variable* v = libcasm_rt::FunctionState::create( *f );

//     //     libcjel_ir::BranchStatement* branch
//     //         = new libcjel_ir::BranchStatement( loop_true );

//     //     libcjel_ir::Instruction* v_id = new libcjel_ir::IdInstruction( v
//     );
//     //     libcjel_ir::Instruction* el = new libcjel_ir::ExtractInstruction(
//     //         uset, v_id ); // PPA: HACK!!! should be through hash!!!

//     //     libcjel_ir::Structure* update_type = libcasm_rt::Update::create();
//     //     libcjel_ir::Instruction* ca
//     //         = new libcjel_ir::CastInstruction( update_type, el );
//     //     libcjel_ir::Instruction* u_bra
//     //         = new libcjel_ir::ExtractInstruction( ca, update_type->get( 0
//     )
//     //         );
//     //     libcjel_ir::Instruction* l_bra
//     //         = new libcjel_ir::LoadInstruction( u_bra );
//     //     branch->add( new libcjel_ir::NeqInstruction( l_bra, c ) );

//     //     libcjel_ir::SequentialScope* branch_apply
//     //         = new libcjel_ir::SequentialScope();
//     //     branch->addScope( branch_apply );
//     //     libcjel_ir::TrivialStatement* stmt_apply
//     //         = new libcjel_ir::TrivialStatement( branch_apply );

//     //     // PPA: HACK!!! should be through hash!!!
//     //     // libcjel_ir::Instruction* u_el = new
//     //     libcjel_ir::ExtractInstruction(
//     //     // uset,
//     //     // new libcjel_ir::IdInstruction( v ) );
//     //     // libcjel_ir::Instruction* u_ca = new
//     libcjel_ir::CastInstruction(
//     //     // update_type, u_el );
//     //     // libcjel_ir::Instruction* u_loc = new
//     //     libcjel_ir::ExtractInstruction(
//     //     // u_ca, update_type->get(1) );
//     //     libcjel_ir::Instruction* u_val
//     //         = new libcjel_ir::ExtractInstruction( ca, update_type->get( 2
//     )
//     //         );
//     //     libcjel_ir::Instruction* u_def
//     //         = new libcjel_ir::ExtractInstruction( ca, update_type->get( 3
//     )
//     //         );

//     //     libcjel_ir::Reference* f_ref = function2linkage[ f ];
//     //     libcjel_ir::Instruction* f_val = new
//     libcjel_ir::ExtractInstruction(
//     //         f_ref, f_ref->structure()->get( 0 ) );
//     //     libcjel_ir::Instruction* f_def = new
//     libcjel_ir::ExtractInstruction(
//     //         f_ref, f_ref->structure()->get( 1 ) );

//     //     libcjel_ir::Instruction* l_val
//     //         = new libcjel_ir::LoadInstruction( u_val );
//     //     libcjel_ir::Instruction* t_val
//     //         = new libcjel_ir::TruncationInstruction( l_val, f_val->type()
//     //         );

//     //     libcjel_ir::Instruction* st_val
//     //         = new libcjel_ir::StoreInstruction( t_val, f_val );
//     //     libcjel_ir::Instruction* st_def
//     //         = new libcjel_ir::StoreInstruction( u_def, f_def );

//     //     stmt_apply->add( st_val );
//     //     stmt_apply->add( st_def );
//     // }

//     // // libcjel_ir::TrivialStatement* epilog = new
//     // libcjel_ir::TrivialStatement(
//     // // scope );
//     // // for( auto var : m_module->get< libcjel_ir::Variable >() )
//     // // {
//     // // 	libcjel_ir::StreamInstruction* output = new
//     // // libcjel_ir::StreamInstruction(
//     // // libcjel_ir::StreamInstruction::OUTPUT );
//     // // 	assert( output );
//     // // 	output->add( var );
//     // // 	output->add( &libcjel_ir::StringConstant::LF );
//     // // 	epilog->add( output );
//     // // }

//     // // generation of 'stand-alone' kernel function which is the main
//     function
//     // of
//     // // all target domains!
//     // libcjel_ir::Function* func = new libcjel_ir::Function( "main",
//     //     libcjel_ir::Type::Relation( libcjel_ir::Type::Bit( 32 ), {} )
//     //     );
//     // assert( func );
//     // m_module->add( func );
//     // libcjel_ir::SequentialScope* func_scope = new
//     // libcjel_ir::SequentialScope();
//     // assert( func_scope );
//     // func->setContext( func_scope );
//     // libcjel_ir::TrivialStatement* stmt
//     //     = new libcjel_ir::TrivialStatement( func_scope );
//     // stmt->add( new libcjel_ir::CallInstruction( kernel ) );
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::Agent& value, libcasm_ir::Context& )
// {
//     // PPA: agent generation currently not implemented due to single agent
//     // execution behavior!
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::Agent& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::Builtin& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::Builtin& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::Function& value, libcasm_ir::Context& )
// {
//     assert( !" PPA: TODO!!! " );

//     // // TODO: FIXME: implement a Memory access if it is not a 0-ary
//     function!
//     // // libcjel_ir::Memory* mem = new libcjel_ir::Memory( factory(
//     // // value.type() ),
//     // // 1 );

//     // libcjel_ir::Variable* state = libcasm_rt::FunctionState::create( value
//     );
//     // m_module->add( state );

//     // libcjel_ir::CallableUnit* location
//     //     = libcasm_rt::FunctionLocation::create( value );
//     // m_module->add( location );
//     // reference[&value ] = location;

//     // // TODO: FIXME: PPA: the following line should be removed in the near
//     // future
//     // //                   after a clean 'self' and Agent implementation!
//     // if( strcmp( value.name(), "program" ) == 0 )
//     // {
//     //     return;
//     // }

//     // assert( value.type().getID() == libcasm_ir::Type::RELATION );
//     // libcasm_ir::RelationType* ftype
//     //     = static_cast< libcasm_ir::RelationType* >( value.type() );

//     // if( ftype->getArguments().size() != 0 )
//     // {
//     //     assert( !" unimplemented transformation for n-ary functions!" );
//     // }

//     // // printf( "%s:%i: '%s'\n", __FILE__, __LINE__,
//     // value.type().name()
//     // // );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::Function& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::Derived& value, libcasm_ir::Context& )
// {
//     assert( !" TODO! " );
// }
// void CasmIRToCjelIRPass::visit_interlog(
//     libcasm_ir::Derived& value, libcasm_ir::Context& )
// {
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::Derived& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::Rule& value, libcasm_ir::Context& )
// {
//     assert( !" PPA: TODO!!! " );

//     const char* name = libstdhl::Allocator::string(
//         "casm_rule_" + std::string( value.name() ) );

//     if( m_reference.count( &value ) > 0 )
//     {
//         libcjel_ir::Value* ptr = m_reference[&value ];
//         assert( ptr and strcmp( ptr->name(), name ) == 0 );
//         return;
//     }

//     libcjel_ir::Function* obj = new libcjel_ir::Function(
//         name, &libcasm_rt::Type::get( value.type() ) );
//     assert( obj );
//     m_module->add( obj );

//     // /*libcjel_ir::Value* refs = */ obj->in(
//     //     "refs", libcasm_rt::State::create()->type() );
//     // /*libcjel_ir::Value* uset = */ obj->in(
//     //     "uset", libcasm_rt::UpdateSet::create()->type() );

//     m_reference[&value ] = obj;
// }
// void CasmIRToCjelIRPass::visit_interlog(
//     libcasm_ir::Rule& value, libcasm_ir::Context& )
// {
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::Rule& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::ParallelBlock& value, libcasm_ir::Context& )
// {
//     libcjel_ir::ParallelScope* scope = new libcjel_ir::ParallelScope();
//     assert( scope );

//     libcasm_ir::ExecutionSemanticsBlock* parent_scope = value.scope();
//     if( !parent_scope )
//     {
//         libcasm_ir::Rule* rule = value.bound();

//         libcjel_ir::Function* comp
//             = (libcjel_ir::Function*)( m_reference[ rule ] );
//         comp->setContext( scope );
//     }
//     else
//     {
//         libcasm_ir::Value* parent = value.parent();
//         assert( parent );
//         assert( m_reference[ parent ] );

//         libcjel_ir::Scope* upper_scope
//             = static_cast< libcjel_ir::Scope* >( m_reference[ parent ] );
//         upper_scope->add( scope );
//         scope->setParent( upper_scope );
//     }

//     m_reference[&value ] = scope;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::ParallelBlock& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::SequentialBlock& value, libcasm_ir::Context& )
// {
//     libcjel_ir::SequentialScope* scope = new libcjel_ir::SequentialScope();
//     assert( scope );

//     libcasm_ir::ExecutionSemanticsBlock* parent_scope = value.scope();
//     if( !parent_scope )
//     {
//         libcasm_ir::Rule* rule = value.bound();

//         libcjel_ir::Function* comp
//             = (libcjel_ir::Function*)( m_reference[ rule ] );
//         comp->setContext( scope );
//     }
//     else
//     {
//         libcasm_ir::Value* parent = value.parent();
//         assert( parent );
//         assert( m_reference[ parent ] );

//         libcjel_ir::Scope* upper_scope
//             = static_cast< libcjel_ir::Scope* >( m_reference[ parent ] );
//         upper_scope->add( scope );
//         scope->setParent( upper_scope );
//     }

//     m_reference[&value ] = scope;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::SequentialBlock& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::TrivialStatement& value, libcasm_ir::Context& )
// {
//     libcasm_ir::ExecutionSemanticsBlock* parent = value.scope();
//     assert( parent );

//     libcjel_ir::TrivialStatement* stmt
//         = new libcjel_ir::TrivialStatement( m_reference[ parent ] );
//     assert( stmt );

//     m_reference[&value ] = stmt;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::TrivialStatement& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::BranchStatement& value, libcasm_ir::Context& )
// {
//     libcasm_ir::ExecutionSemanticsBlock* parent = value.scope();
//     assert( parent );

//     libcjel_ir::BranchStatement* stmt
//         = new libcjel_ir::BranchStatement( m_reference[ parent ] );
//     assert( stmt );

//     m_reference[&value ] = stmt;
// }
// void CasmIRToCjelIRPass::visit_interlog(
//     libcasm_ir::BranchStatement& value, libcasm_ir::Context& )
// {
//     libcjel_ir::BranchStatement* stmt
//         = (libcjel_ir::BranchStatement*)m_reference[&value ];

//     libcjel_ir::Value* last = stmt->instructions().back();

//     assert( libcjel_ir::isa< libcjel_ir::CallInstruction >( last ) );
//     libcjel_ir::CallInstruction* last_call =
//     (libcjel_ir::CallInstruction*)last;

//     assert(
//         libcjel_ir::isa< libcjel_ir::CallableUnit >( last_call->value( 0 ) )
//         );
//     libcjel_ir::CallableUnit* last_func
//         = (libcjel_ir::CallableUnit*)( last_call->value( 0 ) );
//     libcjel_ir::Reference* result
//         = (libcjel_ir::Reference*)last_func->outParameters()[ 0 ];

//     libcjel_ir::Instruction* reg
//         = (libcjel_ir::Instruction*)( last_call->values().back() );

//     assert( strcmp( result->structure()->name(), "Boolean" ) == 0 );

//     libcjel_ir::Instruction* rv = new libcjel_ir::ExtractInstruction(
//         reg, result->structure()->at( 0 ) );
//     libcjel_ir::Instruction* rd = new libcjel_ir::ExtractInstruction(
//         reg, result->structure()->at( 1 ) );

//     libcjel_ir::Instruction* lv = new libcjel_ir::LoadInstruction( rv );
//     libcjel_ir::Instruction* ld = new libcjel_ir::LoadInstruction( rd );

//     libcjel_ir::Instruction* rt = new libcjel_ir::EquInstruction( lv, ld );

//     stmt->add( rt );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::BranchStatement& value, libcasm_ir::Context& )
// {
//     libcjel_ir::BranchStatement* stmt
//         = (libcjel_ir::BranchStatement*)m_reference[&value ];

//     for( auto b : value.blocks() )
//     {
//         libcjel_ir::Value* scope = m_reference[ b ];
//         assert( scope && libcjel_ir::isa< libcjel_ir::Scope >( scope ) );

//         stmt->addScope( (libcjel_ir::Scope*)scope );
//     }

//     m_reference[&value ] = 0;
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::LocalInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );
//     // printf( ">>>>>>>>>>>>>>>>>>>>>>>>> %p\n", &value );

//     // libcjel_ir::Structure* local_type = libcasm_rt::Type::create(
//     //     static_cast< libcasm_ir::Value& >( value ) );

//     // libcjel_ir::AllocInstruction* local
//     //     = new libcjel_ir::AllocInstruction( local_type->type() );
//     // assert( local );

//     // libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
//     // assert( parent );
//     // libcjel_ir::Statement* stmt = (libcjel_ir::Statement*)m_reference[
//     parent
//     // ];
//     // assert( stmt );
//     // stmt->add( local );

//     // m_reference[&value ] = local;
// }

// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::LocalInstruction& value, libcasm_ir::Context& )
// {
//     m_reference[&value ] = 0;
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::AssertInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::AssertInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::SelectInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::SelectInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::SkipInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" not implemented !!! " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::SkipInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::ForkInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" not implemented !!! " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::ForkInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::MergeInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" not implemented !!! " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::MergeInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::LocationInstruction& value, libcasm_ir::Context& )
// {
//     assert( value.values().size() >= 1 );

//     libcasm_ir::Value* src = value.value( 0 );
//     assert( libcasm_ir::isa< libcasm_ir::Function >( src ) );

//     libcjel_ir::Value* location_src = m_reference[ src ];
//     assert( location_src );

//     libcjel_ir::CallInstruction* call
//         = new libcjel_ir::CallInstruction( location_src );
//     assert( call );

//     assert( libcjel_ir::isa< libcjel_ir::Intrinsic >( location_src ) );
//     libcjel_ir::Intrinsic* location_src_ptr
//         = (libcjel_ir::Intrinsic*)location_src;

//     assert( location_src_ptr->outParameters().size() == 1 );

//     libcjel_ir::AllocInstruction* alloc = new libcjel_ir::AllocInstruction(
//         &location_src_ptr->outParameters()[ 0 ]->type() );
//     assert( alloc );
//     call->add( alloc );

//     libcasm_ir::Value* parent = (libcasm_ir::Value*)value.statement();
//     assert( parent );
//     libcjel_ir::Statement* stmt = (libcjel_ir::Statement*)m_reference[ parent
//     ];
//     assert( stmt );
//     stmt->add( call );

//     m_reference[&value ] = alloc;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::LocationInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::LookupInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" PPA: TODO!!! " );

//     // libcjel_ir::CallableUnit* lup
//     //     = libcasm_rt::LookupImplementation::create( value, m_module );

//     // assert( value.values().size() == 1 );

//     // libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
//     // assert( parent );
//     // libcjel_ir::Statement* stmt = (libcjel_ir::Statement*)m_reference[
//     parent
//     // ];
//     // assert( stmt );

//     // // TODO: FIXME: PPA: the following code block can be reused and can be
//     // // provided in a generic way!!!
//     // libcjel_ir::Value* context = stmt;
//     // while( not libcjel_ir::isa< libcjel_ir::CallableUnit >( context ) )
//     // {
//     //     assert( libcjel_ir::isa< libcjel_ir::Block >( context ) );
//     //     context
//     //         = (libcjel_ir::Value*)( (libcjel_ir::Block*)context
//     //         )->getParent();
//     // }
//     // assert( libcjel_ir::isa< libcjel_ir::CallableUnit >( context ) );
//     // libcjel_ir::CallableUnit* caller = (libcjel_ir::CallableUnit*)context;

//     // libcasm_ir::Value* src = value.get();
//     // assert( libcasm_ir::isa< libcasm_ir::LocationInstruction >( src ) );

//     // libcjel_ir::Value* lookup_src = m_reference[ src ];
//     // assert( lookup_src );

//     // libcjel_ir::CallInstruction* call = new libcjel_ir::CallInstruction(
//     lup
//     // );
//     // assert( call );
//     // call->add( caller->inParameters()[ 0 ] );
//     // call->add( caller->inParameters()[ 1 ] );
//     // call->add( lookup_src );

//     // libcjel_ir::AllocInstruction* alloc = new
//     libcjel_ir::AllocInstruction(
//     //     libcasm_rt::Integer::create()->type() );
//     // assert( alloc );
//     // call->add( alloc );

//     // stmt->add( call );

//     // m_reference[&value ] = alloc;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::LookupInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::UpdateInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" PPA: TODO!!! " );

//     // libcjel_ir::CallableUnit* upd
//     //     = libcasm_rt::UpdateImplementation::create( value, m_module );

//     // assert( value.values().size() == 2 );

//     // libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
//     // assert( parent );
//     // libcjel_ir::Statement* stmt = (libcjel_ir::Statement*)m_reference[
//     parent
//     // ];
//     // assert( stmt );

//     // // TODO: FIXME: PPA: the following code block can be reused and can be
//     // // provided in a generic way!!!
//     // libcjel_ir::Value* context = stmt;
//     // while( not libcjel_ir::isa< libcjel_ir::CallableUnit >( context ) )
//     // {
//     //     assert( libcjel_ir::isa< libcjel_ir::Block >( context ) );
//     //     context
//     //         = (libcjel_ir::Value*)( (libcjel_ir::Block*)context
//     //         )->getParent();
//     // }
//     // assert( libcjel_ir::isa< libcjel_ir::CallableUnit >( context ) );
//     // libcjel_ir::CallableUnit* caller = (libcjel_ir::CallableUnit*)context;

//     // libcasm_ir::Value* src = value.value( 0 );
//     // assert( libcasm_ir::isa< libcasm_ir::LocationInstruction >( src ) );
//     // libcjel_ir::Value* update_src = m_reference[ src ];
//     // assert( update_src );

//     // libcasm_ir::Value* val = value.value( 1 );
//     // assert( libcasm_ir::isa< libcasm_ir::Instruction >( val )
//     //         or libcasm_ir::isa< libcasm_ir::Constant >( val ) );
//     // libcjel_ir::Value* update_val = m_reference[ val ];
//     // assert( update_val );

//     // libcjel_ir::CallInstruction* call = new libcjel_ir::CallInstruction(
//     upd
//     // );
//     // assert( call );

//     // call->add( caller->inParameters()[ 1 ] );
//     // call->add( update_src );
//     // call->add( update_val );

//     // stmt->add( call );

//     // m_reference[&value ] = call;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::UpdateInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::CallInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::CallInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::PrintInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::PrintInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::AddInstruction& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );

//     auto obj = libcasm_rt::Value::get( value, m_module );

//     // libcjel_ir::CallInstruction* call = new libcjel_ir::CallInstruction(
//     obj
//     // );
//     // assert( call );

//     // libcjel_ir::Value* lhs = m_reference[ &value.lhs() ];
//     // assert( lhs );
//     // call->add( lhs );

//     // libcjel_ir::Value* rhs = m_reference[ &value.rhs() ];
//     // assert( rhs );
//     // call->add( rhs );

//     // libcjel_ir::AllocInstruction* result = new
//     libcjel_ir::AllocInstruction(
//     //     &obj->outParameters()[ 0 ]->type() );
//     // assert( result );
//     // call->add( result );
//     // m_reference[&value ] = result;

//     // libcasm_ir::Value* parent = (libcasm_ir::Value*)value.statement();
//     // assert( parent );
//     // libcjel_ir::Statement* stmt = (libcjel_ir::Statement*)m_reference[
//     parent
//     // ];
//     // assert( stmt );
//     // stmt->add( call );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::AddInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::SubInstruction& value, libcasm_ir::Context& )
// {
//     DUMP_PREFIX;
//     DUMP_POSTFIX;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::SubInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::MulInstruction& value, libcasm_ir::Context& )
// {
//     DUMP_PREFIX;
//     DUMP_POSTFIX;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::MulInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::ModInstruction& value, libcasm_ir::Context& )
// {
//     DUMP_PREFIX;
//     DUMP_POSTFIX;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::ModInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::DivInstruction& value, libcasm_ir::Context& )
// {
//     auto obj = libcasm_rt::Value::get( value, m_module );

//     // libcjel_ir::Value* lhs = m_reference[ &value.lhs() ];
//     // assert( lhs );
//     // call->add( lhs );

//     // libcjel_ir::Value* rhs = m_reference[ &value.rhs() ];
//     // assert( rhs );
//     // call->add( rhs );

//     // libcjel_ir::AllocInstruction* result = new
//     libcjel_ir::AllocInstruction(
//     //     &obj->outParameters()[ 0 ]->type() );
//     // assert( result );
//     // call->add( result );
//     // m_reference[&value ] = result;

//     // libcasm_ir::Value* parent = (libcasm_ir::Value*)value.statement();
//     // assert( parent );
//     // libcjel_ir::Statement* stmt = (libcjel_ir::Statement*)m_reference[
//     parent
//     // ];
//     // assert( stmt );
//     // stmt->add( call );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::DivInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::AndInstruction& value, libcasm_ir::Context& )
// {
//     DUMP_PREFIX;
//     DUMP_POSTFIX;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::AndInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::XorInstruction& value, libcasm_ir::Context& )
// {
//     DUMP_PREFIX;
//     DUMP_POSTFIX;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::XorInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::OrInstruction& value, libcasm_ir::Context& )
// {
//     DUMP_PREFIX;
//     DUMP_POSTFIX;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::OrInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::EquInstruction& value, libcasm_ir::Context& )
// {
//     auto obj = libcasm_rt::Value::get( value, m_module );

//     // libcjel_ir::CallInstruction* call = new libcjel_ir::CallInstruction(
//     obj
//     // );
//     // assert( call );

//     // libcjel_ir::Value* lhs = m_reference[ &value.lhs() ];
//     // assert( lhs );
//     // call->add( lhs );

//     // libcjel_ir::Value* rhs = m_reference[ &value.rhs() ];
//     // assert( rhs );
//     // call->add( rhs );

//     // libcjel_ir::AllocInstruction* result = new
//     libcjel_ir::AllocInstruction(
//     //     &obj->outParameters()[ 0 ]->type() );
//     // assert( result );
//     // call->add( result );
//     // m_reference[&value ] = result;

//     // libcasm_ir::Value* parent = (libcasm_ir::Value*)value.statement();
//     // assert( parent );
//     // libcjel_ir::Statement* stmt = (libcjel_ir::Statement*)m_reference[
//     parent
//     // ];
//     // assert( stmt );
//     // stmt->add( call );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::EquInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::NeqInstruction& value, libcasm_ir::Context& )
// {
//     DUMP_PREFIX;
//     DUMP_POSTFIX;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::NeqInstruction& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::LthInstruction& value, libcasm_ir::Context& )
// {
//     DUMP_PREFIX;
//     DUMP_POSTFIX;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::LthInstruction& value, libcasm_ir::Context& )
// {
// }

// //
// // Constants
// //

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::AgentConstant& value, libcasm_ir::Context& )
// {
//     // TODO: FIXME: PPA: this is obsolete for now!!!
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::AgentConstant& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::RuleReferenceConstant& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );

//     // libcjel_ir::Value* def = value.isDefined() ?
//     libcjel_ir::Constant::TRUE()
//     //                                            :
//     // libcjel_ir::Constant::FALSE();

//     // libcjel_ir::Value* val = libcjel_ir::Constant::NIL();

//     // libcasm_ir::Value* rule = value.value();
//     // if( rule )
//     // {
//     //     assert( libcasm_ir::isa< libcasm_ir::Rule >( rule ) );
//     //     if( m_reference.count( rule ) == 0 )
//     //     {
//     //         // pre-visit only for CallableUnit pointer creation!
//     //         visit_prolog( *( (libcasm_ir::Rule*)rule ) );
//     //     }
//     //     assert( m_reference.count( rule ) != 0 );
//     //     libcjel_ir::Value* c = m_reference[ rule ];

//     //     assert( libcjel_ir::isa< libcjel_ir::CallableUnit >( c ) );
//     //     libcjel_ir::CallableUnit* callable = (libcjel_ir::CallableUnit*)c;
//     //     val = callable->getAllocationID();
//     // }

//     // assert( val );
//     // assert( def );

//     // libcjel_ir::Value* const_rule = 0;
//     //     // = libcjel_ir::StructureConstant::create(
//     //     // libcasm_rt::RulePtr::create(), { val, def } );

//     // m_module->add( const_rule );
//     // m_reference[&value ] = const_rule;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::RuleReferenceConstant& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::BooleanConstant& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::BooleanConstant& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::IntegerConstant& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );

//     // libcjel_ir::Value* val = libcjel_ir::BitConstant::create(
//     // value.value(),
//     //     libcasm_rt::Integer::create()->get( 0 )->type().getBitsize() );
//     // libcjel_ir::Value* def = libcjel_ir::BitConstant::create(
//     // value.isDefined(),
//     //     libcasm_rt::Integer::create()->get( 1 )->type().getBitsize() );
//     // assert( val );
//     // assert( def );

//     // libcjel_ir::Value* const_int = libcjel_ir::StructureConstant::create(
//     //     libcasm_rt::Integer::create(), { val, def } );

//     // m_module->add( const_int );
//     // m_reference[&value ] = const_int;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::IntegerConstant& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::BitConstant& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::BitConstant& value, libcasm_ir::Context& )
// {
// }

// void CasmIRToCjelIRPass::visit_prolog(
//     libcasm_ir::StringConstant& value, libcasm_ir::Context& )
// {
//     assert( !" TODO " );
//     // printf( "%s:%i: '%s'\n", __FILE__, __LINE__, value.value() );

//     // libcjel_ir::Structure* type = libcasm_rt::String::create( value );

//     // m_module->add( type );

//     // libcjel_ir::Value* val
//     //     = libcjel_ir::StringConstant::create( value.value() );
//     // libcjel_ir::Value* def = libcjel_ir::BitConstant::create(
//     //     value.isDefined(), type->get( 1 )->type().getBitsize() );
//     // assert( val );
//     // assert( def );

//     // libcjel_ir::Value* const_string
//     //     = libcjel_ir::StructureConstant::create( type, { val, def } );

//     // m_module->add( const_string );
//     // m_reference[&value ] = const_string;
// }
// void CasmIRToCjelIRPass::visit_epilog(
//     libcasm_ir::StringConstant& value, libcasm_ir::Context& )
// {
// }

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
