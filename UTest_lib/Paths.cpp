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
    return applicationFolderPath;
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