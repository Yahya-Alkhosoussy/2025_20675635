cmake_minimum_version(VERSION 3.12 FATAL_ERROR)
project(calc)

add_library(maths adder.cpp)

if (NOT BUILD_SHARED_LIBS)
