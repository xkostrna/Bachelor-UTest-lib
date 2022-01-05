#include <iostream>
#include <algorithm>
#include "Paths.h"
#include "Platform.h"

static std::string applicationFolderPath;
static std::string sharedFolderPath;

void Paths::setAppFolder(const std::string & path) {
    applicationFolderPath = path;
}

void Paths::setSharedFolder(const std::string & path) {
    sharedFolderPath = path;
}

std::string Paths::getAppFolder() {
    #if defined (SOURCE_PATH) && defined (WINDOWS)
        std::string output = SOURCE_PATH;
        std::replace(output.begin(), output.end(), '/', '\\');
        return output;
    #elif defined(SOURCE_PATH) && defined (UNIX)
        return SOURCE_PATH;
    #else
        if(applicationFolderPath.length() == 0) {
            std::cerr << "Please use Paths::setAppFolder()" << std::endl;
            exit(-1);
        } else {
            return applicationFolderPath;
        }
    #endif
}

std::string Paths::getSharedFolder() {
    return sharedFolderPath;
}

std::string Paths::getPlatformSlash() {
    std::string slash;
    #if defined (WINDOWS)
        slash = "\\";
    #elif defined (UNIX)
        slash = "/";
    #endif
    return slash;
}
