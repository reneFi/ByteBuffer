cmake_minimum_required (VERSION 3.14)

project (BitPositionTest)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)

# Google Test support
enable_testing()
find_package(GTest REQUIRED)

add_executable(BitPositionTest BitPositionTest.cpp ByteBufferTest.cpp)
target_include_directories(BitPositionTest PUBLIC ../src)
target_link_libraries(BitPositionTest GTest::GTest GTest::Main)
add_test(test-1 test1)


