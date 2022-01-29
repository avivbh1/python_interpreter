#ifndef TYPE_H
#define TYPE_H
#include <iostream>


class Type
{
protected:
	bool isTemp = false;
	//const std::string typeIs;
public:
	virtual bool GetIsTemp() const { return this->isTemp; }
	virtual void SetIstTemp(const bool temp) { this->isTemp = temp; } 
	virtual const bool isPrintable() const { return true; } // this is correct for all of the class that derived except void which returns false.
	virtual std::string toString() const = 0; // it will be defined in each calss that derived from it
	virtual std::string getType() const = 0; // every type class that wiil derive Type will define this function according to his type
	virtual std::string getLength() const = 0; // will be override by String and List Only

	// arithmetic functions
};





#endif //TYPE_H
