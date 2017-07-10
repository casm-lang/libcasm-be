//
//  Copyright (c) 2015-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                https://github.com/casm-lang/libcasm-be
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

#ifndef _LIB_CASMBE_CASM_IR_TO_CJEL_IR_PASS_H_
#define _LIB_CASMBE_CASM_IR_TO_CJEL_IR_PASS_H_

#include "../casm-ir/src/analyze/ConsistencyCheckPass.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_be
{
    class CasmIRToCjelIRPass final : public libpass::Pass
    {
      public:
        static char id;

        void usage( libpass::PassUsage& pu ) override;
        
        u1 run( libpass::PassResult& pr ) override;

        using Data = libcasm_ir::ConsistencyCheckPass;
    };
}

#endif // _LIB_CASMBE_CASM_IR_TO_CJEL_IR_PASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
