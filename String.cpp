#include "String.h"

std::string String::toString() const
{
	char ch = '\'';
	if (std::find(value.begin(), value.end(), '\'') == value.end())
	{
		// it means we dont have a ' in the string so we need to output the string as 'sring' and not as "string"
		std::string copyOfValue = value;
		copyOfValue[0] = '\'';
		copyOfValue[copyOfValue.length() - 1] = '\'';
		return copyOfValue;
	}
	return value;
};

String* String::operator+(String* object) const
{
	std::string newTextValue = this->value + object->value;
	String* newVarPtr = new String(newTextValue);
	return newVarPtr;
};

