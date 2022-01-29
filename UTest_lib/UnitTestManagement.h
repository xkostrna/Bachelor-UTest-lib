#ifndef UTEST_UNITTESTMANAGEMENT_H
#define UTEST_UNITTESTMANAGEMENT_H

#include <string>
#include "ContainerResult.h"

namespace UnitTestManagement {

    void runDocker();
    ContainerResult getContainerReturnCode();
    void recreateSharedDirectory();
    void writeTestNameToFile(const std::string& testName);
    bool isTestNameCorrect(const std::string& realTestName);
    void removeContainers();
}

#endif
