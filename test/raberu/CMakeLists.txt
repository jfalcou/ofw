##==================================================================================================
##  OFW - One File Wonders
##  Copyright : OFW Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(raberu.exe)

generate_test("raberu" "access.cpp")
generate_test("raberu" "concepts.cpp")
generate_test("raberu" "constraints.cpp")
generate_test("raberu" "contains.cpp")
generate_test("raberu" "get_type.cpp")
generate_test("raberu" "interface.cpp")
generate_test("raberu" "merge.cpp")
generate_test("raberu" "size.cpp")

add_dependencies(raberu.exe raberu.access.exe)
add_dependencies(raberu.exe raberu.concepts.exe)
add_dependencies(raberu.exe raberu.constraints.exe)
add_dependencies(raberu.exe raberu.contains.exe)
add_dependencies(raberu.exe raberu.get_type.exe)
add_dependencies(raberu.exe raberu.interface.exe)
add_dependencies(raberu.exe raberu.merge.exe)
add_dependencies(raberu.exe raberu.size.exe)
