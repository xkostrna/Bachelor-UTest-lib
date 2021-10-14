#include <iostream>
#include "Paths.h"

std::string Paths::getAppFolder() {
    const std::string & applicationFolder{R"(C:\Users\kostr\Bakalarka\MyApplication)"};
    return applicationFolder;
}

std::string Paths::getWindowsSharedFolder() {
    const std::string & sharedFolderDestination{R"(C:\Users\kostr\Bakalarka\DockerShareFolder\Test)"};
    return sharedFolderDestination;
}