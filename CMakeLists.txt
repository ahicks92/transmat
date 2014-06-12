CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(Transmat)
if(${CMAKE_COMPILER_IS_GNUCC})
add_definitions(-std=c99)
endif()

add_library(transmat transmat.c)

SET_PROPERTY(TARGET transmat PROPERTY LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
