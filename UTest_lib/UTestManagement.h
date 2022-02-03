#ifndef UTEST_UTESTMANAGEMENT_H
#define UTEST_UTESTMANAGEMENT_H

#include <string>
#include "ContainerResult.h"

namespace UTestManagement {

    void runDocker();
    ContainerResult getContainerReturnCode();
    void recreateSharedDirectory();
    void writeTestNameToFile(const std::string& testName);
    bool isTestNameCorrect(const std::string& realTestName);
    void removeContainers();
}

#endif
