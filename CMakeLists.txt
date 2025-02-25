cmake_minimum_required(VERSION 3.28)
project(cpp_gtest_extension
    LANGUAGES C CXX
)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UC)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT (CMAKE_C_COMPILER_ID STREQUAL CMAKE_CXX_COMPILER_ID))
    message(FATAL_ERROR "CMAKE_C_COMPILER_ID (${CMAKE_C_COMPILER_ID}) expected to be identical to CMAKE_CXX_COMPILER_ID (${CMAKE_CXX_COMPILER_ID})")
endif()

message(STATUS "CMAKE_C_COMPILER_ID: ${CMAKE_C_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

file(TO_CMAKE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" MY_CMAKE_SCRIPTS_DIR)
set(CMAKE_MODULE_PATH "${MY_CMAKE_SCRIPTS_DIR}" ${CMAKE_MODULE_PATH})

include(utils)
include(fetch_content_wrapper)
cmake_language(CALL ${PROJECT_NAME}_init_fetch_content_wrapper)

cmake_language(CALL ${PROJECT_NAME}_set_compiler_flags)
if(NOT DEFINED SANITIZED_BUILD)
    message(FATAL_ERROR "SANITIZED_BUILD must be set to either TRUE or FALSE")
endif()
message(STATUS "SANITIZED_BUILD: ${SANITIZED_BUILD}")
if(SANITIZED_BUILD)
    cmake_language(CALL ${PROJECT_NAME}_enable_sanitizers)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(${PROJECT_NAME_UC}_ENABLE_COVERAGE ON)
    cmake_language(CALL ${PROJECT_NAME}_delete_gcda_files)
else ()
    set(${PROJECT_NAME_UC}_ENABLE_COVERAGE OFF)
endif()

include(CTest)

add_subdirectory(src)
