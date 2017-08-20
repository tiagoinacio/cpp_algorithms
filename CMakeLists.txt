# Copyright Louis Dionne 2015
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

##############################################################################
# Setup project
##############################################################################
project(cpp_algorithms CXX)
cmake_minimum_required(VERSION 3.0)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
enable_testing()


##############################################################################
# Setup CMake options
##############################################################################
include(CMakeDependentOption)
option(CPP_ALGORITHMS_ENABLE_VALGRIND "Run the unit tests and examples under Valgrind if it is found." OFF)
option(CPP_ALGORITHMS_ENABLE_ASAN "Run the unit tests and examples using AddressSanitizer." OFF)
option(CPP_ALGORITHMS_ENABLE_COVERAGE "Run the unit tests and examples with code coverage instrumentation." OFF)
option(CPP_ALGORITHMS_ENABLE_WERROR "Fail and stop if a warning is triggered." OFF)
option(CPP_ALGORITHMS_ENABLE_DEBUG_INFORMATION "Includes debug information in the binaries." OFF)
option(CPP_ALGORITHMS_ENABLE_ASSERTIONS "Enables assertions." OFF)

##############################################################################
# Setup compiler flags (more can be set on a per-target basis or in subdirectories)
##############################################################################
# Compiler flags:
include(CheckCXXCompilerFlag)
macro(cpp_algorithms_append_flag testname flag)
    check_cxx_compiler_flag(${flag} ${testname})
    if (${testname})
        add_compile_options(${flag})
    endif()
endmacro()

# Language flag: version of the C++ standard to use
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_STDCXX14 -std=c++14)

# PITA warning flags:
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WSHADOW -Wshadow)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNUSED -Wunused)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNUSED_FUNCTION -Wunused-function)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNUSED_LABEL -Wunused-label)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNUSED_PARAMETER -Wunused-parameter)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNUSED_VALUE -Wunused-value)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNUSED_VARIABLE -Wunused-variable)

# Warning flags:
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WALL -Wall)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WEXTRA -Wextra)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WDEPRECATED -Wdeprecated)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WDOCUMENTATION -Wdocumentation)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WCOMMENT -Wcomment)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_PEDANTIC -Wpedantic)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WSTACK_PROTECTOR -Wstack-protector)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WSTRICT_ALIASING "-Wstrict-aliasing=2")
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WSTRICT_OVERFLOW "-Wstrict-overflow=5")
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WDISABLED_OPTIMIZATION -Wdisabled-optimization)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WINLINE -Winline)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WRETURN_TYPE -Wreturn-type)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WCAST_ALIGN -Wcast-align)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WCAST_QUAL -Wcast-qual)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WSIGN_COMPARE -Wsign-compare)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WSIGN_PROMO -Wsign-promo)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WFORMAT "-Wformat=2")
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WFORMAT_NONLITERAL -Wformat-nonliteral)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WFORMAT_SECURITY -Wformat-security)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WFORMAT_Y2K -Wformat-y2k)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WMISSING_BRACES -Wmissing-braces)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WMISSING_FIELD_INITIALIZERS -Wmissing-field-initializers)
#cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WMISSING_INCLUDE_DIRS -Wmissing-include-dirs)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WOVERLOADED_VIRTUAL -Woverloaded-virtual)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WCHAR_SUBSCRIPTS -Wchar-subscripts)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WFLOAT_EQUAL -Wfloat-equal)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WPOINTER_ARITH -Wpointer-arith)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WINVALID_PCH -Winvalid-pch)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WIMPORT -Wimport)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WINIT_SELF -Winit-self)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WREDUNDANT_DECLS -Wredundant-decls)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WPACKED -Wpacked)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WPARENTHESES -Wparentheses)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WSEQUENCE_POINT -Wsequence-point)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WSWITCH -Wswitch)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WSWITCH_DEFAULT -Wswitch-default)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WTRIGRAPHS -Wtrigraphs)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNINITIALIZED -Wuninitialized)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNKNOWN_PRAGMAS -Wunknown-pragmas)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNREACHABLE_CODE -Wunreachable-code)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WVARIADIC_MACROS -Wvariadic-macros)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WVOLATILE_REGISTER_VAR -Wvolatile-register-var)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WWRITE_STRINGS -Wwrite-strings)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WNO_ATTRIBUTES -Wno-attributes)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WUNNEEDED_INTERNAL_DECLARATION -Wunneeded-internal-declaration)

# Template diagnostic flags
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_FDIAGNOSTIC_SHOW_TEMPLATE_TREE -fdiagnostics-show-template-tree)
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_FTEMPLATE_BACKTRACE_LIMIT "-ftemplate-backtrace-limit=0")
cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS___EXTERN_ALWAYS_INLINE -D__extern_always_inline=inline)

# Compiler flags controlled by CMake options above
if (CPP_ALGORITHMS_ENABLE_WERROR)
    cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WERROR -Werror)
    cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_WX -WX)
  endif()

if (CPP_ALGORITHMS_ENABLE_ASAN)
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_SANITIZE "-fsanitize=address,integer,undefined,leak")
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_NO_OMIT_FRAME_POINTER -fno-omit-frame-pointer)
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_NO_SANITIZE "-fno-sanitize=unsigned-integer-overflow")
else()
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_OMIT_FRAME_POINTER -fomit-frame-pointer)
endif()

if (CPP_ALGORITHMS_ENABLE_DEBUG_INFORMATION)
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_G3 -g3)
else()
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_G0 -g0)
endif()

