#
#   Copyright (C) 2015-2018 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber
#                 <https://github.com/casm-lang/libcasm-be>
#
#   This file is part of libcasm-be.
#
#   libcasm-be is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   libcasm-be is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with libcasm-be. If not, see <http://www.gnu.org/licenses/>.
#
#   Additional permission under GNU GPL version 3 section 7
#
#   libcasm-be is distributed under the terms of the GNU General Public License
#   with the following clarification and special exception: Linking libcasm-be
#   statically or dynamically with other modules is making a combined work
#   based on libcasm-be. Thus, the terms and conditions of the GNU General
#   Public License cover the whole combination. As a special exception,
#   the copyright holders of libcasm-be give you permission to link libcasm-be
#   with independent modules to produce an executable, regardless of the
#   license terms of these independent modules, and to copy and distribute
#   the resulting executable under terms of your choice, provided that you
#   also meet, for each linked independent module, the terms and conditions
#   of the license of that module. An independent module is a module which
#   is not derived from or based on libcasm-be. If you modify libcasm-be, you
#   may extend this exception to your version of the library, but you are
#   not obliged to do so. If you do not wish to do so, delete this exception
#   statement from your version.
#

cmake_minimum_required( VERSION 3.1 )

if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../gtest" )
  set( LIBS .. )
else()
  set( LIBS lib )
endif()

foreach( DEPENDENCY
    stdhl
    pass
    cjel-ir
    casm-ir
    casm-rt
    )
  if( NOT TARGET ${DEPENDENCY} )
    add_subdirectory( ${LIBS}/${DEPENDENCY} lib/${DEPENDENCY} )
  endif()  
endforeach()


file( GLOB_RECURSE CXX_SRC_FILES "src/*.cpp" )
file( GLOB_RECURSE CXX_UTS_FILES "uts/*.cpp" )


set( TARGET casm-be )
project( ${TARGET} )


include_directories(
  .
  src
  ${LIBS}/gtest/googletest
  ${LIBS}/gtest/googletest/include
  ${LIBS}/hayai/src
  ${LIBS}/stdhl
  ${LIBS}/pass
  ${LIBS}/cjel-ir
  ${LIBS}/casm-ir
  ${LIBS}/casm-rt
)


set( CMAKE_CXX_FLAGS          "${CMAKE_CXX_FLAGS}          -std=c++11 -Wall" )

set( CMAKE_CXX_FLAGS_DEBUG    "${CMAKE_CXX_FLAGS_DEBUG}    -O0" )
set( CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE}  -O3" )
set( CMAKE_CXX_FLAGS_SANITIZE "${CMAKE_CXX_FLAGS_SANITIZE} -O1 -Wextra -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=undefined -fsanitize=address" )


add_library( ${TARGET} STATIC
  ${CXX_SRC_FILES}
)


add_library( ${TARGET}-test OBJECT
  ${CXX_UTS_FILES}
)

add_executable( ${TARGET}-check
  ${LIBS}/gtest/googletest/src/gtest_main.cc
  ${LIBS}/gtest/googletest/src/gtest-all.cc
  $<TARGET_OBJECTS:${TARGET}-test>
)

target_link_libraries( ${TARGET}-check
  ${TARGET}
  casm-rt
  casm-ir
  cjel-ir
  pass
  stdhl
  pthread
)


add_library( ${TARGET}-benchmark OBJECT
  uts/main.cpp
)

add_executable( ${TARGET}-run
  ${LIBS}/hayai/src/hayai_posix_main.cpp
  ${LIBS}/gtest/googletest/src/gtest-all.cc
  $<TARGET_OBJECTS:${TARGET}-benchmark>
)

target_link_libraries( ${TARGET}-run
  ${TARGET}
  casm-rt
  casm-ir
  cjel-ir
  pass
  stdhl
  pthread
)


if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build : debug sanitize release."
    FORCE
  )
endif( NOT CMAKE_BUILD_TYPE )


message( "* ${CMAKE_BUILD_TYPE} : ${TARGET} : ${LIBS}" )
