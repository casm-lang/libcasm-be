#   
#   Copyright (c) 2016 Philipp Paulweber
#   All rights reserved.
#   
#   Developed by: Philipp Paulweber
#                 https://github.com/ppaulweber/libcasm-be
#   
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
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
INCLUDE += -I ../casm-fe/obj/src
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
