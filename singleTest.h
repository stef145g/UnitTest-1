/**
 * @file   singleTest.h
 * @Author Jonathan Bedard
 * @date   7/9/2016
 * @brief  Single test class
 * @bug No known bugs.
 *
 * This file contains declarations for a single
 * unit test.  Unit tests can be defined as separate
 * class or a simple test function.
 *
 */

#ifndef SINGLE_TEST_H
#define SINGLE_TEST_H

#include "Datastructures/Datastructures.h"
#include "UnitTestExceptions.h"
#include "UnitTestLog.h"

namespace test
{
	/** @brief Typedef for single test function
	 *
	 * This typedef defines what a single test
	 * function looks like.  For simplicity,
	 * a single unit test can be defined by a function
	 * of this type instead of inheriting from
	 * test::singleTest.
	 *
	 * @return void
	 */
	typedef void (*testFunction)();

	/** @brief Single unit test class
	 *
	 * This class acts as the base
	 * class for all unit tests.  It
	 * inherits from the os::ptrComp class
	 * to allow it to be inserted into
	 * abstract data-structures.
	 */
	class singleTest
	{
		/** @brief Name of unit test
		 */
		std::string testName;
	public:
		/** @brief Single unit test constructor
		 * @param [in] tn Name of unit test
		 */
		singleTest(std::string tn);
		/** @brief Virtual destructor
		 *
		 * Destructor must be virtual, if an object
		 * of this type is deleted, the destructor
		 * of the type which inherits this class should
		 * be called.
		 */
        virtual ~singleTest(){}

		/** @brief Preforms any test set-up
		 *
		 * This function is designed to preform
		 * any set-up a test requires.  This is
		 * especially useful if a class of tests
		 * require the same set-up routine.  This
		 * function assumes that the test::testSuite
		 * will catch exceptions in this function
		 * if they are thrown.
		 *
		 * @return void
		 */
        virtual void setupTest() {}
		/** @brief Preforms core unit-test
		 *
		 * This function is designed to preform
		 * the actual unit test.  This
		 * function assumes that the test::testSuite
		 * will catch exceptions in this function
		 * if they are thrown.
		 *
		 * @return void
		 */
		virtual void test();
		/** @brief Preforms any test tear-down
		 *
		 * This function is designed to preform
		 * any tear-down a test requires.  This is
		 * especially useful if a class of tests
		 * require the same tear-down routine.  This
		 * function assumes that the test::testSuite
		 * will catch exceptions in this function
		 * if they are thrown.
		 *
		 * @return void
		 */
        virtual void teardownTest() {}
        
		/** @brief Prints out the name of the test
		 * @return void
		 */
		void logBegin();
		/** @brief Logs errors for test
		 *
		 * If the passed exception is NULL, no logging
		 * is preformed.  Otherwise, the "what()" function
		 * of the exception is printed.  This function
		 * return true if NULL is passed as the exception.
		 *
		 * @param [in] except Exception to be printed, NULL by default
		 * @return True if except is NULL
		 */
		bool logEnd(os::errorPointer except = NULL);

		#undef CURRENT_CLASS
		#define CURRENT_CLASS singleTest
		POINTER_COMPARE
		POINTER_HASH_CAST
		COMPARE_OPERATORS
	};
	/** @brief Single unit test from function
	 *
	 * This class allows a test::singleTest to be
	 * defined by a single test function.
	 */
	class singleFunctionTest:public singleTest
	{
		/** @brief Reference to unit test function
		 */
		testFunction func;
	public:
		/** @brief Single unit test constructor
		 * @param [in] tn Name of unit test
		 * @param [in] f Function which defines test
		 */
		singleFunctionTest(std::string tn, testFunction f);
		/** @brief Virtual destructor
		 *
		 * Destructor must be virtual, if an object
		 * of this type is deleted, the destructor
		 * of the type which inherits this class should
		 * be called.
		 */
        virtual ~singleFunctionTest(){}
        
		/** @brief Call unit test function
		 *
		 * Calls the function bound to this
		 * class in the constructor pointed to
		 * by test::singleFunctionTest::func.  If
		 * the function pointed to by the function
		 * pointer throws an exception, this function
		 * will throw the same exception.
		 *
		 * @return void
		 */
		void test() throw(os::errorPointer);

		#undef CURRENT_CLASS
		#define CURRENT_CLASS singleFunctionTest
		POINTER_COMPARE
		COMPARE_OPERATORS
	};
}

#endif