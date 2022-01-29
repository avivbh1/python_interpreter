#include "List.h"
#include <iostream>

std::string List::toString() const
{
	//std::cout << listOfValues[0]->toString() << std::endl;
	std::string output = "[";
	if (listOfValues.size() == 0)
	{
		return "[]";
	}
	else
	{
		for (size_t i = 0; i < listOfValues.size() - 1; i++)
		{
			output += listOfValues[i]->toString();
			output += ',';
		}
		output += listOfValues[listOfValues.size() - 1]->toString();
		output += "]";
	}
	return output;
};



void List::insertToList(Type* objectPtr)
{
	listOfValues.push_back(objectPtr);
};


List* List::operator+(List* listOfObjects) const
{
	std::vector<Type*> copyOfListOfValues = listOfValues;
	for (auto object : listOfObjects->listOfValues)
	{
		copyOfListOfValues.push_back(object);
	}
	List* newObjectPtr = new List(copyOfListOfValues);
	return newObjectPtr;
};


List::~List()
{
	for (size_t i = 0; i < listOfValues.size() - 1; i++)
	{
		if (listOfValues[i]->GetIsTemp())
		{
			// deleting the object in the list if he was a tempObject
			delete (listOfValues[i]);
		}
	}
};
