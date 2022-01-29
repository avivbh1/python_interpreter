#ifndef INDENTATION_EXCEPTION_H
#define INDENTATION_EXCEPTION_H

#include "InterperterException.h"
#include <string>
class IndentationException : public InterperterException
{
public:
	IndentationException() : InterperterException("IndentationError: unexpected Indent") {} // this will finally put the msg we sent in the what() function of
																										// exception class and when we call Indententation.what() it will return
																										// our msg.

	IndentationException(const char* msg) : InterperterException(msg) {} // this for a case when we give as an argument a specific msg in the call of IndentationException...
};

#endif // INDENTATION_EXCEPTION_H