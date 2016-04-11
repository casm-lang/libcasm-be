#   
#   Copyright (c) 2016 Philipp Paulweber
#   All rights reserved.
#   
#   Developed by: Philipp Paulweber
#                 https://github.com/ppaulweber/libcasm-be
#   
#   This software is licensed under the Open Software License v. 3.0 (OSL-3.0).
#   You either find the license text below or in the root directory of this 
#   project in the LICENSE.txt file. If you cannot find the LICENSE.txt file,
#   please refer to https://opensource.org/licenses/OSL-3.0.
#   
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
#   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
#   CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
#   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
#   WITH THE SOFTWARE.
#   

AR=ar

CC=clang
CCFLAG += -std=c11
CCFLAG += -g -O0
CCFLAG += -Wall

CPP=clang
CPPFLAG += -std=c++11
CPPFLAG += -g -O0
CPPFLAG += -Wall
#CPPFLAG += -Wextra

TARGET += libcasm-be.a

CPPOBJECTS += obj/Backend.o
CPPOBJECTS += obj/LLCodeBackend.o
CPPOBJECTS += obj/CasmIRToLLCodePass.o

CPPOBJECTS += obj/CasmIRToNovelPass.o

INCLUDE += -I ./src
INCLUDE += -I ./src/analyze
INCLUDE += -I ./src/transform
INCLUDE += -I ../
INCLUDE += -I ../pass/src
INCLUDE += -I ../casm-fe/src
INCLUDE += -I ../casm-fe/build/src
INCLUDE += -I ../casm-ir/src
INCLUDE += -I ../casm-ir/src/analyze
INCLUDE += -I ../casm-ir/src/transform
INCLUDE += -I ../novel/src
INCLUDE += -I ../novel/src/analyze

default: obj $(TARGET)

obj:
	mkdir -p obj

obj/%.o: src/%.cpp
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

obj/%.o: src/analyze/%.cpp
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

obj/%.o: src/transform/%.cpp
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

$(TARGET): $(CPPOBJECTS)
	@echo "AR  " $@
	@$(AR) rsc $@ $(filter %.o,$^)
	@ranlib $@

clean:
	@echo "RM  " obj
	@rm -rf obj
	@echo "RM  " $(TARGET)
	@rm -f $(TARGET)
