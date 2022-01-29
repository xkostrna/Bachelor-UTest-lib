#include <string>
#include <iostream>
#include "IOErrors.h"

void IOErrors::printErrorMessage(const std::string & functionName, const int & line) {
    std::cerr << functionName << " error => I/O error flag recognized" << std::endl;
    std::cerr << "Line : " << line << std::endl;
}
