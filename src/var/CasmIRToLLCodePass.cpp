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

#include "CasmIRToLLCodePass.h"

using namespace libcasm_be;

char CasmIRToLLCodePass::id = 0;

static libpass::PassRegistration< CasmIRToLLCodePass > PASS(
    "CASM IR to LLVM IR", "generates LLVM IR code of CASM IR", 0, 0 );

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

    libcasm_ir::Value::SymbolTable& symbols = *libcasm_ir::Value::getSymbols();

    const char* init_rule = 0;
    for( auto value : symbols[ ".agent" ] )
    {
        libcasm_ir::RulePointerConstant* rule_ptr =
            ( (libcasm_ir::Agent*)value )->getInitRulePointer();

        if( rule_ptr )
        {
            assert( rule_ptr->getValue() );
            assert( !init_rule );
            init_rule = rule_ptr->getValue()->getName();
        }
    }

    fprintf( output, "\n" );
    fprintf( output, "; constants\n" );

    for( auto value : symbols[ ".constant" ] )
    {
        // if( Value::isa< Constant >( value ) )
        // {
        // 	emit( output, value) ;
        // }
        // else
        if( libcasm_ir::Value::isa< libcasm_ir::AgentConstant >( value ) )
        {
            emit( output, ( (libcasm_ir::AgentConstant*)value ) );
        }
        else if( libcasm_ir::Value::isa< libcasm_ir::RulePointerConstant >( value ) )
        {
            emit( output, ( (libcasm_ir::RulePointerConstant*)value ) );
        }
        else if( libcasm_ir::Value::isa< libcasm_ir::BooleanConstant >( value ) )
        {
            emit( output, ( (libcasm_ir::BooleanConstant*)value ) );
        }
        else if( libcasm_ir::Value::isa< libcasm_ir::IntegerConstant >( value ) )
        {
            emit( output, ( (libcasm_ir::IntegerConstant*)value ) );
        }
        else if( libcasm_ir::Value::isa< libcasm_ir::BitConstant >( value ) )
        {
            emit( output, ( (libcasm_ir::BitConstant*)value ) );
        }
        else if( libcasm_ir::Value::isa< libcasm_ir::StringConstant >( value ) )
        {
            emit( output, ( (libcasm_ir::StringConstant*)value ) );
        }
        else if( libcasm_ir::Value::isa< libcasm_ir::Identifier >( value ) )
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

    for( auto value : symbols[ ".function" ] )
    {
        assert( libcasm_ir::Value::isa< libcasm_ir::Function >( value ) );
        emit( output, ( (libcasm_ir::Function*)value ) );
    }

    fprintf( output, "\n" );
    fprintf( output, "; derived expressions\n" );

    for( auto value : symbols[ ".derived" ] )
    {
        assert( libcasm_ir::Value::isa< libcasm_ir::Derived >( value ) );
        emit( output, ( (libcasm_ir::Derived*)value ) );
    }

    fprintf( output, "\n" );
    fprintf( output, "; rules\n" );

    for( auto value : symbols[ ".rule" ] )
    {
        assert( libcasm_ir::Value::isa< libcasm_ir::Rule >( value ) );
        emit( output, ( (libcasm_ir::Rule*)value ) );
    }

#define IND "  "
#define LF "\n"

    fprintf(
        output,
        // LF ""
        // LF "target datalayout = \"e-m:e-i64:64-f80:128-n8:16:32:64-S128\""
        // LF "target triple = \"x86_64-pc-linux-gnu\""
        // LF ""
        LF "define i8 @main( i32 %%args, i8** %%argv ) nounwind" LF "{" LF "begin:" LF IND
           "%%p = call i8* @program.location( i8* null )" LF IND
           "%%r = bitcast i8* %%p to %%libcasm-rt.Rule*" LF IND
           "call void @libcasm-rt.set.Rule.ptr"
           "( %%libcasm-rt.Rule* %%r, %%libcasm-rt.RuleAddr @%s )" LF IND
           "%%mem  = alloca %%stdll.mem" LF IND
           "call i8 @stdll.mem.new( %%stdll.mem* %%mem, i64 %u )" LF IND "" LF IND
           "call void @libcasm-rt.main( %%stdll.mem* %%mem )" LF IND
           "call i8 @stdll.mem.del( %%stdll.mem* %%mem )" LF IND "ret i8 0" LF "}" LF,
        init_rule,
        256000000 );

    return false;
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
