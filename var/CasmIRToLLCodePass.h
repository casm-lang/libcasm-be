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

#ifndef _CASMIRTOLLCODEPASS_H_
#define _CASMIRTOLLCODEPASS_H_

#include "libcasm-be.h"
#include "libcasm-ir.h"
#include "libpass.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_be
{

    class CasmIRToLLCodePass : public libpass::Pass, public LLCodeBackend
    {
      public:
        static char id;

        virtual bool run( libpass::PassResult& pr );
    };
}

#endif /* _CASMIRTOLLCODEPASS_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
