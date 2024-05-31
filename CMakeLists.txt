cmake_minimum_required (VERSION 3.14)

project (BitPositionLib)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror)

# Google Test support
enable_testing()
find_package(GTest REQUIRED)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# Require dot, treat the other components as optional
#find_package(Doxygen
#             REQUIRED dot
#             OPTIONAL_COMPONENTS mscgen dia)

#set(DOXYGEN_GENERATE_HTML YES)
#set(DOXYGEN_GENERATE_MAN NO)
             
#doxygen_add_docs(
#                doxygen
#                ${PROJECT_SOURCE_DIR}
#                COMMENT "Generate man pages"
#            )

add_executable(BitPositionLib BitPosition.cpp BitPositionTest.cpp ByteBufferTest.cpp)
target_link_libraries(BitPositionLib GTest::GTest GTest::Main)
add_test(test-1 test1)


