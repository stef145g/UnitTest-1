/**
 * @file   UnitTest.h
 * @author Jonathan Bedard
 * @date   7/9/2016
 * @brief  Unit Test header file
 * @bug No known bugs.
 *
 * Packages all headers required for the
 * UnitTest library and declares a number
 * of global test functions used for initializing
 * and ending a Unit Test battery.
 */

#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "Datastructures/Datastructures.h"
#include "UnitTestLog.h"
#include "masterTestHolder.h"
#include "UnitTestExceptions.h"
#include "TestSuite.h"
#include <iostream>
#include <exception>

namespace test
{
	/** @brief Print out header for Unit Tests
	 *
	 * Prints out a global division block line of
	 * '=' characters, then 'Unit Test Battery' and
	 * then another global division block.
	 *
	 * @return void
	 */
	void startTests();
	/** @brief End tests in error
	 *
	 * Prints out a global division block line of
	 * '=' characters, then the information provided
	 * in the exception passed to the function then
	 * another global division block
	 *
	 * @param [in] except Exception which caused the error
	 * @return void
	 */
	void endTestsError(os::errorPointer except);
	/** @brief End tests successfully
	 *
	 * Prints out a global division block line of
	 * '=' characters, then the test results data provided
	 * by the test::masterTestHolder then
	 * another global division block
	 *
	 * @return void
	 */
	void endTestsSuccess();

	/** @brief Test initialization
	 *
	 * This function is re-implemented by
	 * each executable which uses the UnitTest
	 * library.  This function is used to bind
	 * all of the library tests, except the
	 * Datastructures library test.
	 *
	 * @return void
	 */
	void testInit(int argc=0,char** argv=NULL);
}

#endif