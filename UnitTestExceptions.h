//Confirmed Working 11/7/2015
//Primary Author: Jonathan Bedard

#ifndef UNIT_TEST_EXCEPTIONS_H
#define UNIT_TEST_EXCEPTIONS_H

#include "Datastructures.h"
#include <exception>
#include <string>

namespace test
{
	//General exception
	class generalTestException: public std::exception
	{
	private:
		std::string location;
		std::string _error;
		std::string total_error;
	public:
		generalTestException(std::string err, std::string loc)
		{
			location = loc;
			_error = err;
			total_error = err+", "+loc;
		}
        virtual ~generalTestException(){}
		virtual const char* what() const throw(){return total_error.c_str();}
		const std::string& getLocation() const {return location;}
		const std::string& getString() const {return _error;}
	};
	//Unknown exception
	class unknownException: public generalTestException
	{
	public:
		unknownException(std::string loc):
			generalTestException("Unregistered exception type occured",loc)
		{}
        virtual ~unknownException(){}
	};

	//Null Function Pointer Exception
	class nullFunctionException: public generalTestException
	{
	public:
		nullFunctionException(std::string loc):
			generalTestException("NULL Function pointer received",loc)
		{}
        ~nullFunctionException(){}
	};
}

#endif