/**
 * @file   singleTestFunction.h
 * @Author Jonathan Bedard
 * @date   7/9/2016
 * @brief  Single test function
 * @bug No known bugs.
 *
 * This file contains declarations for a single
 * unit test as defined by a function.
 *
 */

#ifndef SINGLE_TEST_FUNCTION_H
#define SINGLE_TEST_FUNCTION_H

#include "singleTest.h"

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

	/** @brief Single unit test from function
	 *
	 * This class allows a test::singleTest to be
	 * defined by a single test function.
	 */
	class singleFunctionTest final:public singleTest
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
        ~singleFunctionTest() final{}
        
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
		void test() throw(os::errorPointer) final;

		#undef CURRENT_CLASS
		#define CURRENT_CLASS singleFunctionTest
		POINTER_COMPARE
		COMPARE_OPERATORS
	};
}

#endif