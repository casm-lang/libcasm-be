//  
//  Copyright (c) 2015-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-be
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

#ifndef _LIB_CASMBE_CASMIRTONOVELPASS_H_
#define _LIB_CASMBE_CASMIRTONOVELPASS_H_

#include "libpass.h"
#include "libcasm-be.all.h"
#include "libcasm-ir.all.h"
#include "libcasm-rt.h"
#include "libnovel.all.h"

/**
   @brief    TODO
   
   TODO
*/

namespace libcasm_be
{	
	class CasmIRToNovelPass : public libpass::Pass, public libcasm_ir::Visitor
	{
	private:
		libnovel::Module* module;
		
		std::unordered_map< libcasm_ir::Value*, libnovel::Value* > reference;
		
	public:
		static char id;
			
		virtual bool run( libpass::PassResult& pr );

		libnovel::Module* getModule( void ) const;

		LIB_CASMIR_VISITOR_INTERFACE;

	private:
		libnovel::Structure* factory ( libcasm_ir::Type* type );
		
		libnovel::Value* constant( libnovel::Type* type );
	};
}


#endif /* _LIB_CASMBE_CASMIRTONOVELPASS_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
