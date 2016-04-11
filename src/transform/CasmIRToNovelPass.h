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
