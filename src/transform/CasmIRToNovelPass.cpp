//  
//  Copyright (c) 2015-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-be
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

#include "CasmIRToNovelPass.h"

using namespace libcasm_be;


char CasmIRToNovelPass::id = 0;

static libpass::PassRegistration< CasmIRToNovelPass > PASS
( "CASM IR to NOVEL IR"
, "generates a NOVEL instance of CASM IR"
, 0
, 0
);



bool CasmIRToNovelPass::run( libpass::PassResult& pr )
{
    libcasm_ir::Specification* value = (libcasm_ir::Specification*)pr.getResult< libcasm_ir::CasmIRDumpPass >();
	assert( value );
	
    module = 0;
	
	value->iterate
	( libcasm_ir::Traversal::PREORDER
	, this
	);
	
	pr.setResult< CasmIRToNovelPass >( module );
	pr.setResult< libnovel::NovelDumpPass >( module );
	
	return false;
}

libnovel::Module* CasmIRToNovelPass::getModule( void ) const
{
	assert( module );
	return module;
}

#define DUMP_PREFIX  printf( "%-14s: %p, %s", __FUNCTION__, &value, value.getName() )
#define DUMP_POSTFIX printf( " [TODO]\n" );





void CasmIRToNovelPass::visit_prolog( libcasm_ir::Specification& value )
{
    module = new libnovel::Module( value.getName() );
	
	module->add( libcasm_rt::UpdateSet::create() );	
	module->add( libcasm_rt::Integer::create() );
	module->add( libcasm_rt::RulePtr::create() );
	module->add( libcasm_rt::Update::create() );

	module->add( libcasm_rt::HashImplementation::create() );

	module->add( libcasm_rt::State::create() );
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Specification& value )
{
	std::unordered_map< libcasm_ir::Function*, libnovel::Reference* > function2linkage;
	
    // CASM RT KERNEL
	libnovel::Function* kernel = new libnovel::Function( value.getName() );
	assert( kernel );
	module->add( kernel );
	
	libnovel::SequentialScope* scope = new libnovel::SequentialScope();
	assert( scope );
	kernel->setContext( scope );
	
	libnovel::Reference* program = 0;
	
	for( auto function : value.get< libcasm_ir::Function >() )
	{
		assert( function and libcasm_ir::Value::isa< libcasm_ir::Function >( function ) );
		libcasm_ir::Function* f = (libcasm_ir::Function*)function;
	    libnovel::Variable* v = libcasm_rt::FunctionState::create( *f );
		
	    libnovel::Reference* ref = new libnovel::Reference
		( ((libnovel::Variable*)v)->getIdent()
		, v->getType()
		, kernel
		, libnovel::Reference::LINKAGE
		);
		assert( ref );
		ref->setRef< libnovel::Variable >( v );
		v->setRef< libnovel::Reference >( ref );
		
		if( v == libcasm_rt::ProgramFunctionState::create() )
		{
			assert( !program && " only one program variable is allowed! " );
			program = ref;
		}

		function2linkage[ f ] = ref;
	}
	assert( program );
	
	
	libnovel::Reference* uset = 0;
	if( module->has< libnovel::Memory >() )
	{
		for( auto mem : module->get< libnovel::Memory >() )
		{
			assert( libnovel::Value::isa< libnovel::Memory >( mem ) ); 
			
			libnovel::Reference* ref = new libnovel::Reference
			( "uset"
			, mem->getType()
			, kernel
			, libnovel::Reference::LINKAGE
			);
			assert( ref );
			ref->setRef< libnovel::Memory >( mem );
		    mem->setRef< libnovel::Reference >( ref );

			uset = ref;
		}
	}
	
	libnovel::Reference* ic_ref = new libnovel::Reference
	( "interconnect"
	, libcasm_rt::State::create()->getType()
	, kernel
	, libnovel::Reference::LINKAGE
	);
	ic_ref->setRef< libnovel::Interconnect >( libcasm_rt::State::create() );
	libcasm_rt::State::create()->setRef< libnovel::Reference >( ic_ref );
	
    
	// TODO: FIXME: this agent->rule->init_rule detection should be created directly in the AST to IR transf.
	//              so that it is a direct property of an Agent!!!
	assert( value.has< libcasm_ir::Agent >() );
	assert( value.get< libcasm_ir::Agent >().size() == 1 );
	libcasm_ir::Value* agent_ptr = value.get< libcasm_ir::Agent >()[0];
	assert( libcasm_ir::Value::isa< libcasm_ir::Agent >( agent_ptr ) );
	libcasm_ir::Agent* agent = (libcasm_ir::Agent*)agent_ptr;
	libcasm_ir::Rule* init_rule = agent->getInitRulePointer()->getValue();
	libnovel::Value* init_rule_func_val = reference[ init_rule ];
	assert( init_rule_func_val );
	assert( libnovel::Value::isa< libnovel::Function >( init_rule_func_val ) );
	libnovel::Function* init_rule_func = (libnovel::Function*)init_rule_func_val;
	
	
	
	libnovel::TrivialStatement* prolog = new libnovel::TrivialStatement( scope );
	libnovel::Value* pv  = new libnovel::ExtractInstruction( program, program->getStructure()->get(0) );
	libnovel::IdInstruction* id = new libnovel::IdInstruction( init_rule_func );
	assert( id );
	libnovel::Value* lpv = new libnovel::StoreInstruction( id, pv );
    prolog->add( lpv );
	
	libnovel::Value* pd  = new libnovel::ExtractInstruction( program, program->getStructure()->get(1) );
    libnovel::BitConstant* c = libnovel::BitConstant::create( 1, pd->getType()->getBitsize() );
	assert( c );
	module->add( c );
    libnovel::Value* lpd = new libnovel::StoreInstruction( c, pd );	
	prolog->add( lpd );
	
	libnovel::LoopStatement* loop = new libnovel::LoopStatement( scope );
    pd  = new libnovel::ExtractInstruction( program, program->getStructure()->get(1) );
    lpd = new libnovel::LoadInstruction( pd );
    c   = libnovel::BitConstant::create( 0, pd->getType()->getBitsize() );
	assert( c );
	module->add( c );
	libnovel::Value* check = new libnovel::NeqUnsignedInstruction( lpd, c );
	loop->add( check );
	
	libnovel::SequentialScope* loop_true = new libnovel::SequentialScope();	
	loop->addScope( loop_true );
    libnovel::TrivialStatement* execute = new libnovel::TrivialStatement( loop_true );
    pv  = new libnovel::ExtractInstruction( program, program->getStructure()->get(0) );
	lpv = new libnovel::LoadInstruction( pv );
	
	
	
	libnovel::CastInstruction* cast = new libnovel::CastInstruction( libcasm_rt::ProgramRuleSignature::create(), lpv );
	libnovel::CallInstruction* run_rule = new libnovel::CallInstruction( cast );
	
	run_rule->add( ic_ref );
    run_rule->add( uset );
    execute->add( run_rule );
	
	
	for( auto function : value.get< libcasm_ir::Function >() )
	{
		assert( function and libcasm_ir::Value::isa< libcasm_ir::Function >( function ) );
		libcasm_ir::Function* f = (libcasm_ir::Function*)function;
	    libnovel::Variable* v = libcasm_rt::FunctionState::create( *f );
		
		libnovel::BranchStatement* branch = new libnovel::BranchStatement( loop_true );
		
		
		
		libnovel::Instruction* v_id = new libnovel::IdInstruction( v );
		libnovel::Instruction* el = new libnovel::ExtractInstruction( uset, v_id ); // PPA: HACK!!! should be through hash!!!
		
		libnovel::Structure* update_type = libcasm_rt::Update::create();	
	    libnovel::Instruction* ca = new libnovel::CastInstruction( update_type, el );
		libnovel::Instruction* u_bra = new libnovel::ExtractInstruction( ca, update_type->get(0) );
		libnovel::Instruction* l_bra = new libnovel::LoadInstruction( u_bra );		
		branch->add( new libnovel::NeqUnsignedInstruction( l_bra, c ) );
		
		libnovel::SequentialScope* branch_apply = new libnovel::SequentialScope();	
	    branch->addScope( branch_apply );
		libnovel::TrivialStatement* stmt_apply = new libnovel::TrivialStatement( branch_apply );
		
		// PPA: HACK!!! should be through hash!!!
	    // libnovel::Instruction* u_el = new libnovel::ExtractInstruction( uset, new libnovel::IdInstruction( v ) );
	    // libnovel::Instruction* u_ca = new libnovel::CastInstruction( update_type, u_el );
		//libnovel::Instruction* u_loc = new libnovel::ExtractInstruction( u_ca, update_type->get(1) );
		libnovel::Instruction* u_val = new libnovel::ExtractInstruction( ca, update_type->get(2) );
	    libnovel::Instruction* u_def = new libnovel::ExtractInstruction( ca, update_type->get(3) );

		libnovel::Reference* f_ref = function2linkage[ f ];
		libnovel::Instruction* f_val = new libnovel::ExtractInstruction( f_ref, f_ref->getStructure()->get(0) );
		libnovel::Instruction* f_def = new libnovel::ExtractInstruction( f_ref, f_ref->getStructure()->get(1) );
		
		libnovel::Instruction* st_val = new libnovel::StoreInstruction( u_val, f_val );
		libnovel::Instruction* st_def = new libnovel::StoreInstruction( u_def, f_def );
	    
		stmt_apply->add( st_val );
		stmt_apply->add( st_def );		
	}
	
	
	libnovel::TrivialStatement* epilog = new libnovel::TrivialStatement( scope );	
	for( auto var : module->get< libnovel::Variable >() )
	{
		libnovel::StreamInstruction* output = new libnovel::StreamInstruction( libnovel::StreamInstruction::OUTPUT );
		assert( output );
		output->add( var );
		output->add( &libnovel::StringConstant::LF );
		epilog->add( output );
	}
	
	
	// generation of 'stand-alone' kernel function which is the main function of all target domains!
	libnovel::Function* func = new libnovel::Function( "main" );
	assert( func );
	module->add( func );
	libnovel::SequentialScope* func_scope = new libnovel::SequentialScope();
	assert( func_scope );
	func->setContext( func_scope );
	libnovel::TrivialStatement* stmt = new libnovel::TrivialStatement( func_scope );
    stmt->add( new libnovel::CallInstruction( kernel ) );
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::Agent& value )
{
	// PPA: agent generation currently not implemented due to single agent execution behavior!
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Agent& value )
{
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::Function& value )
{
	// TODO: FIXME: implement a Memory access if it is not a 0-ary function!
	// libnovel::Memory* mem = new libnovel::Memory( factory( value.getType() ), 1 );
	
	libnovel::Variable* state = libcasm_rt::FunctionState::create( value );
	module->add( state );
	
	libnovel::CallableUnit* location = libcasm_rt::FunctionLocation::create( value );
	module->add( location );
	reference[ &value ] = location;

	// TODO: FIXME: PPA: the following line should be removed in the near future
	//                   after a clean 'self' and Agent implementation!
	if( strcmp( value.getName(), "program" ) == 0 )
	{
		return;
	}
	
	const std::vector< libcasm_ir::Type* >& params = value.getType()->getParameters();
	if( params.size() != 0 )
	{
		assert( !" unimplemented transformation for n-ary functions!" );
	}
	
	//printf( "%s:%i: '%s'\n", __FILE__, __LINE__, value.getType()->getName() );	
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Function& value )
{
}



