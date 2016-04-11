//  
//  Copyright (c) 2016 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-be
//  
//  This software is licensed under the Open Software License v. 3.0 (OSL-3.0).
//  You either find the license text below or in the root directory of this 
//  project in the LICENSE.txt file. If you cannot find the LICENSE.txt file,
//  please refer to https://opensource.org/licenses/OSL-3.0.
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
