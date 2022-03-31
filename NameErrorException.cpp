#include "NameErrorException.h"
#include <string>

std::string NameErrorException::What() const
{
	std::string msgPart1 = "“NameError : name ";
	std::string msgPart2 = " is not defined";
	return msgPart1 + this->name + msgPart2;
}
