#include "UTestResult.h"
#include <iostream>
#include <algorithm>

UTestResult::UTestResult(std::string testName, TestCase result, int line, std::string failureCase)
    : testName(std::move(testName))
    , result(result)
    , line(line)
    , failureCase(std::move(failureCase)) { }

std::list<UTestResult> & UTestResult::getResultsList() {
    static std::list<UTestResult> resultsList;
    return resultsList;
}

void UTestResult::add(std::string testName, TestCase result, int line, std::string failureCase) {
    std::list<UTestResult> & resultList{getResultsList()};
    UTestResult testResult(std::move(testName), result, line, std::move(failureCase));
    testResult.print();
    resultList.push_back(testResult);
}

void UTestResult::print() {
    std::cout << "test name : " << this->testName << std::endl;
    std::cout << "result : " << (result == TestCase::PASSED ? "Passed" : "Failed" ) << std::endl;
    if (result == TestCase::FAILED) {
        std::cout << "line : " << this->line << std::endl;
        std::cout << "failure case : " << this->failureCase << std::endl;
    }
}

void UTestResult::getInfo() {
    std::list<UTestResult> & resultList = getResultsList();
    int passed{0};
    int failed{0};
    std::for_each(resultList.begin(), resultList.end(), [&passed, &failed](const UTestResult & uResult) {
        if (uResult.result == TestCase::PASSED) {
            passed++;
        }
        else {
            failed++;
        }
    });
    std::cout << "total tests : " << resultList.size() << std::endl;
    std::cout << "passed tests : " << passed << std::endl;
    std::cout << "failed tests : " << failed << std::endl;
    std::cout << "success rate : " << (double(passed) / double(resultList.size())) * 100.0 << "%" << std::endl;
}