void CasmIRToNovelPass::visit_prolog( libcasm_ir::Rule& value )
{
	string* name = new string( "casm_rule__" + string( value.getName() ));
	
	
	libnovel::Function* obj = new libnovel::Function( name->c_str() );
	assert( obj );
	module->add( obj );
	
	libnovel::Value* refs = obj->in( "refs", libcasm_rt::State::create()->getType() );
	libnovel::Value* uset = obj->in( "uset", libcasm_rt::UpdateSet::create()->getType() );
    
	assert( reference.count( &value ) == 0 );
	reference[ &value ] = obj;
}
void CasmIRToNovelPass::visit_interlog( libcasm_ir::Rule& value )
{
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Rule& value )
{
	//reference[ &value ] = 0;
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::ParallelBlock& value )
{
	libnovel::ParallelScope* scope = new libnovel::ParallelScope();
	assert( scope );
	
    libcasm_ir::ExecutionSemanticsBlock* parent = value.getParent();
	if( !parent )
	{
		libcasm_ir::Rule* rule = value.getBound();
		
		libnovel::Function* comp = (libnovel::Function*)(reference[rule]);
		comp->setContext( scope );
	}
	else
	{
		assert(0);
	}
	
	reference[ &value ] = scope;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::ParallelBlock& value )
{
	reference[ &value ] = 0;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::SequentialBlock& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::SequentialBlock& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::TrivialStatement& value )
{
	libcasm_ir::ExecutionSemanticsBlock* parent = value.getScope();
	assert( parent );
	
	libnovel::TrivialStatement* stmt = new libnovel::TrivialStatement( reference[ parent ] );
	assert( stmt );
	
    reference[ &value ] = stmt;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::TrivialStatement& value )
{	
    reference[ &value ] = 0;
}

		
void CasmIRToNovelPass::visit_prolog( libcasm_ir::LocationInstruction& value )
{
    assert( value.getValues().size() >= 1 );
	
	libcasm_ir::Value* src = value.getValue(0);
	assert( libcasm_ir::Value::isa< libcasm_ir::Function >( src ) );
	
	libnovel::Value* location_src = reference[ src ];
	assert( location_src );
	
	libnovel::CallInstruction* call = new libnovel::CallInstruction( location_src );
	assert( call );
	
	assert( libnovel::Value::isa< libnovel::Intrinsic >( location_src ) );
	libnovel::Intrinsic* location_src_ptr = (libnovel::Intrinsic*)location_src;

	assert( location_src_ptr->getOutParameters().size() == 1 );
	
	libnovel::AllocInstruction* alloc = new libnovel::AllocInstruction( location_src_ptr->getOutParameters()[0]->getType() );
	assert( alloc );
	call->add( alloc );
	
	libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	assert( parent );	
	libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	assert( stmt );
	stmt->add( call );
	
	reference[ &value ] = alloc;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::LocationInstruction& value )
{
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::LookupInstruction& value )
{
	libnovel::CallableUnit* lup = libcasm_rt::LookupImplementation::create( value, module );
	
	
	assert( value.getValues().size() == 1 );
	
	libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	assert( parent );	
	libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	assert( stmt );
	
	
	// TODO: FIXME: PPA: the following code block can be reused and can be provided in a generic way!!!
	libnovel::Value* context = stmt;
	while( not libnovel::Value::isa< libnovel::CallableUnit >( context ) )
	{
		assert( libnovel::Value::isa< libnovel::Block >( context ) );
		context = (libnovel::Value*)((libnovel::Block*)context)->getParent();
	}
	assert( libnovel::Value::isa< libnovel::CallableUnit >( context ) );
	libnovel::CallableUnit* caller = (libnovel::CallableUnit*)context;
	
	
	libcasm_ir::Value* src = value.get();
	assert( libcasm_ir::Value::isa< libcasm_ir::LocationInstruction >( src ) );
	
	libnovel::Value* lookup_src = reference[ src ];
	assert( lookup_src );
	
	libnovel::CallInstruction* call = new libnovel::CallInstruction( lup );
	assert( call );
	call->add( caller->getInParameters()[0] );
	call->add( caller->getInParameters()[1] );
	call->add( lookup_src );
	
	libnovel::AllocInstruction* alloc = new libnovel::AllocInstruction( libcasm_rt::Integer::create()->getType() );
	assert( alloc );
	call->add( alloc );
	
	stmt->add( call );
	
	reference[ &value ] = alloc;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::LookupInstruction& value )
{
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::UpdateInstruction& value )
{
	libnovel::CallableUnit* upd = libcasm_rt::UpdateImplementation::create( value, module );
	
	
	assert( value.getValues().size() == 2 );

	libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	assert( parent );	
	libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	assert( stmt );
	
	// TODO: FIXME: PPA: the following code block can be reused and can be provided in a generic way!!!
	libnovel::Value* context = stmt;
	while( not libnovel::Value::isa< libnovel::CallableUnit >( context ) )
	{
		assert( libnovel::Value::isa< libnovel::Block >( context ) );
		context = (libnovel::Value*)((libnovel::Block*)context)->getParent();
	}
	assert( libnovel::Value::isa< libnovel::CallableUnit >( context ) );
	libnovel::CallableUnit* caller = (libnovel::CallableUnit*)context;

	
	libcasm_ir::Value* src = value.getValue(0);
	assert( libcasm_ir::Value::isa< libcasm_ir::LocationInstruction >( src ) );
	libnovel::Value* update_src = reference[ src ];
	assert( update_src );
	
	libcasm_ir::Value* val = value.getValue(1);
	assert
	(  libcasm_ir::Value::isa< libcasm_ir::Instruction >( val )
	or libcasm_ir::Value::isa< libcasm_ir::ConstantValue >( val )
	);
	libnovel::Value* update_val = reference[ val ];
	assert( update_val );
	
	libnovel::CallInstruction* call = new libnovel::CallInstruction( upd );
	assert( call );
	call->add( caller->getInParameters()[0] );
	call->add( caller->getInParameters()[1] );
	call->add( update_src );
	call->add( update_val );
	
	stmt->add( call );
	
	reference[ &value ] = call;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::UpdateInstruction& value )
{
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::AddInstruction& value )
{
	// TODO: FIXME: PPA: this add function has to be moved later into the 'run-time' implementation
	static libnovel::Intrinsic* add = 0;
	if( !add )
	{
		add = new libnovel::Intrinsic( "casm_rt__add" );
		assert( add );
		module->add( add );
		
		libnovel::Reference* ra = new libnovel::Reference
		( "ra"
		, libcasm_rt::Integer::create()->getType() // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, add
		);
		assert( ra );
	    
		libnovel::Reference* rb = new libnovel::Reference
		( "rb"
		, libcasm_rt::Integer::create()->getType() // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, add
		);
		assert( rb );

		libnovel::Reference* rt = new libnovel::Reference
		( "rt"
		, libcasm_rt::Integer::create()->getType() // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, add
		, libnovel::Reference::OUTPUT
		);
		assert( rt );
		
		libnovel::ParallelScope* scope = new libnovel::ParallelScope();
		assert( scope );
		add->setContext( scope );
		
		libnovel::ExtractInstruction* rav = new libnovel::ExtractInstruction( ra, ra->getStructure()->get(0) );
		libnovel::ExtractInstruction* rad = new libnovel::ExtractInstruction( ra, ra->getStructure()->get(1) );
		libnovel::ExtractInstruction* rbv = new libnovel::ExtractInstruction( rb, rb->getStructure()->get(0) );
		libnovel::ExtractInstruction* rbd = new libnovel::ExtractInstruction( rb, rb->getStructure()->get(1) );
		
		libnovel::LoadInstruction* lav  = new libnovel::LoadInstruction( rav );
		libnovel::LoadInstruction* lad  = new libnovel::LoadInstruction( rad );
		libnovel::LoadInstruction* lbv  = new libnovel::LoadInstruction( rbv );
		libnovel::LoadInstruction* lbd  = new libnovel::LoadInstruction( rbd );
		
		libnovel::AddSignedInstruction* icv = new libnovel::AddSignedInstruction( lav, lbv );
		libnovel::AndInstruction* icd = new libnovel::AndInstruction( lad, lbd );

		libnovel::ExtractInstruction* rtv = new libnovel::ExtractInstruction( rt, rt->getStructure()->get(0) );
		libnovel::ExtractInstruction* rtd = new libnovel::ExtractInstruction( rt, rt->getStructure()->get(1) );
		
		libnovel::StoreInstruction* scv = new libnovel::StoreInstruction( icv, rtv );
		libnovel::StoreInstruction* scd = new libnovel::StoreInstruction( icd, rtd );
		
		libnovel::TrivialStatement* stmt_v = new libnovel::TrivialStatement( scope );
		libnovel::TrivialStatement* stmt_d = new libnovel::TrivialStatement( scope );
		stmt_v->add( scv );
		stmt_d->add( scd );
	}
	
	libnovel::CallInstruction* call = new libnovel::CallInstruction( add );
	assert( call );
	
	libnovel::Value* lhs = reference[ value.getLHS() ];
	assert( lhs );
    call->add( lhs );
	
	libnovel::Value* rhs = reference[ value.getRHS() ];
	assert( rhs );
    call->add( rhs );
	
	libnovel::AllocInstruction* result = new libnovel::AllocInstruction( add->getOutParameters()[0]->getType() );
	assert( result );
	call->add( result );	
	reference[ &value ] = result;
	
	libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	assert( parent );	
	libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	assert( stmt );
	stmt->add( call );	
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::AddInstruction& value )
{}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::DivInstruction& value )
{
	// TODO: FIXME: PPA: this div function has to be moved later into the 'run-time' implementation
	static libnovel::Intrinsic* div = 0;
	if( !div )
	{
		div = new libnovel::Intrinsic( "casm_rt__div" );
		assert( div );
		module->add( div );
		
		libnovel::Reference* ra = new libnovel::Reference
		( "ra"
		, libcasm_rt::Integer::create()->getType() // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, div
		);
		assert( ra );

		libnovel::Reference* rb = new libnovel::Reference
		( "rb"
		, libcasm_rt::Integer::create()->getType() // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, div
		);
		assert( rb );

		libnovel::Reference* rt = new libnovel::Reference
		( "rt"
		, libcasm_rt::Integer::create()->getType() // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, div
		, libnovel::Reference::OUTPUT
		);
		assert( rt );
		
		libnovel::SequentialScope* scope = new libnovel::SequentialScope();
		assert( scope );
		div->setContext( scope );
		
		libnovel::ExtractInstruction* rav = new libnovel::ExtractInstruction( ra, ra->getStructure()->get(0) );
		libnovel::ExtractInstruction* rad = new libnovel::ExtractInstruction( ra, ra->getStructure()->get(1) );
		libnovel::ExtractInstruction* rbv = new libnovel::ExtractInstruction( rb, rb->getStructure()->get(0) );
		libnovel::ExtractInstruction* rbd = new libnovel::ExtractInstruction( rb, rb->getStructure()->get(1) );

		libnovel::LoadInstruction* lav  = new libnovel::LoadInstruction( rav );
		libnovel::LoadInstruction* lad  = new libnovel::LoadInstruction( rad );
		libnovel::LoadInstruction* lbv  = new libnovel::LoadInstruction( rbv );
		libnovel::LoadInstruction* lbd  = new libnovel::LoadInstruction( rbd );
		
		libnovel::DivSignedInstruction* icv = new libnovel::DivSignedInstruction( lav, lbv );
		libnovel::AndInstruction* icd = new libnovel::AndInstruction( lad, lbd );

		
		libnovel::ExtractInstruction* rtv = new libnovel::ExtractInstruction( rt, rt->getStructure()->get(0) );
		libnovel::ExtractInstruction* rtd = new libnovel::ExtractInstruction( rt, rt->getStructure()->get(1) );
		
		libnovel::StoreInstruction* scv = new libnovel::StoreInstruction( icv, rtv );
		libnovel::StoreInstruction* scd = new libnovel::StoreInstruction( icd, rtd );
		
		libnovel::TrivialStatement* stmt_v = new libnovel::TrivialStatement( scope );
		libnovel::TrivialStatement* stmt_d = new libnovel::TrivialStatement( scope );
		stmt_v->add( scv );
		stmt_d->add( scd );
	}
	
	libnovel::CallInstruction* call = new libnovel::CallInstruction( div );
	assert( call );
	
	libnovel::Value* lhs = reference[ value.getLHS() ];
	assert( lhs );
    call->add( lhs );
	
	libnovel::Value* rhs = reference[ value.getRHS() ];
	assert( rhs );
    call->add( rhs );
	
	libnovel::AllocInstruction* result = new libnovel::AllocInstruction( div->getOutParameters()[0]->getType() );
	assert( result );
	call->add( result );	
	reference[ &value ] = result;
	
	libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	assert( parent );	
	libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	assert( stmt );
	stmt->add( call );
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::DivInstruction& value )
{}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::AndInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::AndInstruction& value )
{}


