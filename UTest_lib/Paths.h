#ifndef UTEST_PATHS_H
#define UTEST_PATHS_H

#include <string>

namespace Paths {

    void setAppFolder(const std::string & path);
    void setSharedFolder(const std::string & path);

    std::string getAppFolder();
    std::string getSharedFolder();
}

#endif
