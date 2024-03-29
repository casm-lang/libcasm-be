#
#   Copyright (C) 2015-2024 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber et al.
#   <https://github.com/casm-lang/libcasm-be/graphs/contributors>
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

# LIBCASM_BE_FOUND        - system has found the package
# LIBCASM_BE_INCLUDE_DIRS - the package include directories
# LIBCASM_BE_LIBRARY      - the package library

include( LibPackage )

libfind_pkg_check_modules( LIBCASM_BE_PKGCONF libcasm-be )

find_path( LIBCASM_BE_INCLUDE_DIR
  NAMES libcasm-be/libcasm-be.h
  PATHS ${LIBCASM_BE_PKGCONF_INCLUDE_DIRS}
  )

find_library( LIBCASM_BE_LIBRARY
  NAMES libcasm-be casm-be
  PATHS ${LIBCASM_BE_PKGCONF_LIBRARY_DIRS}
  )

set( LIBCASM_BE_PROCESS_INCLUDES LIBCASM_BE_INCLUDE_DIR )
set( LIBCASM_BE_PROCESS_LIBS     LIBCASM_BE_LIBRARY )

libfind_process( LIBCASM_BE )

if( EXISTS "${LIBCASM_BE_INCLUDE_DIR}" AND
    EXISTS "${LIBCASM_BE_LIBRARY}" AND
    ${LIBCASM_BE_INCLUDE_DIR} AND
    ${LIBCASM_BE_LIBRARY}
    )
  set( LIBCASM_BE_FOUND TRUE PARENT_SCOPE )
else()
  set( LIBCASM_BE_FOUND FALSE PARENT_SCOPE )
endif()
