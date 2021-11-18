#include <iostream>
#include "Paths.h"

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

std::string Paths::getWindowsSharedFolder() {
    return sharedFolderPath;
}