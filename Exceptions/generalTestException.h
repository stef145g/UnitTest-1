/**
 * @file   Exceptions/generalTestException.h
 * @Author Jonathan Bedard
 * @date   7/9/2016
 * @brief  General unit test exception
 * @bug No known bugs.
 *
 * This file defines an exception designed
 * to be generally used for errors in
 * any unit test.
 *
 */

#ifndef GENERAL_TEST_EXCEPTIONS_H
#define GENERAL_TEST_EXCEPTIONS_H

#include "Datastructures//Datastructures.h"
#include <exception>
#include <string>

namespace test
{
	/** @brief Base class for test exceptions
	 *
	 * This class defines an exception which has
	 * a location.  Because this class holds multiple
	 * std::string objects, the error description can
	 * be dynamically set.
	 */
	class generalTestException: public std::exception
	{
	private:
		/** @brief The location where the error came from
		 */
		std::string location;
		/** @brief A description of the error
		 */
		std::string _error;
		/** @brief Combination of the error and location
		 *
		 * This string is constructed in the constructor
		 * so that "what()" can refer to a location in
		 * memory.  This std::string is a combination
		 * of test::generalTestException::_error and
		 * test::generalTestException::location.
		 */
		std::string total_error;
	public:
		/** @brief Creates and throws a test exception
		 * @param [in] description Error description
		 * @param [in] location Source of the error, file and function
		 * @return void
		 */
		static void throwException(const std::string& description,const std::string& location);
	
		/** @brief Construct exception with error and location
		 *
		 * Constructs the exception with an error string and
		 * a location string.  Also builds the
		 * test::generalTestException::total_error string for
		 * use by the "what()" function.
		 *
		 * @param [in] err Error string
		 * @param [in] loc Location string
		 */
		generalTestException(const std::string& err, const std::string& loc)
		{
			location = loc;
			_error = err;
			total_error = err+", "+loc;
		}
		/** @brief Virtual destructor
		 *
		 * Destructor must be virtual, if an object
		 * of this type is deleted, the destructor
		 * of the type which inherits this class should
		 * be called.
		 */
		virtual ~generalTestException() throw(){}
		/** @brief std::exception overload
		 *
		 * Overloaded from std::exception.  This function
		 * outputs the complete description, which contains
		 * both the error description and location description.
		 *
		 * @return character pointer to the complete description
		 */
		const char* what() const throw() final{return total_error.c_str();}
		/** @brief Location description
		 * @return test::generalTestException::location
		 */
		const std::string& getLocation() const {return location;}
		/** @brief Error description
		 * @return test::generalTestException::_error
		 */
		const std::string& getString() const {return _error;}
	};
	
	/** @brief Creates and throws a test exception
	 * @param [in] description Error description
	 * @param [in] location Source of the error, file and function
	 * @return void
	 */
	void throwGeneralTestException(const std::string& description,const std::string& location);
	
}

#endif