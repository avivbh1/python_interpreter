#pragma once
#include "InterperterException.h"
#include <iostream>


class NameErrorException : public InterperterException
{
private:
	std::string name;
public:
	NameErrorException(std::string text) : name(text) {};
	std::string What() const;
};
