//Confirmed Working 10/25/2015
//Primary Author: Jonathan Bedard

#ifndef UNIT_TEST_EXCEPTIONS_H
#define UNIT_TEST_EXCEPTIONS_H

#include "Datastructures.h"
#include <exception>
#include <string>

namespace test
{
	//Unknown exception
	class unknownException: public std::exception
	{
	private:
		std::string location;
		std::string total_error;
	public:
		unknownException(std::string loc)
		{
			location = loc;
			total_error = "Unregistered exception type occured, "+location;
		}
		virtual const char* what() const throw(){return total_error.c_str();}
	};

	//Null Function Pointer Exception
	class nullFunctionException: public std::exception
	{
	private:
		std::string location;
		std::string total_error;
	public:
		nullFunctionException(std::string loc)
		{
			location = loc;
			total_error = "NULL Function pointer received, "+location;
		}
		virtual const char* what() const throw(){return total_error.c_str();}
	};
}

#endif