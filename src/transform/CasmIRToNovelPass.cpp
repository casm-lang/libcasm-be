//  
//  Copyright (c) 2016 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-be
//  
//  Permission is hereby granted, free of charge, to any person obtaining a 
//  copy of this software and associated documentation files (the "Software"), 
//  to deal with the Software without restriction, including without limitation 
//  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//  and/or sell copies of the Software, and to permit persons to whom the 
//  Software is furnished to do so, subject to the following conditions:
//  
//  * Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimers.
//  
//  * Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimers in the 
//    documentation and/or other materials provided with the distribution.
//  
//  * Neither the names of the copyright holders, nor the names of its 
//    contributors may be used to endorse or promote products derived from 
//    this Software without specific prior written permission.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
//  CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//  WITH THE SOFTWARE.
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
	
	// ADD RUNTIME !!!
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Specification& value )
{
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::Agent& value )
{
	// PPA: agent generation currently not implemented due to single agent execution behavior!
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Agent& value )
{
}

static libnovel::Structure* CasmRT_Integer = 0;

libnovel::Structure* CasmIRToNovelPass::factory( libcasm_ir::Type* type )
{
	static std::unordered_map< u64, libnovel::Structure* > cache;
	
	assert( type );
	assert( type->getParameters().size() == 0 );
	assert( type->getSubTypes().size() == 0 );

	libnovel::Structure* structure = 0;
	
	u64 tid = type->getID();
	
	if( tid == libcasm_ir::IntegerType.getID() )
	{
		auto result = cache.find( tid );
		if( result != cache.end() )
		{
			return result->second;
		}

		structure = new libnovel::Structure( "Integer" );
		assert( structure );
		CasmRT_Integer = structure;
		CasmRT_Integer->getType()->bind( CasmRT_Integer );
		
		structure->add( new libnovel::Structure( "value", &libnovel::TypeB64 ) );
		structure->add( new libnovel::Structure( "isdef", &libnovel::TypeB1  ) );
		
		cache[ tid ] = structure;
	    module->add( structure );
	}
	else
	{
		assert( !"only Integer type is currently supported!" );
	}

	return structure;
}

libnovel::Value* CasmIRToNovelPass::constant( libnovel::Type* type )
{
	assert( type );

	libnovel::Value* c = 0;
	
	if( type->getIDKind() == libnovel::Type::STRUCTURE )
	{
		libnovel::Value* b = type->getBound();
		assert( b and libnovel::Value::isa< libnovel::Structure >( b ) );
		libnovel::Structure* s = (libnovel::Structure*)b;
		c = libnovel::StructureConstant::create( s );
	}
	else
	{
		assert( !"unsupported type to create constant found!" );
	}
	
	assert( c );
	module->add( c );
	
	return c;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::Function& value )
{
	// TODO: FIXME: implement a Memory access if it is not a 0-ary function!
	// libnovel::Memory* mem = new libnovel::Memory( factory( value.getType() ), 1 );
	
	libnovel::Structure* ty = factory( value.getType() );
	libnovel::Variable* var = new libnovel::Variable( ty->getType(), constant( ty->getType() ) );
	assert( var );
	module->add( var );
	
	string* name = new string( "location_" + string( value.getName() ));
	libnovel::Function* func = new libnovel::Function( name->c_str() );
	assert( func );
	module->add( func );
	
	
	libnovel::SequentialScope* scope = new libnovel::SequentialScope();
	assert( scope );
	func->setContext( scope );
	
	libnovel::TrivialStatement* stmt = new libnovel::TrivialStatement( scope );
	libnovel::IdInstruction* id = new libnovel::IdInstruction( var );
	assert( id );

	
	// output parameter for intrinsic!
	libnovel::Reference* loc = new libnovel::Reference
   	( "location"
	, id->getType() // ASSUMTION: PPA: addresses stay in the 48-bit range!
	, func
	, false
	);
    assert( loc ); // PPA: CONTINUE HERE!!!
	
	libnovel::StoreInstruction* store = new libnovel::StoreInstruction( id, loc );
	assert( store );
	stmt->add( store );
	
	const std::vector< libcasm_ir::Type* >& params = value.getType()->getParameters();
	if( params.size() != 0 )
	{
		assert( !" unimplemented transformation for n-ary functions!" );
	}
	
	
	
	printf( "%s:%i: '%s'\n", __FILE__, __LINE__, value.getType()->getName() );
	
	reference[ &value ] = func;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Function& value )
{
}



