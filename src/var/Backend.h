//
//  Copyright (C) 2015-2018 CASM Organization <https://casm-lang.org>
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

        virtual void emit( FILE* f, libcasm_ir::ParallelBlock* ir ) = 0;
        virtual void emit( FILE* f, libcasm_ir::SequentialBlock* ir ) = 0;

        virtual void emit( FILE* f, libcasm_ir::TrivialStatement* ir ) = 0;
        virtual void emit( FILE* f, libcasm_ir::BranchStatement* ir ) = 0;

        // virtual void emit( FILE* f, libcasm_ir::BranchInstruction* ir ) = 0;

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
        virtual void emit( FILE* f, libcasm_ir::OrInstruction* ir ) = 0;
        virtual void emit( FILE* f, libcasm_ir::XorInstruction* ir ) = 0;
        virtual void emit( FILE* f, libcasm_ir::AndInstruction* ir ) = 0;
        virtual void emit( FILE* f, libcasm_ir::NotInstruction* ir ) = 0;
        virtual void emit( FILE* f, libcasm_ir::MovInstruction* ir ) = 0;
    };
}

#endif  // _LIB_CASMBE_BACKEND_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
