# Copyright (C) 2023 Dylibso.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

cmake_minimum_required (VERSION 3.14)

project (hermit-cli)

set (CMAKE_VERBOSE_MAKEFILE OFF)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif ()

#lower case needed for rust build path
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)

#set release flag by default for cargo build
set(CARGO_RELEASE_FLAG "--release")

#unset release flag if release mode wasn't specified
if(NOT CMAKE_BUILD_TYPE_LOWER STREQUAL "release")
    set(CARGO_RELEASE_FLAG "")
endif()

#unset logging flag by default for cargo build
set(CARGO_LOGGING_FLAG "")

#set logging flag if logging mode was specified
if(HERMIT_LOGGING_ON EQUAL 1)
    set(CARGO_LOGGING_FLAG "--features=logging")
endif()

set(cliwasmpath "${CMAKE_CURRENT_SOURCE_DIR}/target/wasm32-wasi/${CMAKE_BUILD_TYPE_LOWER}/hermitfile-parser.wasm")
set(cliwasmpath ${cliwasmpath} PARENT_SCOPE)
add_custom_command(OUTPUT ${cliwasmpath} COMMAND
  cargo build --target wasm32-wasi ${CARGO_RELEASE_FLAG} ${CARGO_LOGGING_FLAG}
  VERBATIM
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
add_custom_target(cli ALL DEPENDS ${cliwasmpath})