if (NOT CPP_ALGORITHMS_ENABLE_ASSERTIONS)
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_NDEBUG -DNDEBUG)
endif()

if (CPP_ALGORITHMS_ENABLE_COVERAGE)
  if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(FATAL_ERROR "code coverage instrumentation requires CMAKE_BUILD_TYPE=Debug")
  endif()
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

# Optimization flags: debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_O0 -O0)
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_NO_INLINE -fno-inline)
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_STACK_PROTECTOR_ALL -fstack-protector-all)
endif()

# Optimization flags: release
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_OFAST -Ofast)
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_MARCH_NATIVE "-march=native")
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_MTUNE_NATIVE "-mtune=native")
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_STRICT_ALIASING "-fstrict-aliasing")
  cpp_algorithms_append_flag(CPP_ALGORITHMS_HAS_VECTORIZE "-fvectorize")
  # Others could be: -pipe pfdata-sections -ffunction-sections
  # for clang: -mllvm -inline-threshold=X (X=1000, 10000, ...)
endif()

##############################################################################
# Search for packages.
#
# Behavior when the package is found or not is customized at the
# point where the package is required.
##############################################################################

# Git: parses current project commit
find_package(Git)
if (GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
    OUTPUT_VARIABLE CPP_ALGORITHMS_CURRENT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# Doxygen
find_package(Doxygen)

# Valgrid
if (CPP_ALGORITHMS_ENABLE_VALGRIND)
  find_program(MEMORYCHECK_COMMAND valgrind)
  if(MEMORYCHECK_COMMAND-NOTFOUND)
    message(FATAL_ERROR "valgrind not found")
  endif()
  set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
  include(Dart)
endif()

#find_package(Boost)

# find_package(Meta)
# find_package(MPL11)
# find_package(PythonInterp 2.7)
# find_package(Ruby 2.1)


# if (NOT ${Boost_FOUND})
#     message(WARNING
#         "The Boost library headers were not found; targets depending "
#         "on Boost won't be available.")
# endif()



##############################################################################
# Setup the URL to the official repository on GitHub.
#
# If there is a GITHUB_TOKEN environment variable, we assume this token allows
# us to push to the GitHub repository and we use that in the URL. This token
# will give us push access for updating the 'gh-pages' branch and doing other
# useful things e.g. from Travis. Otherwise, if there's no such environment
# variable, the URL just refers to the GitHub repository without authentication.
# In this case, we'll be asked for our username and password when/if we try to
# push to the repository.
##############################################################################
#if (DEFINED ENV{GITHUB_TOKEN})
#  set(CPP_ALGORITHMS_ORIGIN_URL "https://github_user:$ENV{GITHUB_TOKEN}@github.com/github_user/cpp_algorithms")
#else()
#  set(CPP_ALGORITHMS_ORIGIN_URL "https://github.com/github_user/cpp_algorithms")
#endif()

if (DEFINED ENV{GITHUB_TOKEN})
  set(CPP_ALGORITHMS_ORIGIN_URL "https://gnzlbg:$ENV{GITHUB_TOKEN}@github.com/gnzlbg/cpp_algorithms")
else()
  set(CPP_ALGORITHMS_ORIGIN_URL "https://github.com/gnzlbg/cpp_algorithms")
endif()


##############################################################################
# Setup custom functions to ease the creation of targets
##############################################################################
#   cpp_algorithms_target_name_for(<output variable> <source file> [ext])
#
# Return the target name associated to a source file. If the path of the
# source file relative from the root of cpp_algorithms is `path/to/source/file.ext`,
# the target name associated to it will be `path.to.source.file`.
#
# The extension of the file should be specified as a last argument. If no
# extension is specified, the `.cpp` extension is assumed.
function(cpp_algorithms_target_name_for out file)
    if (NOT ARGV2)
        set(_extension ".cpp")
    else()
        set(_extension "${ARGV2}")
    endif()

    file(RELATIVE_PATH _relative ${cpp_algorithms_SOURCE_DIR} ${file})
    string(REPLACE "${_extension}" "" _name ${_relative})
    string(REGEX REPLACE "/" "." _name ${_name})
    set(${out} "${_name}" PARENT_SCOPE)
endfunction()

#   cpp_algorithms_add_test(<name> <command> [<arg>...])
#
# Creates a test called `name`, which runs the given `command` with the given
# `arg`uments.
function(cpp_algorithms_add_test name)
  add_test(${name} ${ARGN})
endfunction()

#   cpp_algorithms_list_remove_glob(<list> <GLOB|GLOB_RECURSE> [globbing expressions]...)
#
# Generates a list of files matching the given glob expressions, and remove
# the matched elements from the given <list>.
macro(cpp_algorithms_list_remove_glob list glob)
    file(${glob} _bhlrg10321023_avoid_macro_clash_matches ${ARGN})
    list(REMOVE_ITEM ${list} ${_bhlrg10321023_avoid_macro_clash_matches})
endmacro()


##############################################################################
# Setup subdirectories
##############################################################################
#add_subdirectory(benchmark)
add_subdirectory(site)
add_subdirectory(example)
add_subdirectory(test)


##############################################################################
# Setup the `check` target to build and then run all the tests and examples.
##############################################################################
add_custom_target(check ALL
    COMMAND ${CMAKE_CTEST_COMMAND} --VV #--output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS tests examples
    COMMENT "Build and then run all the tests and examples.")

