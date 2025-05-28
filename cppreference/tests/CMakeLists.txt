cmake_minimum_required(VERSION 3.25)
project(cppreference LANGUAGES CXX)

# C++23
set(CMAKE_CXX_COMPILER "clang++-19")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GoogleTest
enable_testing()
find_package(GTest CONFIG REQUIRED)

# test codes
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")


include(GoogleTest)
add_executable(test_main ${TEST_SOURCES})
target_compile_options(test_main PRIVATE "-Wall -g3")

target_link_libraries(test_main PRIVATE GTest::gtest GTest::gtest_main)
gtest_discover_tests(test_main)
