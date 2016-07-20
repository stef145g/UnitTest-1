/**
 * @file   Exceptions/unknownException.h
 * @Author Jonathan Bedard
 * @date   7/17/2016
 * @brief  Unknown test exception
 * @bug No known bugs.
 *
 * Exception thrown by a unit test
 * when the exception type is undefined
 * or uncaught.
 *
 */

#ifndef UNKNOWN_EXCEPTION_H
#define UNKNOWN_EXCEPTION_H

#include "generalTestException.h"

namespace test
{
	/** @brief Unknown exception class
	 *
	 * This class defines the common exception
	 * case where the precise nature of the exception
	 * is unknown.
	 */
	class unknownException final: public generalTestException
	{
	public:
		/** @brief Creates and throws an unknown exception
		 * @param [in] location Source of the error, file and function
		 * @return void
		 */
		static void throwException(const std::string& location);
	
		/** @brief Construct exception with location
		 *
		 * Constructs a test::generalTestException with
		 * the provided location and the static string
		 * for an unknown exception.
		 *
		 * @param [in] loc Location string
		 */
		unknownException(const std::string& loc):
			generalTestException("Unregistered exception type occurred",loc)
		{}
		/** @brief Final destructor
		 *
		 * This class cannot be inherited from,
		 * so the the destructor cannot be extended.
		 */
		 ~unknownException() throw() final{}
	};
	/** @brief Creates and throws an unknown exception
	 * @param [in] location Source of the error, file and function
	 * @return void
	 */
	void throwUnknownException(const std::string& location);
	
}

#endif