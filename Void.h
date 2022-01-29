#ifndef VOID_H
#define VOID_H
#include "Type.h"
class Void : public Type
{
	const bool isPrintable() const override { return false; }// this function was overrided beacuse it return false unlike the other classes which return true.
	std::string getType() const override { return "Void"; };
};

#endif // VOID_H