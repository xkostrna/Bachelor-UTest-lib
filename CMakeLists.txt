cmake_minimum_required(VERSION 3.19)
project(UTest)

set(CMAKE_CXX_STANDARD 20)

add_library(UTest STATIC UTest_lib)
set_target_properties(UTest PROPERTIES LINKER_LANGUAGE CXX)
