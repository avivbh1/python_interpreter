#include "Boolean.h"
#include <iostream>

std::string Boolean::toString() const
{
	if (this->value == true)
	{
		return "True";
	}
	else if (this->value == false)
	{
		return "False";
	}
};