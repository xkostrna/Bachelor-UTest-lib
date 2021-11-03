#include <iostream>
#include "Paths.h"

std::string Paths::getAppFolder() {
    // must be set by user
    const std::string & applicationFolder{R"(C:\Users\kostr\Bakalarka\MyApplication)"};
    return applicationFolder;
}

std::string Paths::getWindowsSharedFolder() {
    // must be set by user
    const std::string & sharedFolderDestination{R"(C:\Users\kostr\Bakalarka\DockerShareFolder\Test)"};
    return sharedFolderDestination;
}