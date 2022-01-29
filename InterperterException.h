#ifndef INTERPERTER_EXCEPTION_H
#define INTERPERTER_EXCEPTION_H

#include <exception>

class InterperterException : public std::exception
{
public:
	InterperterException() : std::exception("InterpreterException") {}
	InterperterException(const char* msg) : std::exception(msg) {}
};



#endif //INTERPERTER_EXCEPTION_H