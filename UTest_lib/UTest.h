#ifndef UTEST_UTEST_H
#define UTEST_UTEST_H

#include <string>
#include <iostream>
#include "Serialize.h"
#include "UTestManagement.h"
#include "AssertFailedException.h"
#include "UTestResult.h"
#include "UTestCase.h"
#include "UTestMacro.h"
#include "Platform.h"
#include "ContainerResult.h"

template <typename TYPE>
class UTest {
public:
    UTest() = default;

protected:
    void run(const std::string& testName) {
        #if defined PLATFORM_USER
            this->runUser(testName);
        #elif defined PLATFORM_CONTAINER
            this->runContainer(testName);
        #endif
    }

    void runUser(const std::string& testName) {
        UTestManagement::writeTestNameToFile(testName);
        UTestManagement::runDocker();
        const ContainerResult containerResult{UTestManagement::getContainerReturnCode()};
        if (containerResult == ContainerResult::OK) {
            runUserPartOfUnitTest(testName);
        } else if (containerResult == ContainerResult::CODE_TIMEOUT) {
            UTestResult::add(testName, UTestCase::FAILED, 0, "Code timeout");
        } else if (containerResult == ContainerResult::MAKE_ERR) {
            UTestResult::add(testName, UTestCase::FAILED, 0, "Container make error");
        } else {
            UTestResult::add(testName, UTestCase::FAILED, 0, "Run time error");
        }
        UTestManagement::removeContainers();
        UTestManagement::recreateSharedDirectory();
    }

    void runContainer(const std::string& testName) {
        if (UTestManagement::isTestNameCorrect(testName)) {
            TYPE realValue{this->container()};
            Serialize::serialize(realValue);
            exit(0);
        }
    }

    virtual TYPE container() = 0;
    virtual void user(TYPE realValue) = 0;

private:
    void runUserPartOfUnitTest(const std::string & testName) {
        try {
            TYPE realValue = Serialize::deserialize<TYPE>();
            this->user(realValue);
            UTestResult::add(testName, UTestCase::PASSED);
        }
        catch(const AssertFailedException & exception) {
            UTestResult::add(testName, UTestCase::FAILED, exception.getLine(), exception.getFailureCase());
        }
        catch(...) {
            UTestResult::add(testName, UTestCase::FAILED, 0, "Unknown error");
        }
    }
};

#endif
