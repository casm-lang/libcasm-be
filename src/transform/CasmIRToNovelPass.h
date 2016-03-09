//  
//  Copyright (c) 2015 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-be
//  
//  Permission is hereby granted, free of charge, to any person obtaining a 
//  copy of this software and associated documentation files (the "Software"), 
//  to deal with the Software without restriction, including without limitation 
//  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//  and/or sell copies of the Software, and to permit persons to whom the 
//  Software is furnished to do so, subject to the following conditions:
//  
//  * Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimers.
//  
//  * Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimers in the 
//    documentation and/or other materials provided with the distribution.
//  
//  * Neither the names of the copyright holders, nor the names of its 
//    contributors may be used to endorse or promote products derived from 
//    this Software without specific prior written permission.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
//  CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//  WITH THE SOFTWARE.
//  

#ifndef _LIB_CASMBE_CASM_IR_TO_NOVEL_PASS_H_
#define _LIB_CASMBE_CASM_IR_TO_NOVEL_PASS_H_

#include "Pass.h"

#include "libcasm-ir.h"
#include "libcasm-be.h"
#include "libnovel.h"

#include "CasmIRDumpPass.h"
#include "NovelDumpPass.h"

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


#endif /* _LIB_CASMBE_CASM_IR_TO_NOVEL_PASS_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  