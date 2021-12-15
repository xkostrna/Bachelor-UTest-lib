#include "UTestResult.h"
#include "IOErrors.h"
#include <iostream>
#include <algorithm>
#include <fstream>

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

void UTestResult::getInfo(bool toConsole, bool toFile, const std::string& path) {
    if(toConsole) {
        UTestResult::toConsole();
    }
    if(toFile) {
        UTestResult::toFile(path);
    }
}

std::vector<int> UTestResult::calculateResults() {
    std::list<UTestResult> & resultList = getResultsList();
    int passed{0};
    int failed{0};
    std::for_each(resultList.begin(), resultList.end(), [&passed, &failed](const UTestResult & uResult) {
        if (uResult.result == UTestCase::PASSED) {
            passed++;
        }
        else {
            failed++;
        }
    });
    return std::vector<int>{passed, failed};
}

void UTestResult::toConsole() {
    std::list<UTestResult> & resultList = getResultsList();
    std::vector<int> results = UTestResult::calculateResults();
    std::cout << "total tests : " << resultList.size() << std::endl;
    std::cout << "passed tests : " << results[0] << std::endl;
    std::cout << "failed tests : " << results[1] << std::endl;
    std::cout << "success rate : " << (double(results[0]) / double(resultList.size())) * 100.0 << "%" << std::endl;
}

void UTestResult::toFile(const std::string & path) {
    std::ofstream outputSteam(path + Paths::getPlatformSlash() + "results.txt");
    if(outputSteam.good()) {
        std::list<UTestResult> & resultList = getResultsList();
        std::vector<int> results = UTestResult::calculateResults();
        for (const UTestResult & result : resultList) {
            outputSteam << "test name : " << result.testName << std::endl;
            outputSteam << "result : " << (result.result == UTestCase::PASSED ? "Passed" : "Failed" ) << std::endl;
            if (result.result == UTestCase::FAILED) {
                outputSteam << "line : " << result.line << std::endl;
                outputSteam << "failure case : " << result.failureCase << std::endl;
            }
            outputSteam << "--------------------------" << std::endl;
        }
        outputSteam << "total tests : " << resultList.size() << std::endl;
        outputSteam << "passed tests : " << results[0] << std::endl;
        outputSteam << "failed tests : " << results[1] << std::endl;
        outputSteam << "success rate : " << (double(results[0]) / double(resultList.size())) * 100.0 << "%" << std::endl;
    } else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    outputSteam.close();
}
