#include "UTestResult.h"
#include "IOErrors.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iomanip>

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
    std::cout << "result : " << (result == UTestCase::PASSED ? "Passed" : "Failed" ) << std::endl;
    if (result == UTestCase::FAILED) {
        std::cout << "line : " << this->line << std::endl;
        std::cout << "failure case : " << this->failureCase << std::endl;
    }
}

void UTestResult::getInfo(bool toFile, const std::string& path, const std::string& fileName) {
    UTestResult::toConsole();
    if(toFile) {
        UTestResult::toFile(path, fileName);
    }
}

struct results UTestResult::calculateResults() {
    std::list<UTestResult> & resultList{getResultsList()};
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
    std::list<UTestResult> & resultList{getResultsList()};
    struct results testResults = UTestResult::calculateResults();
    std::cout << "total tests : " << resultList.size() << std::endl;
    std::cout << "passed tests : " << testResults.passed << std::endl;
    std::cout << "failed tests : " << testResults.failed << std::endl;
    std::cout << "success rate : " << (double(testResults.passed) / double(resultList.size())) * 100.0 << "%" << std::endl;
}

std::string UTestResult::getDate() {
    time_t now{time(nullptr)};
    tm *ltm{localtime(&now)};
    std::stringstream sstream;
    sstream << std::put_time(ltm, "%Y-%m-%d %H-%M-%S");
    return sstream.str();
}

void UTestResult::toFile(const std::string & path, const std::string& fileName) {
    std::string date{UTestResult::getDate()};
    std::ofstream outputStream(path + Paths::getPlatformSlash() + fileName + " " + date + ".txt");
    if(outputStream.good()) {
        std::list<UTestResult> & resultList{getResultsList()};
        struct results testResults = UTestResult::calculateResults();
        outputStream << "Date : " << date << std::endl;
        outputStream << "--------------------------" << std::endl;
        for (const UTestResult & result : resultList) {
            outputStream << "test name : " << result.testName << std::endl;
            outputStream << "results : " << (result.result == UTestCase::PASSED ? "Passed" : "Failed" ) << std::endl;
            if (result.result == UTestCase::FAILED) {
                outputStream << "line : " << result.line << std::endl;
                outputStream << "failure case : " << result.failureCase << std::endl;
            }
            outputStream << "--------------------------" << std::endl;
        }
        outputStream << "total tests : " << resultList.size() << std::endl;
        outputStream << "passed tests : " << testResults.passed << std::endl;
        outputStream << "failed tests : " << testResults.failed << std::endl;
        outputStream << "success rate : " << (double(testResults.passed) / double(resultList.size())) * 100.0 << "%" << std::endl;
    } else {
        IOErrors::printErrorMessage(__func__, __LINE__);
    }
    outputStream.close();
}
