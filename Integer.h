#ifndef INTEGER_H
#define INTEGER_H
#include "Type.h"
#include <string>

class Integer : public Type
{
private:
	int value;
public:
	explicit Integer(int value) : value(value) {};
	std::string toString() const override { return (std::to_string(value)); }; // we are casting the int to a std::string and return it as a std:string
	std::string getType() const override { return "Integer"; }
	std::string getLength() const override { return "TypeError: object of type ‘int’ has no len() ."; }

	// arithmetic operators
	Integer* operator*(Integer* object) const ;     // multiply between integers will myltiply their values
	Integer* operator+(Integer* object) const ;    // add between integers will sum their values
	Integer* operator-(Integer* object) const ;   // substract between integers will substract their values
};
#endif // INTEGER_H