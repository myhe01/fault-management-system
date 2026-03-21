cmake_minimum_required(VERSION 3.25)

project(fms_tests
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test binary
add_executable(fms_tests
    test/FaultTableTest.cpp
    test/FaultTableEntryTest.cpp
    test/UidTest.cpp
    src/FaultTable.cpp
    src/FaultTableEntry.cpp
)

target_include_directories(fms_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(fms_tests PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Werror
)

target_link_libraries(fms_tests PRIVATE
    GTest::gtest_main
    GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(fms_tests)