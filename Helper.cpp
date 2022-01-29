#include "Helper.h"
#include <iostream>
bool Helper::isInteger(const std::string& s)
{
	int start = (s[0] == '-' or s[0] == '+') ? 1 : 0;
	for (int i = start; i < s.size(); i++)
	{
		if (!isDigit(s[i]))
		{
			return false;
		}
	}

	return true;
}

bool Helper::isBoolean(const std::string& s)
{
	return (s == "True" || s == "False");
}


bool Helper::isString(const std::string& s)
{
	if (s[0] == '\"' && s[s.length() -1] == '\"')
	{
		for (int i = 1; i < s.length() - 1; i++)
		{
			if (s[i] == '\"')
			{
				return false;
			}
		}
		return true;
	}
	if (s[0] == '\'' && s[s.length() - 1] == '\'')
	{
		// checks if the string contains " inside the string while the string was delcared with "string"
		for (int i = 1; i < s.length() - 1; i++)
		{
			// checks if the string contains ' inside the string while the string was delcared with 'string'
			if (s[i] == '\'')
			{
				return false;
			}
		}
		return true;
	}

	return false;
}

bool Helper::isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

void Helper::trim(std::string &str)
{
	rtrim(str);
	ltrim(str);

}

void Helper::rtrim(std::string &str)
{
	size_t endpos = str.find_last_not_of(" \t");
	if (std::string::npos != endpos)
	{
		str = str.substr(0, endpos + 1);
	}
}

void Helper::ltrim(std::string &str)
{
	size_t startpos = str.find_first_not_of(" \t");
	if (std::string::npos != startpos)
	{
		str = str.substr(startpos);
	}
}

void Helper::removeLeadingZeros(std::string &str)
{
	size_t startpos = str.find_first_not_of("0");
	if (std::string::npos != startpos)
	{
		str = str.substr(startpos);
	}
}


bool Helper::isLowerLetter(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool Helper::isUpperLetter(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool Helper::isLetter(char c)
{
	return (isLowerLetter(c) || isUpperLetter(c));
}

bool Helper::isUnderscore(char c)
{
	return ('_' == c);
}

bool Helper::isList(std::string str)
{
	if ((str[0] == '[') && (str[str.length() - 1] == ']') )
	{
		return true;
	}
	return false;
}

