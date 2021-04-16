##==================================================================================================
##  OFW - One File Wonders
##  Copyright : OFW Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
cmake_minimum_required(VERSION 3.2)

##==================================================================================================
## Setup project
##==================================================================================================
project(ofw LANGUAGES CXX)
set(PROJECT_VERSION 0.1.0)
set(PROJECT_DOC_DIR   ${PROJECT_SOURCE_DIR}/doc)

##==================================================================================================
## No in-source build
##==================================================================================================
if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
  message(FATAL_ERROR "[ofw]: In-source build is not recommend")
endif()

##==================================================================================================
## Install target for people using FetchContent
##==================================================================================================
add_library(ofw_lib INTERFACE)
target_include_directories(ofw_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
target_compile_options( ofw_lib INTERFACE -Wno-gnu-string-literal-operator-template)
endif()

target_compile_features(ofw_lib INTERFACE cxx_std_20)
add_library(ofw::ofw ALIAS ofw_lib)

##==================================================================================================
## Options
##==================================================================================================
option( OFW_BUILD_TEST  "Build tests for ofw" ON )

##==================================================================================================
## Test target
##==================================================================================================
if( OFW_BUILD_TEST )
  include(CTest)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test/)
endif()
