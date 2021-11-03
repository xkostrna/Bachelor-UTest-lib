#ifndef UTEST_UTESTRESULT_H
#define UTEST_UTESTRESULT_H

#include <string>
#include <list>
#include "TestCase.h"

class UTestResult {
private:
    const std::string testName;
    const TestCase result;
    const int line;
    const std::string failureCase;
    UTestResult(std::string testName, TestCase result, int line = 0, std::string failureCase = "");
public:
    static std::list<UTestResult> & getResultsList();
    void print();
    static void add(std::string testName, TestCase result, int line = 0, std::string failureCase = "");
    static void getInfo();
};


#endif
