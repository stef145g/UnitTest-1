/**
 * @file   UnitTestLog.h
 * @Author Jonathan Bedard
 * @date   7/8/2016
 * @brief  Logging for test namespace
 * @bug No known bugs.
 *
 * This file contains declarations which are used
 * for logging within the test namespace.
 *
 */

#ifndef UNIT_TEST_LOG_H
#define UNIT_TEST_LOG_H

#include "Datastructures/Datastructures.h"
#include <iostream>

namespace test
{
	/** @brief Standard out pointer for test namespace
	 *
	 * This std::ostream is used as standard out
	 * for the test namespace.  This pointer can be
	 * swapped out to programmatically redirect standard out for
	 * the test namespace.
	 */
	extern os::smart_ptr<std::ostream> testout_ptr;
	/** @brief Standard error pointer for test namespace
	 *
	 * This std::ostream is used as standard error
	 * for the test namespace.  This pointer can be
	 * swapped out to programmatically redirect standard error for
	 * the test namespace.
	 */
    extern os::smart_ptr<std::ostream> testerr_ptr;
	/** @brief Standard out object for test namespace
	 *
	 * #define statements allow the user to call this
	 * function with "test::testout."  Logging is achieved
	 * by using "test::testout" as one would use "std::cout."
	 */
	std::ostream& testout_func();
	/** @brief Standard error object for test namespace
	 *
	 * #define statements allow the user to call this
	 * function with "test::testerr."  Logging is achieved
	 * by using "test::testerr" as one would use "std::cerr."
	 */
	std::ostream& testerr_func();
}

#ifndef testout
#define testout testout_func()
#endif
#ifndef testerr
#define testerr testerr_func()
#endif

#endif