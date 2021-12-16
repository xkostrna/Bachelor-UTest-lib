#include "UTestResult.h"
#include "IOErrors.h"
#include <iostream>
#include <algorithm>
#include <fstream>

struct results {
    int passed{0};
    int failed{0};
};

UTestResult::UTestResult(std::string testName, UTestCase result, int line, std::string failureCase)
    : testName(std::move(testName))
    , result(result)
    , line(line)
    , failureCase(std::move(failureCase)) { }

std::list<UTestResult> & UTestResult::getResultsList() {
    static std::list<UTestResult> resultsList;
    return resultsList;
}

void UTestResult::add(std::string testName, UTestCase result, int line, std::string failureCase) {
    std::list<UTestResult> & resultList{getResultsList()};
    UTestResult testResult(std::move(testName), result, line, std::move(failureCase));
    testResult.print();
    resultList.push_back(testResult);
}

void UTestResult::print() {
    std::cout << "test name : " << this->testName << std::endl;
    std::cout << "result : " << (result == UTestCase::PASSED ? "Passed" : "Failed" ) << std::endl;
    if (result == UTestCase::FAILED) {
        std::cout << "line : " << this->line << std::endl;
        std::cout << "failure case : " << this->failureCase << std::endl;
    }
}

void UTestResult::getInfo(bool toFile, const std::string& path) {
    UTestResult::toConsole();
    if(toFile) {
        UTestResult::toFile(path);
    }
}

struct results UTestResult::calculateResults() {
    std::list<UTestResult> & resultList = getResultsList();
    struct results testResults;
    std::for_each(resultList.begin(), resultList.end(), [&testResults](const UTestResult & uResult) {
        if (uResult.result == UTestCase::PASSED) {
            testResults.passed++;
        }
        else {
            testResults.failed++;
        }
    });
    return testResults;
}

void UTestResult::toConsole() {
    std::list<UTestResult> & resultList = getResultsList();
    struct results testResults = UTestResult::calculateResults();
    std::cout << "total tests : " << resultList.size() << std::endl;
    std::cout << "passed tests : " << testResults.passed << std::endl;
    std::cout << "failed tests : " << testResults.failed << std::endl;
    std::cout << "success rate : " << (double(testResults.passed) / double(resultList.size())) * 100.0 << "%" << std::endl;
}

void UTestResult::toFile(const std::string & path) {
    std::ofstream outputSteam(path + Paths::getPlatformSlash() + "test-results.txt");
    if(outputSteam.good()) {
        std::list<UTestResult> & resultList = getResultsList();
        struct results testResults = UTestResult::calculateResults();
        for (const UTestResult & result : resultList) {
            outputSteam << "test name : " << result.testName << std::endl;
            outputSteam << "results : " << (result.result == UTestCase::PASSED ? "Passed" : "Failed" ) << std::endl;
            if (result.result == UTestCase::FAILED) {
                outputSteam << "line : " << result.line << std::endl;
                outputSteam << "failure case : " << result.failureCase << std::endl;
            }
            outputSteam << "--------------------------" << std::endl;
        }
        outputSteam << "total tests : " << resultList.size() << std::endl;
        outputSteam << "passed tests : " << testResults.passed << std::endl;
        outputSteam << "failed tests : " << testResults.failed << std::endl;
        outputSteam << "success rate : " << (double(testResults.passed) / double(resultList.size())) * 100.0 << "%" << std::endl;
    } else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    outputSteam.close();
}
