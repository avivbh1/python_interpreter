#pragma once
#include "Sequence.h"
#include "Type.h"
#include <string>

class String : public Sequence
{
private:
	std::string value;
public:
	explicit String(std::string value) : value(value) {};
	std::string toString() const override;
	std::string getType() const override { return "String"; }
	std::string getLength() const override { return std::to_string(value.length() - 2); } // were substracting 2 because it contains ths quotes each side

	// arithmetic operations
	String* operator*(String* object) const { return nullptr; }      // mull isnt available in strings
	String* operator+(String* object) const;					     // add between strings will connect their strings
	String* operator-(String* object) const { return nullptr; }    // substract isnt valiable in strings

};
