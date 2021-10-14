#ifndef MYAPPLICATION_UNITTESTMANAGEMENT_H
#define MYAPPLICATION_UNITTESTMANAGEMENT_H

#include <string>
#include "ContainerResult.h"

namespace UnitTestManagement {
    //docker invoking commands
    void runDocker();
    ContainerResult getContainerReturnCode();

    //DockerShareFolder/Test handling
    void recreateSharedDirectory();

    //testName.txt handling
    void writeTestNameToFile(const std::string& testName);
    bool isTestNameCorrect(const std::string& realTestName);
}

#endif
