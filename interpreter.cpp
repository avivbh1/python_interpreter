#include "type.h"
#include "InterperterException.h"
#include "parser.h"
#include "IndentationException.h"
#include "SyntaxException.h"
#include "NameErrorException.h"
#include "TypeError.h"
#include "parser.h"
#include "Boolean.h"
#include "Integer.h"
#include "String.h"
#include "Void.h"
#include <iostream>

#define WELCOME "Welcome to NOT-Magshimim Python Interperter version 1.0 by "
#define YOUR_NAME "AVIV"

int main(int argc, char** argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string input_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, input_string);

	while (input_string != "quit()")
	{
		// prasing command
		try
		{
			Type* ptrToVar = Parser::parseString(input_string);

			if (ptrToVar != NULL && ptrToVar->isPrintable())
			{
				// will print the value of the object if it's not NULL and if it can be printed (type Void cant be)
				std::cout << ptrToVar->toString() << std::endl; // printing the value of the object
			}
			if (ptrToVar != NULL && ptrToVar->GetIsTemp())
			{
				// will delete the the object if it is a temp variable
				delete (ptrToVar); // deleting the object
			}
		}
		catch (IndentationException error1)
		{
			std::cerr << error1.what() << std::endl; // std::cerr supposed to print in red color
		}
		catch (SyntaxException error2)
		{
			std::cerr << error2.what() << std::endl; // std::cerr supposed to print in red color
		}
		catch (NameErrorException error3)
		{
			std::cerr << error3.What() << std::endl;
		}
		catch (TypeError error4)
		{
			std::cerr << error4.what() << std::endl;
		}
		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
	}
	Parser::cleanMemoryOfObject();
	return 0;
}


