#include <iostream>
#include <fstream>
#include "UnitTestManagement.h"
#include "Paths.h"
#include "IOErrors.h"

void UnitTestManagement::runDocker() {
    const std::string winFolder = Paths::getWindowsSharedFolder();
    const std::string appFolder = Paths::getAppFolder();
    std::string copyCommand;

    #if defined (WINDOWS)
        copyCommand = "xcopy "+appFolder+" "+winFolder+" /e /q";
    #elif defined (UNIX)
        copyCommand = "cp -r "+appFolder+"/* "+winFolder;
    #endif

    system(copyCommand.c_str());
    std::string runCommand;

    #if defined (WINDOWS)
        runCommand = "docker container run -ti -v "+winFolder+":/Program/Share appimage python3 ../run_script.py";
    #elif defined (UNIX)
        runCommand = "docker container run -ti --user \"$(id -u):$(id -g\") -v "+winFolder+":/Program/Share appimage python3 ../run_script.py";
    #endif

    if(copyCommand.length() == 0) {
        std::cerr << "Platform not defined please use Windows or Unix based OS" << std::endl;
        exit(-1);
    }

    system(runCommand.c_str());
}

ContainerResult UnitTestManagement::getContainerReturnCode() {
    std::string operand;

    #if defined (WINDOWS)
        operand = "\\";
    #elif defined (UNIX)
        operand = "/";
    #endif

    const std::string errorFile = Paths::getWindowsSharedFolder() + operand + "err_output.txt";

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
    #if defined (WINDOWS)
        system(("rmdir "+Paths::getWindowsSharedFolder()+" /S /Q").c_str());
    #elif defined (UNIX)
        system(("rm -rf "+Paths::getWindowsSharedFolder()).c_str());
    #endif
    system(("mkdir "+Paths::getWindowsSharedFolder()).c_str());
    std::cout << "-----------------" << std::endl;
}

std::string & getRequiredTestName() {
    static std::string requiredTestName;
    return requiredTestName;
}

static constexpr char testNameFile[] = "test_name.txt";

void UnitTestManagement::writeTestNameToFile(const std::string &testName) {
    std::string operand;

    #if defined WINDOWS
        operand = "\\";
    #elif defined UNIX
        operand = "/";
    #endif

    const std::string outputPath = Paths::getWindowsSharedFolder() + operand + testNameFile;
    std::ofstream outputStream(outputPath);
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
