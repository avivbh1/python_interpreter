#include "Integer.h"
#include <string>

Integer* Integer::operator*(Integer* object) const
{
    int sumOFValues = (this->value * stoi(object->toString()));
    Integer* newObjectPtr = new Integer(sumOFValues);
    return newObjectPtr;
};


Integer* Integer::operator+(Integer* object) const
{
    int sumOFValues = (this->value + stoi(object->toString()));
    Integer* newObjectPtr = new Integer(sumOFValues);
    return newObjectPtr;
};


Integer* Integer::operator-(Integer* object) const
{
    int sumOFValues = (this->value - stoi(object->toString()));
    Integer* newObjectPtr = new Integer(sumOFValues);
    return newObjectPtr;
};
