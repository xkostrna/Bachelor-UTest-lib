cmake_minimum_required(VERSION 3.20)
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
        UTestCase.h
        UTestManagement.h
        UTestManagement.cpp
        UTest.h
        UTestMacro.h
        UTestResult.cpp
        UTestResult.h)

add_definitions("-DSOURCE_PATH=\"${CMAKE_SOURCE_DIR}\"")
set_target_properties(UTest PROPERTIES LINKER_LANGUAGE CXX)
