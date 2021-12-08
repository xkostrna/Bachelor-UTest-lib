#ifndef UTEST_UTESTRESULT_H
#define UTEST_UTESTRESULT_H

#include <string>
#include <list>
#include "UTestCase.h"

class UTestResult {
private:
    const std::string testName;
    const UTestCase result;
    const int line;
    const std::string failureCase;
    UTestResult(std::string testName, UTestCase result, int line = 0, std::string failureCase = "");
public:
    static std::list<UTestResult> & getResultsList();
    void print();
    static void add(std::string testName, UTestCase result, int line = 0, std::string failureCase = "");
    static void getInfo();
};


#endif
