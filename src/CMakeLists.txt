cmake_minimum_required (VERSION 3.14)

project (BitPositionLib)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)


add_executable(BitPositionLib BitPosition.cpp)
target_include_directories(BitPositionLib PUBLIC ../src)
target_link_libraries(BitPositionLib)


