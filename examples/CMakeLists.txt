cmake_minimum_required (VERSION 3.14)

project (ByteBufferExample)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)

add_executable(ByteBufferExample main.cpp)
target_include_directories(ByteBufferExample PUBLIC ../src)


