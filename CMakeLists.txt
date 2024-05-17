cmake_minimum_required (VERSION 3.14)

project (BitPositionLib)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
find_package(GTest REQUIRED)
add_executable(BitPositionLib BitPosition.cpp BitPositionTest.cpp ByteBufferTest.cpp)
target_link_libraries(BitPositionLib GTest::GTest GTest::Main)
add_test(test-1 test1)


