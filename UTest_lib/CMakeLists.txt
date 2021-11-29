cmake_minimum_required(VERSION 3.19)
project(UTest)

set(CMAKE_CXX_STANDARD 20)

add_library(UTest STATIC
        AssertFailedException.h
        AssertFailedException.cpp
        ContainerResult.h
        IOErrors.h
        IOErrors.cpp
        Paths.h
        Paths.cpp
        Platform.h
        Serialize.h
        Serialize.cpp
        TestCase.h
        UnitTestManagement.h
        UnitTestManagement.cpp
        UTest.h
        UTestMacro.h
        UTestResult.cpp
        UTestResult.h)

set_target_properties(UTest PROPERTIES LINKER_LANGUAGE CXX)
