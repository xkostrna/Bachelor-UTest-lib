#ifndef MYAPPLICATION_UTEST_H
#define MYAPPLICATION_UTEST_H

#include <string>
#include <iostream>
#include "Serialize.h"
#include "UnitTestManagement.h"
#include "AssertFailedException.h"
#include "UTestResult.h"
#include "TestCase.h"
#include "UTestMacro.h"
#include "Platform.h"
#include "ContainerResult.h"

template <typename TYPE>
class UTest {
public:
    UTest() = default;

protected:
    void run(const std::string& testName) {
        #if defined OS_WIN
            this->runWindows(testName);
        #elif defined OS_LINUX
            this->runContainer(testName);
        #endif
    }

    void runWindows(const std::string& testName) {
        UnitTestManagement::writeTestNameToFile(testName);
        UnitTestManagement::runDocker();
        const ContainerResult containerResult = UnitTestManagement::getContainerReturnCode();
        if (containerResult == ContainerResult::OK) {
            tryDeserialize(testName);
        }
        else if (containerResult == ContainerResult::CODE_TIMEOUT) {
            UTestResult::add(testName, TestCase::FAILED, 0, "Code timeout");
        }
        else {
            UTestResult::add(testName, TestCase::FAILED, 0, "Run time error");
        }
        UnitTestManagement::recreateSharedDirectory();
    }

    void runContainer(const std::string& testName) {
        if (UnitTestManagement::isTestNameCorrect(testName)) {
            TYPE realValue{this->container()};
            Serialize::serialize(realValue);
            exit(0);
        }
    }

    virtual TYPE container() = 0;
    virtual void windows(TYPE realValue) = 0;

private:
    void tryDeserialize(const std::string & testName) {
        try {
            TYPE realValue = Serialize::deserialize<TYPE>();
            this->windows(realValue);
            UTestResult::add(testName, TestCase::PASSED);
        }
        catch(const AssertFailedException & exception) {
            UTestResult::add(testName, TestCase::FAILED, exception.getLine(), exception.getFailureCase());
        }
        catch(...) {
            UTestResult::add(testName, TestCase::FAILED, 0, "Unknown error");
        }
    }
};

#endif