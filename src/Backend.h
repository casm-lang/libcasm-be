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

#ifndef _LIB_CASMBE_BACKEND_H_
#define _LIB_CASMBE_BACKEND_H_

#include "libcasm-ir.h"

namespace libcasm_be
{
	class Backend
	{
    protected:
		void emit( FILE* f, libcasm_ir::Value* ir );
		void emit( FILE* f, libcasm_ir::ExecutionSemanticsBlock* ir );
		void emit( FILE* f, libcasm_ir::Statement* ir );
		
		virtual void emit( FILE* f, libcasm_ir::RulePointerConstant* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::AgentConstant* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::BooleanConstant* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::IntegerConstant* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::StringConstant* ir ) = 0;
		
		virtual void emit( FILE* f, libcasm_ir::Function* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::Derived* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::Rule* ir ) = 0;
	    
		virtual void emit( FILE* f, libcasm_ir::ParallelBlock*   ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::SequentialBlock* ir ) = 0;

		virtual void emit( FILE* f, libcasm_ir::TrivialStatement* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::BranchStatement* ir ) = 0;
		
		virtual void emit( FILE* f, libcasm_ir::BranchInstruction* ir ) = 0;

		virtual void emit( FILE* f, libcasm_ir::SwitchInstruction* ir ) = 0;
		
		virtual void emit( FILE* f, libcasm_ir::LocationInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::LookupInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::UpdateInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::CallInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::PrintInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::LetInstruction* ir ) = 0;		
		virtual void emit( FILE* f, libcasm_ir::AddInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::SubInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::MulInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::DivInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::RivInstruction* ir ) = 0;
		virtual void emit( FILE* f, libcasm_ir::ModInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::EquInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::NeqInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::LthInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::LeqInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::GthInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::GeqInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::OrInstruction*  ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::XorInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::AndInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::NotInstruction* ir ) = 0;
 		virtual void emit( FILE* f, libcasm_ir::MovInstruction* ir ) = 0;		
	};
}

#endif // _LIB_CASMBE_BACKEND_H_

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
