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

#include "CasmIRToNovelPass.h"

using namespace libcasm_be;


char CasmIRToNovelPass::id = 0;

static libpass::PassRegistration< CasmIRToNovelPass > PASS
( "CASM IR to NOVEL IR"
, "generates a NOVEL instance of CASM IR"
, 0
, 0
);

static const char* default_output_name = "stdout";



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
	
	return false;
}

libnovel::Module* CasmIRToNovelPass::getModule( void ) const
{
	assert( module );
	return module;
}


#define DUMP_PREFIX  printf( "%-14s: %p, %s ", __FUNCTION__, &value, value.getName() )
#define DUMP_POSTFIX printf( "\n" );

void CasmIRToNovelPass::visit_prolog( libcasm_ir::Specification& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Specification& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::Agent& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Agent& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::Function& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Function& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::Rule& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_interlog( libcasm_ir::Rule& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::Rule& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}


void CasmIRToNovelPass::visit_prolog( libcasm_ir::ParallelBlock& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::ParallelBlock& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
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
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::TrivialStatement& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

		
void CasmIRToNovelPass::visit_prolog( libcasm_ir::LocationInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::LocationInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::LookupInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::LookupInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::UpdateInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::UpdateInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::AddInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::AddInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::DivInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::DivInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}

void CasmIRToNovelPass::visit_prolog( libcasm_ir::AndInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
}
void CasmIRToNovelPass::visit_epilog( libcasm_ir::AndInstruction& value )
{
	DUMP_PREFIX; DUMP_POSTFIX;
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

