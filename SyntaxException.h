#pragma once

#include "InterperterException.h"
#ifndef SYNTAX_EXCEPTION_H
#define SYNTAX_EXCEPTION_H

class SyntaxException : public InterperterException
{
public:
	SyntaxException() : InterperterException("SyntaxError: invalid syntax") {}  // this will finally put the msg we sent in the what() function of
																				// exception class and when we call SyntaxException.what() it will return
																				// our msg.
	SyntaxException(const char* msg) : InterperterException(msg) {} // this for a case when we give as an argument a specific msg in the call of SyntaxException...
};

#endif // SYNTAX_EXCEPTION_H