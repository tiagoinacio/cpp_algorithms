# Copyright Louis Dionne 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

##############################################################################
# Setup custom functions, master targets and file lists for the unit tests
##############################################################################
add_custom_target(test.headers
  COMMENT "Build all the header-inclusion unit tests.")

add_custom_target(tests
  DEPENDS test.headers
  COMMENT "Build all the unit tests.")

#   cpp_algorithms_add_unit_test(<name> ...)
#
# Equivalent to `cpp_algorithms_add_test`, except the test is also added as a
# dependency of the `tests` target.
function(cpp_algorithms_add_unit_test name)
  cpp_algorithms_add_test(${ARGV})
  add_dependencies(tests ${name})
endfunction()

#   cpp_algorithms_add_header_test(<header-name>)
#
# Add a unit test for the public header file `header-name`, which must be a
# relative path from cpp_algorithms's include directory, e.g. `cpp_algorithms/cpp_algorithms.hpp`.
#
# This function creates an executable named `header.header-name` and a test
# of the same name. The only source file of the executable contains an empty
# `main` and it includes the `header-name` file. This is used to make sure
# that including any public header works properly. Also, the
# `header.header-name` target is made a dependency of the `headers` target.
function(cpp_algorithms_add_header_test header)
  string(REGEX REPLACE "/" "." _target "${header}")
  if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/header/${header}.cpp")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/header/${header}.cpp" "
            #include <${header}>
            int main() { return 0; }
        ")
  endif()
  add_executable(test.header.${_target} EXCLUDE_FROM_ALL
    "${CMAKE_CURRENT_BINARY_DIR}/header/${header}.cpp")
  cpp_algorithms_add_test(test.header.${_target}
    ${CMAKE_CURRENT_BINARY_DIR}/test.header.${_target})
  add_dependencies(test.headers test.header.${_target})
endfunction()

# A list of all the test files
file(GLOB_RECURSE CPP_ALGORITHMS_TEST_SOURCES "${cpp_algorithms_SOURCE_DIR}/test/*.cpp")

# A list of all the public headers
file(GLOB_RECURSE CPP_ALGORITHMS_PUBLIC_HEADERS "${cpp_algorithms_SOURCE_DIR}/include/*.hpp")


##############################################################################
# Include directories
##############################################################################
include_directories(${cpp_algorithms_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})

##############################################################################
# Generate tests that include each public header
##############################################################################
foreach(_header IN LISTS CPP_ALGORITHMS_PUBLIC_HEADERS)
  file(RELATIVE_PATH _relative "${cpp_algorithms_SOURCE_DIR}/include" "${_header}")
  cpp_algorithms_add_header_test("${_relative}")
endforeach()

##############################################################################
# Add all the unit tests
##############################################################################
foreach(_file IN LISTS CPP_ALGORITHMS_TEST_SOURCES)
  file(READ "${_file}" _contents)
  cpp_algorithms_target_name_for(_target "${_file}")

  add_executable(${_target} EXCLUDE_FROM_ALL "${_file}")
  cpp_algorithms_add_unit_test(${_target} ${CMAKE_CURRENT_BINARY_DIR}/${_target})
endforeach()