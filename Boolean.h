#ifndef BOOLEAN_H
#define BOOLEAN_H
#include "Type.h"

class Boolean : public Type
{
private:
	bool value;
public:
	explicit Boolean(bool value) : value(value) {};
	std::string toString() const override;
	std::string getType() const override { return "Boolean"; }
	std::string getLength() const override { return "TypeError: object of type ‘Boolean’ has no len() ."; }

	// arithmetic operators
	Boolean* operator*(Boolean* object) const { return nullptr; } // boolean type has no multiply ability
	Boolean* operator+(Boolean* object) const { return nullptr; } // boolean type has no add ability
	Boolean* operator-(Boolean* object) const { return nullptr; } // boolean type has no substruct ability
};
#endif // BOOLEAN_H