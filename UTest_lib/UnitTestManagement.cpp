#include <iostream>
#include <fstream>
#include "UnitTestManagement.h"
#include "Paths.h"
#include "IOErrors.h"

void UnitTestManagement::runDocker() {
    const std::string winFolder = Paths::getWindowsSharedFolder();
    const std::string appFolder = Paths::getAppFolder();
    const std::string copyCommand{"xcopy "+appFolder+" "+winFolder+" /e /q"};
    system(copyCommand.c_str());
    const std::string runCommand{"docker container run -ti -v "+winFolder+":/Program/Share appimage python3 ../run_script.py"};
    system(runCommand.c_str());
}

ContainerResult UnitTestManagement::getContainerReturnCode() {
    const std::string errorFile{Paths::getWindowsSharedFolder()+R"(\err_output.txt)"};
    std::ifstream inputStream{errorFile};
    int outputValue{0};
    if (inputStream.good()) {
        inputStream >> outputValue;
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    inputStream.close();
    switch(outputValue) {
        case 0 : return ContainerResult::OK;
        case -1000 : return ContainerResult::MAKE_ERR;
        case -2000 : return ContainerResult::CODE_TIMEOUT;
        default: break;
    }
    return ContainerResult::RUNTIME_ERR;
}

void UnitTestManagement::recreateSharedDirectory() {
    system(("rmdir "+Paths::getWindowsSharedFolder()+" /S /Q").c_str());
    system(("mkdir "+Paths::getWindowsSharedFolder()).c_str());
    std::cout << "-----------------" << std::endl;
}

std::string & getRequiredTestName() {
    static std::string requiredTestName;
    return requiredTestName;
}

static constexpr char testNameFile[] = "test_name.txt";

void UnitTestManagement::writeTestNameToFile(const std::string &testName) {
    std::ofstream outputStream(Paths::getWindowsSharedFolder()+"\\"+testNameFile);
    if (outputStream.good()) {
        outputStream << testName;
    }
    else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    outputStream.close();
}

bool UnitTestManagement::isTestNameCorrect(const std::string &realTestName) {
    if (getRequiredTestName().empty()) {
        std::ifstream inputStream(testNameFile);
        if (inputStream.good()) {
            inputStream >> getRequiredTestName();
        }
        else {
            IOErrors::printErrorMessage(__func__, __LINE__);
        }
        inputStream.close();
    }
    return (getRequiredTestName() == realTestName);
}
