cmake_minimum_required(VERSION 3.19)
project(UTest)

set(CMAKE_CXX_STANDARD 20)

add_library(UTest STATIC
        UTest_lib/AssertFailedException.h
        UTest_lib/AssertFailedException.cpp
        UTest_lib/ContainerResult.h
        UTest_lib/IOErrors.h
        UTest_lib/IOErrors.cpp
        UTest_lib/Paths.h
        UTest_lib/Paths.cpp
        UTest_lib/Platform.h
        UTest_lib/Serialize.h
        UTest_lib/Serialize.cpp
        UTest_lib/TestCase.h
        UTest_lib/UnitTestManagement.h
        UTest_lib/UnitTestManagement.cpp
        UTest_lib/UTest.h
        UTest_lib/UTestMacro.h
        UTest_lib/UTestResult.cpp
        UTest_lib/UTestResult.h
        )
set_target_properties(UTest PROPERTIES LINKER_LANGUAGE CXX)
