#ifndef MYAPPLICATION_ASSERTFAILEDEXCEPTION_H
#define MYAPPLICATION_ASSERTFAILEDEXCEPTION_H


#include <exception>
#include <string>

class AssertFailedException : public std::exception {
private:
    const int line;
    const std::string failureCase;
public:
    AssertFailedException(int funcLine, std::string failureCase);

    [[nodiscard]] const std::string & getFailureCase() const;

    [[nodiscard]] int getLine() const;

};

#endif