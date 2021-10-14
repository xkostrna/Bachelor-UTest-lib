#include "AssertFailedException.h"
#include <utility>

AssertFailedException::AssertFailedException(int line, std::string failureCase)
    : line(line)
    , failureCase(std::move(failureCase)) { }

int AssertFailedException::getLine() const {
    return this->line;
}

const std::string & AssertFailedException::getFailureCase() const {
    return this->failureCase;
}
