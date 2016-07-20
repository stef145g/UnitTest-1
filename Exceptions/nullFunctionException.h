/**
 * @file   Exception/generalTestException.h
 * @Author Jonathan Bedard
 * @date   7/17/2016
 * @brief  Null function exception definition
 * @bug No known bugs.
 *
 * Defines an exception thrown when a
 * when a test function is undefined.
 */

#ifndef NULL_FUNCTION_EXCEPTIONS_H
#define NULL_FUNCTION_EXCEPTIONS_H

#include "generalTestException.h"

namespace test
{
	/** @brief NULL function exception class
	 *
	 * This class defines the common exception
	 * case where a NULL function pointer is
	 * received.
	 */
	class nullFunctionException final: public generalTestException
	{
	public:
		/** @brief Creates and throws a null function exception
		 * @param [in] location Source of the error, file and function
		 * @return void
		 */
		static void throwException(const std::string& location);
		
		/** @brief Construct exception with location
		 *
		 * Constructs a test::generalTestException with
		 * the provided location and the static string
		 * for a NULL function exception.
		 *
		 * @param [in] loc Location string
		 */
		nullFunctionException(const std::string& loc):
			generalTestException("NULL Function pointer received",loc)
		{}
		/** @brief Final destructor
		 *
		 * This class cannot be inherited from,
		 * so the the destructor cannot be extended.
		 */
		~nullFunctionException() throw() final{}
	};

	/** @brief Creates and throws a null function exception
	 * @param [in] location Source of the error, file and function
	 * @return void
	 */
	void throwNullFunctionException(const std::string& location);
	
}

#endif