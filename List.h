#pragma once
#include "Sequence.h"
#include <vector>
#include <string>

class List : public Sequence
{
public:
	std::vector<Type*> listOfValues;
	List(std::vector<Type*>& list) : listOfValues(list) {};

	std::string toString() const override; // overriding it from Type class (list->sequence->type)
	std::string getType() const override { return "List"; }
	void insertToList(Type* objectPtr);
	std::string getLength() const override { return std::to_string(listOfValues.size()); }

	// operators
	List* operator*(List* object) const { return nullptr; };    // mull isnt available in Lists
	List* operator+(List* listOfObjects) const;				        // add between strings will connect their lists
	List* operator-(List* object) const { return nullptr; }   // substract isnt valiable in lists

	~List();
	List(List& object) {};
	List& operator=(const List&) {};

};
