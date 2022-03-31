#pragma once
#include "InterperterException.h"
#include <iostream>

class TypeError : public InterperterException
{
public:
	TypeError() : InterperterException("TypeError: incorrect Type") {}
	TypeError(std::string msg) : InterperterException(msg.c_str()) {}
};