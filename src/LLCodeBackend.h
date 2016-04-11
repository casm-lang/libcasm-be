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

#ifndef _LIB_CASMBE_LLCODEBACKED_H_
#define _LIB_CASMBE_LLCODEBACKED_H_

#include "Backend.h"

namespace libcasm_be
{
	class LLCodeBackend : public Backend
	{
	private:
		u64 register_count;
		u64 label_count;
		u1 derived_mode;
		
		std::unordered_map< libcasm_ir::Value*, std::string > register_cache;
		const char* getRegister( libcasm_ir::Value* value, u1 let_flag = false );

		void lifetime_start( FILE* f, libcasm_ir::Instruction* ir );
		void lifetime_end( FILE* f, libcasm_ir::Instruction* ir );
		
		void emit_constant( FILE* f, libcasm_ir::Value* ir, const char* ty, const char* val,u1 def );
		void emit_scope( FILE* f, libcasm_ir::ExecutionSemanticsBlock* ir );
		void emit_statement( FILE* f, libcasm_ir::Statement* ir );
		void emit_instruction( FILE* f, libcasm_ir::Instruction* ir, const char* alias );

	protected:
		virtual void emit( FILE* f, libcasm_ir::AgentConstant* ir );
		virtual void emit( FILE* f, libcasm_ir::RulePointerConstant* ir );
		virtual void emit( FILE* f, libcasm_ir::BooleanConstant* ir );
		virtual void emit( FILE* f, libcasm_ir::IntegerConstant* ir );
		virtual void emit( FILE* f, libcasm_ir::BitConstant* ir );
		virtual void emit( FILE* f, libcasm_ir::StringConstant* ir );
		
		virtual void emit( FILE* f, libcasm_ir::Function* ir );
		virtual void emit( FILE* f, libcasm_ir::Derived* ir );
		virtual void emit( FILE* f, libcasm_ir::Rule* ir );
		
		virtual void emit( FILE* f, libcasm_ir::ParallelBlock*   ir );
		virtual void emit( FILE* f, libcasm_ir::SequentialBlock* ir );
		
		virtual void emit( FILE* f, libcasm_ir::TrivialStatement* ir );
		virtual void emit( FILE* f, libcasm_ir::BranchStatement* ir );
		
		virtual void emit( FILE* f, libcasm_ir::BranchInstruction* ir );

		virtual void emit( FILE* f, libcasm_ir::SwitchInstruction* ir );
		
		virtual void emit( FILE* f, libcasm_ir::LocationInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::LookupInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::UpdateInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::CallInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::PrintInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::LetInstruction* ir );

		virtual void emit( FILE* f, libcasm_ir::AssertInstruction* ir );
		
		virtual void emit( FILE* f, libcasm_ir::AddInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::SubInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::MulInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::DivInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::RivInstruction* ir );
		virtual void emit( FILE* f, libcasm_ir::ModInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::EquInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::NeqInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::LthInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::LeqInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::GthInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::GeqInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::OrInstruction*  ir );
 		virtual void emit( FILE* f, libcasm_ir::XorInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::AndInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::NotInstruction* ir );
 		virtual void emit( FILE* f, libcasm_ir::MovInstruction* ir );
	};
}

#endif // _LIB_CASMBE_LLCODEBACKED_H_

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