void CasmIRToNovelPass::visit_prolog( libcasm_ir::Rule& value )
{
	string* name = new string( "rule_" + string( value.getName() ));
	
	
	libnovel::Component* comp = new libnovel::Component( name->c_str() );
	assert( comp );
	module->add( comp );

	reference[ &value ] = comp;
}
void CasmIRToNovelPass::visit_interlog( libcasm_ir::Rule& value )
{
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Rule& value )
{
	reference[ &value ] = 0;
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::ParallelBlock& value )
{
	libnovel::ParallelScope* scope = new libnovel::ParallelScope();
	assert( scope );

    libcasm_ir::ExecutionSemanticsBlock* parent = value.getParent();
	if( !parent )
	{
		libcasm_ir::Rule* rule = value.getBound();
		
		libnovel::Component* comp = (libnovel::Component*)(reference[rule]);
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
	
	// libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	// assert( parent );
	// libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	// assert( stmt );
	// stmt->add( call );
	
	reference[ &value ] = call;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::LocationInstruction& value )
{	
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::LookupInstruction& value )
{
	// TODO: FIXME: PPA: this lookup function has to be moved later into the 'run-time' implementation
	static libnovel::Function* lup = 0;
	if( !lup )
	{
		lup = new libnovel::Function( "lookup" );
		assert( lup );
		module->add( lup );

		libnovel::Reference* loc = new libnovel::Reference
		( "location"
		, &libnovel::TypeB64 // ASSUMTION: PPA: addresses stay in the 64-bit range!
		, lup
		);
		assert( loc );
		
		libnovel::SequentialScope* scope = new libnovel::SequentialScope();
		assert( scope );
		lup->setContext( scope );
	}
    
	assert( value.getValues().size() == 1 );
	
	libcasm_ir::Value* src = value.get();
	assert( libcasm_ir::Value::isa< libcasm_ir::LocationInstruction >( src ) );
	
	libnovel::Value* lookup_src = reference[ src ];
	assert( lookup_src );
	
	libnovel::CallInstruction* call = new libnovel::CallInstruction( lup );
	assert( call );
	call->add( lookup_src );
	
	libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	assert( parent );	
	libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	assert( stmt );
	stmt->add( call );
	
	reference[ &value ] = call;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::LookupInstruction& value )
{
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::UpdateInstruction& value )
{
	// TODO: FIXME: PPA: this lookup function has to be moved later into the 'run-time' implementation
	static libnovel::Function* upd = 0;
	if( !upd )
	{
		upd = new libnovel::Function( "update" );
		assert( upd );
		module->add( upd );

		libnovel::Reference* loc = new libnovel::Reference
		( "location"
		, &libnovel::TypeB64 // ASSUMTION: PPA: addresses stay in the 64-bit range!
		, upd
		);
		assert( loc );

		libnovel::Reference* val = new libnovel::Reference
		( "value"
		, &libnovel::TypeB64 // ASSUMTION: PPA: values are numbers only for now! later, dyn ptr. too for SW-emit only!
		, upd
		);
		assert( val );
		
		libnovel::SequentialScope* scope = new libnovel::SequentialScope();
		assert( scope );
		upd->setContext( scope );
	}
	
	assert( value.getValues().size() == 2 );
	
	libcasm_ir::Value* src = value.getValue(0);
	assert( libcasm_ir::Value::isa< libcasm_ir::LocationInstruction >( src ) );
	libnovel::Value* update_src = reference[ src ];
	assert( update_src );
	
	libcasm_ir::Value* val = value.getValue(1);
	assert( libcasm_ir::Value::isa< libcasm_ir::Instruction >( val ) );
	libnovel::Value* update_val = reference[ src ];
	assert( update_val );
	
	libnovel::CallInstruction* call = new libnovel::CallInstruction( upd );
	assert( call );
	call->add( update_src );
	call->add( update_val );
	
	libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	assert( parent );	
	libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	assert( stmt );
	stmt->add( call );

	reference[ &value ] = call;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::UpdateInstruction& value )
{
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::AddInstruction& value )
{
	// TODO: FIXME: PPA: this add function has to be moved later into the 'run-time' implementation
	static libnovel::Function* add = 0;
	if( !add )
	{
		add = new libnovel::Function( "add" );
		assert( add );
		module->add( add );
		
		libnovel::Reference* ra = new libnovel::Reference
		( "ra"
		, CasmRT_Integer->getType() // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, add
		);
		assert( ra );
	    
		libnovel::Reference* rb = new libnovel::Reference
		( "rb"
		, &libnovel::TypeStructure // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, add
		);
		assert( rb );

		libnovel::Reference* rt = new libnovel::Reference
		( "rt"
		, &libnovel::TypeStructure // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, add
		, false
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
	
	libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	assert( parent );	
	libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	assert( stmt );
	stmt->add( call );
	
	reference[ &value ] = call;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::AddInstruction& value )
{
	
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::DivInstruction& value )
{
	// TODO: FIXME: PPA: this div function has to be moved later into the 'run-time' implementation
	static libnovel::Function* div = 0;
	if( !div )
	{
		div = new libnovel::Function( "div" );
		assert( div );
		module->add( div );
		
		libnovel::Reference* ra = new libnovel::Reference
		( "ra"
		, &libnovel::TypeStructure // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, div
		);
		assert( ra );

		libnovel::Reference* rb = new libnovel::Reference
		( "rb"
		, &libnovel::TypeStructure // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, div
		);
		assert( rb );

		libnovel::Reference* rt = new libnovel::Reference
		( "rt"
		, &libnovel::TypeStructure // TODO: FIXME: this type has to be maybe changed in the future!!! 
		, div
		, false
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

	libcasm_ir::Value* parent = (libcasm_ir::Value*)value.getStatement();
	assert( parent );	
	libnovel::Statement* stmt = (libnovel::Statement*)reference[ parent ];
	assert( stmt );
	stmt->add( call );
	
	reference[ &value ] = call;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::DivInstruction& value )
{
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::AndInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::AndInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}


// CONSTANTS

void CasmIRToNovelPass::visit_prolog( libcasm_ir::IntegerConstant& value )
{
	libnovel::Value* val = libnovel::BitConstant::create( value.getValue(),  CasmRT_Integer->get(0)->getType()->getBitsize() );
	libnovel::Value* def = libnovel::BitConstant::create( value.isDefined(), CasmRT_Integer->get(1)->getType()->getBitsize() );
	assert( val );
	assert( def );

	libnovel::Value* const_int = libnovel::StructureConstant::create( CasmRT_Integer, { val, def } );
	
	module->add( const_int );
	reference[ &value ] = const_int;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::IntegerConstant& value )
{
	
}



//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  

