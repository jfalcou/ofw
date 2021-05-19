##==================================================================================================
##  OFW - One File Wonders
##  Copyright : OFW Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Compiler options
##==================================================================================================
add_library(ofw_test INTERFACE)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options( ofw_test INTERFACE /W3 /EHsc /std:c++latest)
else()
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options( ofw_test INTERFACE -std=c++20 -Werror -Wall -Wextra -Wno-gnu-string-literal-operator-template)
  else()
  target_compile_options( ofw_test INTERFACE -std=c++20 -Werror -Wall -Wextra)
  endif()
endif()

target_include_directories( ofw_test INTERFACE
                            ${tts_SOURCE_DIR}/include
                            ${PROJECT_SOURCE_DIR}/test
                            ${PROJECT_SOURCE_DIR}/include
                          )

##==================================================================================================
## Setup TTS
##==================================================================================================
set(TTS_BUILD_TEST    OFF CACHE INTERNAL "OFF")
set(TTS_IS_DEPENDENT  ON  CACHE INTERNAL "ON")

include(FetchContent)
FetchContent_Declare( tts
                      GIT_REPOSITORY https://github.com/jfalcou/tts.git
                      GIT_TAG develop
                    )

FetchContent_MakeAvailable(tts)

##==================================================================================================
## Make test
##==================================================================================================
function(generate_test root file)
  string(REPLACE ".cpp" ".exe" base ${file})
  string(REPLACE "/"    "." base ${base})
  string(REPLACE "\\"   "." base ${base})
  set(test "${root}.${base}")

  add_executable( ${test}  "${file}")
  target_link_libraries(${test} PUBLIC ofw_test)

  set_property( TARGET ${test}
                PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              )

  if (CMAKE_CROSSCOMPILING_CMD)
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND ${CMAKE_CROSSCOMPILING_CMD} $<TARGET_FILE:${test}> --no-color --pass
            )
  else()
    add_test( NAME ${test}
              WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/unit"
              COMMAND $<TARGET_FILE:${test}> --no-color --pass
            )
  endif()

  set_target_properties ( ${test} PROPERTIES
                          EXCLUDE_FROM_DEFAULT_BUILD TRUE
                          EXCLUDE_FROM_ALL TRUE
                          ${MAKE_UNIT_TARGET_PROPERTIES}
                        )

  target_include_directories( ${test}
                              PRIVATE
                              ${tts_SOURCE_DIR}/include
                              ${PROJECT_SOURCE_DIR}/test
                              ${PROJECT_SOURCE_DIR}/include
                            )

  add_dependencies(unit ${test})
endfunction()

add_custom_target(unit)

##==================================================================================================
## Actual tests
##==================================================================================================
add_subdirectory(kumi)
add_subdirectory(raberu)
