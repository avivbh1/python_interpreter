
#include "parser.h"
#include "IndentationException.h"
#include "TypeError.h"
#include <iostream>
#include <algorithm>
#include "Helper.h"

#include "Integer.h"
#include "Boolean.h"
#include "String.h"
#include "SyntaxException.h"
#include "NameErrorException.h"
#include "List.h"

std::unordered_map<std::string, Type*> Parser::_variables;

Type* Parser::parseString(std::string str)
{
	if (str.length() > 0)
	{
		// checking if the input is with indeentation error 
		if (str[0] == ' ')
		{
			// in case there is an indentation block not in place
			throw IndentationException();
		}

		Helper::rtrim(str); // now we right trim the input 

		// checking if the input is one of our built functions
		if (Parser::isBuiltInFunctions(str))
		{
			Type* msgPtr = nullptr;
			if (Parser::isDelFunction(str))
			{
				msgPtr = Parser::delFunction(str);
			}
			if (Parser::isLenFunction(str))
			{
				msgPtr = Parser::lenFunction(str);
			}
			if (Parser::isTypeFunction(str))
			{
				msgPtr = Parser::typeFunction(str);
			}
			return msgPtr;
		}


		Type* thisVarPtr = Parser::getVariableValue(str); // trying to see if the line contains a variable that the user wants to print his value 
		if (thisVarPtr != NULL)
		{
			// in case the varPtr is not NULL it means there is an object on _variables (our data map) with this key as his varName so we return this object
			return thisVarPtr;
		}
		// in case we are here it means there is no exist variable so we keep check other possibilties

		thisVarPtr = GetType(str);
		if (thisVarPtr == NULL)
		{
			// if the ptr is null it means the line isnt a valid value to print 

			// now we check if this is an assignmnet line
			if (Parser::makeAssignment(str) == false)
			{
				// make sure it is a valid input otherwise synataxError
				throw SyntaxException("SyntaxError: An unvalid input");
			}

			// in case makeAssignment(str) == true it means it was an assignment line and it also made for us a new variable in the _variable map
			std::string varName = str.substr(0, str.find('=')); // take the chars from the left of the assignmet operator(the name)
			Helper::rtrim(varName); // cuts the spaces in the right side of var name
			_variables[varName]->SetIstTemp(false); // setting the tempVar as false because the user made a new variable with assignment line 
			return nullptr; // we return nullptr because the line was an assignment line and the user didnt ask from us to print
		}
		else if (thisVarPtr != NULL)
		{
			// it means the GetType(str) returned a valid type so we return the pointer to this object we created at GetType
			thisVarPtr->SetIstTemp(true); // setting it as temp because we want to delete the object after we print it
			return thisVarPtr;
		}
		

	}
	return NULL;
};


Type* Parser::GetType(std::string str)
{
	Helper::trim(str);

	if (Helper::isInteger(str))
	{
		// checks if the output is Integer
		Integer* varPtr = new Integer(stoi(str)); // stoi made the string an int (string to int)
		//varPtr->SetIstTemp(true);
		return varPtr;
	}
	if (Helper::isBoolean(str))
	{
		// checks if the output is boolean
		if(str == "True")
		{
			Boolean* varPtr = new Boolean(true);
			//varPtr->SetIstTemp(true);
			return varPtr;																																																																																																																																																																																																																																																																																																																																																																																																																																																		
		}
		Boolean* varPtr = new Boolean(false);
		//varPtr->SetIstTemp(true);
		return varPtr;
	}

	if (Helper::isString(str))
	{
		// checks if the output is String
		str[0] = '\"'; // boundaring the string with " and not '
		str[str.length() - 1] = '\"';// boundaring the string with " and not '
		String *varPtr = new String(str); // making an object of type of String
		//varPtr->SetIstTemp(true); 
		return varPtr;
	}
	if (Helper::isList(str))
	{
		std::vector<Type*> listOfValues = makeList(str);
		//std::cout << "line 105 in parser.cpp the value is: " << listOfValues[listOfValues.size() - 1]->toString() << std::endl;
		//std::cout << listOfValues[0] << std::endl;
		List* varPtr = new List(listOfValues);
		return varPtr;
	}
	else
	{
		return NULL;
	}
};