// CONSTANTS

void CasmIRToNovelPass::visit_prolog( libcasm_ir::IntegerConstant& value )
{
	libnovel::Value* val = libnovel::BitConstant::create( value.getValue(),  libcasm_rt::Integer::create()->get(0)->getType()->getBitsize() );
	libnovel::Value* def = libnovel::BitConstant::create( value.isDefined(), libcasm_rt::Integer::create()->get(1)->getType()->getBitsize() );
	assert( val );
	assert( def );
	
	libnovel::Value* const_int = libnovel::StructureConstant::create( libcasm_rt::Integer::create(), { val, def } );
	
	module->add( const_int );
	reference[ &value ] = const_int;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::IntegerConstant& value )
{}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::RulePointerConstant& value )
{
	// TODO: PPA: FIXME!!! resolve libcasm_ir::RulePointerConstant to correct libnovel::CallableUnit pointer/reference !!! 
	// via value.getValue()
	
	libnovel::Value* val = libnovel::BitConstant::create( 0 /* FIXME: HACK! */,  libcasm_rt::RulePtr::create()->get(0)->getType()->getBitsize() );
	libnovel::Value* def = libnovel::BitConstant::create( value.isDefined(), libcasm_rt::RulePtr::create()->get(1)->getType()->getBitsize() );
	assert( val );
	assert( def );
	
	libnovel::Value* const_rule = libnovel::StructureConstant::create( libcasm_rt::RulePtr::create(), { val, def } );
	
	module->add( const_rule );
	reference[ &value ] = const_rule;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::RulePointerConstant& value )
{}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::AgentConstant& value )
{
	// TODO: FIXME: PPA: this is obsolete for now!!!
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::AgentConstant& value )
{}



//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  

