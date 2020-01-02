//
//  Copyright (C) 2015-2020 CASM Organization <https://casm-lang.org>
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

#include "Backend.h"

using namespace libcasm_ir;
using namespace libcasm_be;

void Backend::emit( FILE* f, Value* ir )
{
    switch( ir->getValueID() )
    {
        case Value::PARALLEL_BLOCK:
            emit( f, ( (ParallelBlock*)ir ) );
            break;
        case Value::SEQUENTIAL_BLOCK:
            emit( f, ( (SequentialBlock*)ir ) );
            break;
        case Value::TRIVIAL_STATEMENT:
            emit( f, ( (TrivialStatement*)ir ) );
            break;
        case Value::BRANCH_STATEMENT:
            emit( f, ( (BranchStatement*)ir ) );
            break;

        case Value::LOCATION_INSTRUCTION:
            emit( f, ( (LocationInstruction*)ir ) );
            break;
        case Value::LOOKUP_INSTRUCTION:
            emit( f, ( (LookupInstruction*)ir ) );
            break;
        case Value::UPDATE_INSTRUCTION:
            emit( f, ( (UpdateInstruction*)ir ) );
            break;
        case Value::PRINT_INSTRUCTION:
            emit( f, ( (PrintInstruction*)ir ) );
            break;
        case Value::CALL_INSTRUCTION:
            emit( f, ( (CallInstruction*)ir ) );
            break;
        case Value::LOCAL_INSTRUCTION:
            emit( f, ( (LetInstruction*)ir ) );
            break;

        case Value::ASSERT_INSTRUCTION:
            emit( f, ( (AssertInstruction*)ir ) );
            break;

            // case Value::BRANCH_INSTRUCTION:
            //     emit( f, ( (BranchInstruction*)ir ) );
            //     break;

        case Value::SKIP_INSTRUCTION: /*nop*/
            break;
        case Value::SWITCH_INSTRUCTION:
            emit( f, ( (SwitchInstruction*)ir ) );
            break;

        case Value::ADD_INSTRUCTION:
            emit( f, ( (AddInstruction*)ir ) );
            break;
        case Value::SUB_INSTRUCTION:
            emit( f, ( (SubInstruction*)ir ) );
            break;
        case Value::MUL_INSTRUCTION:
            emit( f, ( (MulInstruction*)ir ) );
            break;
        case Value::DIV_INSTRUCTION:
            emit( f, ( (DivInstruction*)ir ) );
            break;
        case Value::RIV_INSTRUCTION:
            emit( f, ( (RivInstruction*)ir ) );
            break;
        case Value::MOD_INSTRUCTION:
            emit( f, ( (ModInstruction*)ir ) );
            break;
        case Value::EQU_INSTRUCTION:
            emit( f, ( (EquInstruction*)ir ) );
            break;
        case Value::NEQ_INSTRUCTION:
            emit( f, ( (NeqInstruction*)ir ) );
            break;
        case Value::LTH_INSTRUCTION:
            emit( f, ( (LthInstruction*)ir ) );
            break;
        case Value::LEQ_INSTRUCTION:
            emit( f, ( (LeqInstruction*)ir ) );
            break;
        case Value::GTH_INSTRUCTION:
            emit( f, ( (GthInstruction*)ir ) );
            break;
        case Value::GEQ_INSTRUCTION:
            emit( f, ( (GeqInstruction*)ir ) );
            break;
        case Value::XOR_INSTRUCTION:
            emit( f, ( (XorInstruction*)ir ) );
            break;
        case Value::OR_INSTRUCTION:
            emit( f, ( (OrInstruction*)ir ) );
            break;
        case Value::AND_INSTRUCTION:
            emit( f, ( (AndInstruction*)ir ) );
            break;
        case Value::NOT_INSTRUCTION:
            emit( f, ( (NotInstruction*)ir ) );
            break;
        case Value::MOV_INSTRUCTION:
            emit( f, ( (MovInstruction*)ir ) );
            break;

        case Value::RULE_POINTER_CONSTANT:
            emit( f, ( (RulePointerConstant*)ir ) );
            break;
        case Value::AGENT_CONSTANT:
            emit( f, ( (AgentConstant*)ir ) );
            break;
        case Value::BOOLEAN_CONSTANT:
            emit( f, ( (BooleanConstant*)ir ) );
            break;
        case Value::INTEGER_CONSTANT:
            emit( f, ( (IntegerConstant*)ir ) );
            break;
        case Value::BIT_CONSTANT:
            emit( f, ( (BitConstant*)ir ) );
            break;
        case Value::STRING_CONSTANT:
            emit( f, ( (StringConstant*)ir ) );
            break;

        default:
        {
            printf( "%s:%i: %s: %u\n", __FILE__, __LINE__, __FUNCTION__, ir->getValueID() );
            ir->dump();
            assert( 0 && "unimplemented value to distribute an emit!" );
        }
    }
};

void Backend::emit( FILE* f, ExecutionSemanticsBlock* ir )
{
    assert( Value::isa< ExecutionSemanticsBlock >( ir ) );

    for( auto value : ir->getBlocks() )
    {
        emit( f, ( (Value*)value ) );
    }
}

void Backend::emit( FILE* f, Statement* ir )
{
    assert( Value::isa< Statement >( ir ) );

    for( auto value : ir->getInstructions() )
    {
        emit( f, ( (Value*)value ) );
    }
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
