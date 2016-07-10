/**
 * @file   Exceptions/Exceptions.cpp
 * @Author Jonathan Bedard
 * @date   7/9/2016
 * @brief  Implements the error throwing functions 
 * @bug No known bugs.
 *
 * Defines the functions which throw
 * each of the unit test exceptions.
 *
 */

 ///@cond INTERNAL

#include "Exceptions.h"

#ifndef EXCEPTIONS_CPP
#define EXCEPTIONS_CPP

namespace test
{
	void generalTestException::throwException(const std::string& description,const std::string& location)
	{throw os::errorPointer(new generalTestException(description,location),os::shared_type);}
	
	void unknownException::throwException(const std::string& location)
	{throw os::errorPointer(new unknownException(location),os::shared_type);}
	
	void nullFunctionException::throwException(const std::string& location)
	{throw os::errorPointer(new nullFunctionException(location),os::shared_type);}
	
	void throwGeneralTestException(const std::string& description,const std::string& location)
	{generalTestException::throwException(description,location);}
	
	void throwUnknownException(const std::string& location)
	{unknownException::throwException(location);}
	
	void throwNullFunctionException(const std::string& location)
	{nullFunctionException::throwException(location);}
}

#endif

///@endcond