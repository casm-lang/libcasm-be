//
//  Copyright (C) 2015-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                <https://github.com/casm-lang/libcasm-be>
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

        void emit_constant(
            FILE* f, libcasm_ir::Value* ir, const char* ty, const char* val, u1 def );
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

        virtual void emit( FILE* f, libcasm_ir::ParallelBlock* ir );
        virtual void emit( FILE* f, libcasm_ir::SequentialBlock* ir );

        virtual void emit( FILE* f, libcasm_ir::TrivialStatement* ir );
        virtual void emit( FILE* f, libcasm_ir::BranchStatement* ir );

        // virtual void emit( FILE* f, libcasm_ir::BranchInstruction* ir );

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
        virtual void emit( FILE* f, libcasm_ir::OrInstruction* ir );
        virtual void emit( FILE* f, libcasm_ir::XorInstruction* ir );
        virtual void emit( FILE* f, libcasm_ir::AndInstruction* ir );
        virtual void emit( FILE* f, libcasm_ir::NotInstruction* ir );
        virtual void emit( FILE* f, libcasm_ir::MovInstruction* ir );
    };
}

#endif  // _LIB_CASMBE_LLCODEBACKED_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
