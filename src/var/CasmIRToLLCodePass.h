//
//  Copyright (C) 2015-2023 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-be/graphs/contributors>
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
    class CasmIRToLLCodePass
    : public libpass::Pass
    , public LLCodeBackend
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
