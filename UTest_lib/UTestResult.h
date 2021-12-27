#ifndef UTEST_UTESTRESULT_H
#define UTEST_UTESTRESULT_H

#include <string>
#include <list>
#include <vector>
#include "UTestCase.h"
#include "Paths.h"

class UTestResult {
private:
    const std::string testName;
    const UTestCase result;
    const int line;
    const std::string failureCase;
    UTestResult(std::string testName, UTestCase result, int line = 0, std::string failureCase = "");
    static struct results calculateResults();
    static void toConsole();
    static void toFile(const std::string & path, const std::string & fileName);
    static std::string getDate();
public:
    static std::list<UTestResult> & getResultsList();
    void print();
    static void add(std::string testName, UTestCase result, int line = 0, std::string failureCase = "");
    static void getInfo(bool toFile = true, const std::string & path = Paths::getAppFolder(), const std::string & fileName = "test_results");
};


#endif
