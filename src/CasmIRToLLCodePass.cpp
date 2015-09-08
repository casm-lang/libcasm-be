//  
//  Copyright (c) 2015 Philipp Paulweber
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

#include "CasmIRToLLCodePass.h"

using namespace libcasm_ir;
using namespace libcasm_be;


char CasmIRToLLCodePass::id = 0;

static libpass::PassRegistration< CasmIRToLLCodePass > PASS
( "CASM IR to LLVM IR"
, "generates LLVM IR code of CASM IR"
, 0
, 0
);

static const char* default_output_name = "stdout";



bool CasmIRToLLCodePass::run( libpass::PassResult& pr )
{
	// AstNode* node = (AstNode*)pr.getResult< TypeCheckPass >();
	
	const char* output_name = (const char*)pr.getResults()[ (void*)1 ];
	
	FILE* output = stdout;
	if( !output_name )
	{
		output_name = default_output_name;
	}
	else
	{
		output = fopen( output_name, "w" );
	}
	
	printf( "%s:%i: [%s] '%s'\n", __FILE__, __LINE__, __FUNCTION__, output_name );
	
	
	Value::SymbolTable& symbols = *Value::getSymbols();

	const char* init_rule = 0;
	for( auto value : symbols[".agent"] )
	{
		RulePointerConstant* rule_ptr = ((Agent*)value)->getInitRulePointer();
		
		if( rule_ptr )
		{
			assert( rule_ptr->getValue() );
			assert( !init_rule );
			init_rule = rule_ptr->getValue()->getName();
		}
	}
	
	
	fprintf( output, "\n" );
	fprintf( output, "; constants\n" );
	
	for( auto value : symbols[".constant"] )
	{
		if( Value::isa< AgentConstant >( value ) )
		{
			emit( output, ((AgentConstant*)value) );
		}
		else if( Value::isa< RulePointerConstant >( value ) )
		{
			emit( output, ((RulePointerConstant*)value) );
		}
		else if( Value::isa< BooleanConstant >( value ) )
		{
			emit( output, ((BooleanConstant*)value) );
		}
		else if( Value::isa< IntegerConstant >( value ) )
		{
			emit( output, ((IntegerConstant*)value) );
		}
		else if( Value::isa< StringConstant >( value ) )
		{
			emit( output, ((StringConstant*)value) );
		}
		else if( Value::isa< Identifier >( value ) )
		{
		    continue;
		}
		else
		{
			assert( 0 );
		}
	}
	
	fprintf( output, "\n" );
	fprintf( output, "; functions\n" );

	for( auto value : symbols[".function"] )
	{
		assert( Value::isa< Function >( value ) );		
		emit( output, ((Function*)value) );
	}
	
	fprintf( output, "\n" );
	fprintf( output, "; derived expressions\n" );
	
	for( auto value : symbols[".derived"] )
	{
		assert( Value::isa< Derived >( value ) );		
		emit( output, ((Derived*)value) );		
	}
	
	fprintf( output, "\n" );
	fprintf( output, "; rules\n" );
	
	for( auto value : symbols[".rule"] )
	{
		assert( Value::isa< Rule >( value ) );		
		emit( output, ((Rule*)value) );		
	}

#define IND "  "
#define LF "\n"
	
	fprintf( output,
			 // LF ""
			 // LF "target datalayout = \"e-m:e-i64:64-f80:128-n8:16:32:64-S128\""
			 // LF "target triple = \"x86_64-pc-linux-gnu\""
			 // LF ""
			 LF "define i8 @main( i32 %%args, i8** %%argv ) nounwind"
			 LF "{"
			 LF "begin:"
			 LF IND "%%p = call i8* @program.location( i8* null )"
			 LF IND "%%r = bitcast i8* %%p to %%libcasm-rt.Rule*"
			 LF IND "call void @libcasm-rt.set.Rule.ptr"
			        "( %%libcasm-rt.Rule* %%r, %%libcasm-rt.RuleAddr @%s )"			 
			 LF IND "%%mem  = alloca %%stdll.mem"
			 LF IND "call i8 @stdll.mem.new( %%stdll.mem* %%mem, i64 %u )"
			 LF IND ""
			 LF IND "call void @libcasm-rt.main( %%stdll.mem* %%mem )"
			 LF IND "call i8 @stdll.mem.del( %%stdll.mem* %%mem )"
			 LF IND "ret i8 0"
			 LF "}"
			 LF
			 , init_rule, 256000000
		);
	
	return false;
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