bool Parser::isLegalVarName(const std::string& name)
{
	if (name != "False" && name != "True")
	{
		if (Helper::isDigit(name[0]) == false)
		{
			for (size_t i = 1; i < name.length(); i++)
			{
				if (Helper::isDigit(name[i]) == false && Helper::isLetter(name[i]) == false && name[i] != '_')
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
};

bool Parser::makeAssignment(const std::string& cmdLine)
{
	if ((cmdLine.find('=') < (cmdLine.length() - 1)) && cmdLine.find('=') > 0)
	{
		// means there is '=' in the string
		if ((cmdLine[0] != '=' && cmdLine[cmdLine.length() - 1] != '='))
		{
			// means the '=' is not in the start or the end of the string
			int assignmentOperatorIndex = cmdLine.find('=');
			std::string leftValue = cmdLine.substr(0, assignmentOperatorIndex); // from index 0 makes x steps forward
			std::string rightValue = cmdLine.substr(assignmentOperatorIndex + 1, cmdLine.length() - assignmentOperatorIndex - 1);
			Helper::rtrim(leftValue); //right trim the varName (all the spaces that can be)
			Helper::ltrim(rightValue); //left trim the varValue (all the spaces that can be)


			if (Parser::isLegalVarName(leftValue) == false)
			{
				//checks if the varName is legal
				throw NameErrorException(leftValue);
			}

			Type* rightValuePtr = Parser::parseString(rightValue); // checking if the right value represents a len() function or soemthing that return a value
			if (rightValuePtr != nullptr)// if its nullptr it means it the right value is not a command that returns a value
			{
				rightValue = rightValuePtr->toString();
			}
			delete(rightValuePtr); // deleting it because the user didnt ask from us to make a new variable of that

			//now we check if the right value is a a legal name of avariable and that the user want to do  dst=src;
			if (Parser::isLegalVarName(rightValue))
			{
				//now we check if the src is an exist variable in our data base _variable
				if (_variables.find(rightValue) != _variables.end())
				{
					// if it exists so we do the assignment
					if (_variables[rightValue]->getType() == "List")
					{
						// in case the src is a list we want to do shllow copy as python doing
						// so...
						Type* newObjectPtr = _variables[rightValue];
						_variables[leftValue] = newObjectPtr;
						return true;
					}
					else
					{
						// in case the src isnt a type List were doing deep copy as python doing.
						//we're doing deep copy, it means the dst will point to a new variable in a new location but with the same type and value
						Type* newObjectPtr = GetType(_variables[rightValue]->toString());
						_variables[leftValue] = newObjectPtr;
						return true;
					}
				}
				else
				{
					throw NameErrorException(rightValue);
				}
			}

			//if we're here it means the right value isnt a legal name of variable so we keep checking if it is a valid valud the user trying to assign. dst=value
			Type* objectPtr = GetType(rightValue); // making a pointer to the object we created at GetType
			if (objectPtr == NULL)
			{
				// make sure we do have a legal value
				throw SyntaxException("SyntaxError: Illegal variable Value");
			}
			_variables[leftValue] = objectPtr; // inserting the varValue and the varName to the data base _variables
			return true;
		}
	}
	return false;
};


Type* Parser::getVariableValue(const std::string& str)
{
	std::string varName = str; // the string we get represents a name of a varibale that might be exist
	if (_variables.find(varName) == _variables.end())
	{
		// it means there is no variable with this name
		return NULL;
	}
	else
	{
		return (_variables[varName]); // return the pointer to the object with this varName 
	}
};

void Parser::cleanMemoryOfObject()
{
	for (auto it : _variables)
	{
		// ourtunning all the pairs of the data base variables(VarName-object)
		delete (it.second); // it.second is the object of this pair
	}
};


std::vector<Type*> Parser::makeList(std::string& str)
{
	std::vector<Type*> tempListOfObjects = {};
	// checking if the inputstring represents a list

	std::string copyOfStr = str;
	copyOfStr.erase(0 , 1);
	copyOfStr.erase(copyOfStr.length() - 1, 1);


	// checking if there is only one value in the list
	if( copyOfStr.find(',') == std::string::npos ) // check how many commas are in the [.....]  if there are no commas it means its only one variable or none
	{
		// if we're here it means there are no commas in the list so it has only one value

		if (copyOfStr.find_first_not_of(' ') == std::string::npos || copyOfStr == "")
		{
			// here it means there are only spaces in the list or that it is an empty list and it is valid so we return an empty list
			return tempListOfObjects;
		}

		// if we're here it means there is a value or a name of a variable in the list so we check these posobilities now
		std::string tempObjectInList = copyOfStr;
		Helper::trim(tempObjectInList); // trimming the sides : [   7  ] is a valid list with the int value 7 in index 0

		Type* objectPtr = Parser::getVariableValue(tempObjectInList); // checking if the text in the list is a name of a variable
		if (objectPtr == NULL)
		{
			// in case this is not a variable name we check if this is a valid value of a valid type
			Type* objectPtr = GetType(tempObjectInList);
			if (objectPtr == NULL)
			{
				throw NameErrorException(tempObjectInList); // the user entered an unrecognized string which is not a value or a name we know 
			}
			objectPtr->SetIstTemp(true);
			tempListOfObjects.push_back(objectPtr);
		}
		else
		{
		// in case we're here it means the ptr we got from gerVariableValue was not NULL so we push it to the listOfObjects
		tempListOfObjects.push_back(objectPtr);
		}
	}


	//if we're here it means there is at least one comma or more in the list but we check to make sure
	else if (copyOfStr.find(',') != std::string::npos)
	{
	// in case there are commas in the list it means there are many objects in the list
	size_t numOfObjectsInList = std::count(copyOfStr.begin(), copyOfStr.end(), ',') + 1; // number of all the objects in the list

	for (size_t i = 0; i < numOfObjectsInList - 1; i++)
	{
		// running all over the objects in the list except the last one 
		int indexOfFirstComma = copyOfStr.find(','); // finds the index of the first comma in copyOfStr
		//int indexOfSecondComma = copyOfStr.find(',', indexOfFirstComma + 1); // finds the index of the sedond comma in copyOfStr
		std::string tempObjectInList = copyOfStr.substr(0, indexOfFirstComma); // cutting out the first object in the list

		// now we check if the object between the commas is empty so we throw syntaxError
		if (tempObjectInList.find_first_not_of(' ') == std::string::npos || tempObjectInList == "")
		{
			throw SyntaxException();
		}

		// now we check what do we have between the commas. it can be a name of a variable or a valid value of a valid type
		copyOfStr = copyOfStr.substr(indexOfFirstComma + 1, copyOfStr.length() - indexOfFirstComma - 1); // cutting out the tempObjectInList from the copyOfStr
		Helper::trim(tempObjectInList);

		Type* objectPtr = Parser::getVariableValue(tempObjectInList); // chekcing if the text in the list is a name of a variable
		if (objectPtr == NULL)
		{
			// in case this is not a variable name we check if this is a valid value of a valid type
			objectPtr = Parser::GetType(tempObjectInList);
			if (objectPtr == NULL)
			{
				throw NameErrorException(tempObjectInList); // the user entered an unrecognized string which is not a value or a name we know 
			}
			objectPtr->SetIstTemp(true); // if we got the variable from get type we need to make sure to delete it fater we print it 
		}
		tempListOfObjects.push_back(objectPtr);
	}

	std::string tempObjectInList = copyOfStr; // copyOFStr is the whole string of the last object in the list

	if (tempObjectInList.find_first_not_of(' ') == std::string::npos || tempObjectInList == "")
	{
		// here it means there are only spaces in the last object of the list or that it is an empty place and it is valid so we return the list as it is
		return tempListOfObjects;
	}

	// if we're here it means there is something in the last place of the list so we check what it is
	Helper::trim(tempObjectInList);

	Type* objectPtr = Parser::getVariableValue(tempObjectInList); // chekcing if the text in the list is a name of a variable


	if (objectPtr == NULL)
	{
		// in case this is not a variable name we check if this is a valid value of a valid type
		objectPtr = Parser::GetType(tempObjectInList);;
		if (objectPtr == NULL)
		{
			throw NameErrorException(tempObjectInList); // the user entered an unrecognized string which is not a value or a name we know 
		}
		objectPtr->SetIstTemp(true);
	}
	tempListOfObjects.push_back(objectPtr);
	}
	return tempListOfObjects;
};


bool Parser::isTypeLegal(std::string str)
{
	Helper::trim(str);

	if (Helper::isInteger(str))
	{
		// checks if the output is Integer
		return true;
	}
	if (Helper::isBoolean(str))
	{
		// checks if the output is boolean
		return true;
	}

	if (Helper::isString(str))
	{
		// checks if the output is String
		return true;
	}
	return false;
};

bool Parser::isTypeFunction(std::string& str)
{
	std::string typeOperation = str.substr(0, 4); // the type operation suold be in index 0 to 4
	if (typeOperation == "type")
	{
		if (str[4] == '(' && str[str.length() - 1] == ')')
		{
			return true;
		}
	}
	return false;
};

bool Parser::isLenFunction(std::string& str)
{
	std::string lenOperation = str.substr(0, 3); // the type operation suold be in index 0 to 4
	if (lenOperation == "len")
	{
		if (str[3] == '(' && str[str.length() - 1] == ')')
		{
			return true;
		}
	}
	return false;
};


bool Parser::isDelFunction(std::string& str)
{
	std::string delOperation = str.substr(0, 3); // the type operation suold be in index 0 to 4
	if (delOperation == "del")
	{
		if (str[3] == '(' && str[str.length() - 1] == ')')
		{
			return true;
		}
	}
	return false;
};


bool Parser::isBuiltInFunctions(std::string& str)
{
	if (Parser::isDelFunction(str) || Parser::isLenFunction(str) || Parser::isTypeFunction(str))
	{
		return true;
	}
	return false;
};


Type* Parser::typeFunction(std::string& str)
{
	std::string argFunction = str.substr(5, str.length() - 5 - 1); // getting the name of the objects between the brackets ; type(name)
	Helper::trim(argFunction);

	if (Parser::isLegalVarName(argFunction))
	{
		if (Parser::getVariableValue(argFunction) == NULL)
		{
			throw NameErrorException(argFunction);
		}
		Type* varPtr = Parser::parseString(argFunction); // sending the argument to see what it presents
	// we're sending it again because it can be len() function and we need to see if it is valid

		std::string msg = ("<type '" + varPtr->getType() + "'>");
		String* msgPtr = new String(msg);
		msgPtr->SetIstTemp(true);
		msgPtr->setUserCreation(true); // set the String as userCreation to make the interpreter know not to deliever it as normal object that the user created
		return msgPtr;

	}
	else
	{
		Type* varPtr = Parser::parseString(argFunction); // sending the argument to see what it presents
		// we're sending it again because it can be len() function and we need to see if it is valid

		std::string msg = ("<type '" + varPtr->getType() + "'>");
		String* msgPtr = new String(msg);
		msgPtr->SetIstTemp(true);
		msgPtr->setUserCreation(true); // set the String as userCreation to make the interpreter know not to deliever it as normal object that the user created
		delete (varPtr);
		return msgPtr;

	}

};


Type* Parser::delFunction(std::string& str)
{
	std::string argFunction = str.substr(4, str.length() - 4 - 1);
	Helper::trim(argFunction);
	if (Parser::isLegalVarName(argFunction))
	{
		if (Parser::getVariableValue(argFunction) != NULL) // checking if the variable is in our data base 
		{
			delete (_variables[argFunction]);
			_variables.erase(argFunction);
			std::cout << argFunction << " was deleted successfully" << std::endl;
			return nullptr;
		}
		throw NameErrorException(argFunction);
	}
	throw SyntaxException();
};


Type* Parser::lenFunction(std::string& str)
{
	std::string argFunction = str.substr(4, str.length() - 4 - 1);
	Helper::trim(argFunction);
	Type* varPtr = Parser::parseString(argFunction);
	//Sequence* newVarPtr = varPtr;

	if (varPtr != NULL && varPtr->getIsUserCreation() == false)
	{
		if (varPtr->getType() != "List" && varPtr->getType() != "String")
		{
			//TypeError: object of type ñintò has no len() .
			std::string msg = "TypeError: object of '" + varPtr->getType() + "' has no len() .";
			throw TypeError(msg);
			return nullptr;
		}
		else
		{
			std::string msg = varPtr->getLength();
			Integer* msgPtr = new Integer(stoi(msg));
			msgPtr->SetIstTemp(true); // set as temp to delete it after we print the length
			if (Parser::getVariableValue(argFunction) == NULL)
			{
				delete varPtr; // if the argument wasnt a name in our data base we will delete it after we create it
			}
			return msgPtr;
		}
	}
	throw SyntaxException("SyntaxError: invalid syntax in len() function");
};