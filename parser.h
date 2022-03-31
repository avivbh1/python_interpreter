#ifndef PARSER_H
#define PARSER_H

#include "InterperterException.h"
#include "type.h"
#include "Helper.h"
#include <string>
#include <unordered_map>
#include <iostream>

class Parser
{
public:
	static std::unordered_map<std::string, Type*>  _variables; // the data base of our interpreter.

	static Type* parseString(std::string str);

	static bool isLegalVarName(const std::string& str);
	static bool isTypeLegal(std::string str);
	static Type* getVariableValue(const std::string& str);

	static Type* GetType(std::string str);
	static bool makeAssignment(const std::string& str);
	static std::vector<Type*> makeList(std::string& str);

	// check input if it is a built in function
	static bool isBuiltInFunctions(std::string& str);
	static bool isTypeFunction(std::string& str);
	static bool isDelFunction(std::string& str);
	static bool isLenFunction(std::string& str);

	// built in functions 
	static Type* lenFunction(std::string& str);
	static Type* delFunction(std::string& str);
	static Type* typeFunction(std::string& str);

	static void cleanMemoryOfObject();
	
};

#endif //PARSER_H
