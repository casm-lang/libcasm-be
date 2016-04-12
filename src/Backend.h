//  
//  Copyright (c) 2016 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-be
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
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
		virtual void emit( FILE* f, libcasm_ir::BitConstant* ir ) = 0;
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

		virtual void emit( FILE* f, libcasm_ir::AssertInstruction* ir ) = 0;
		
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
