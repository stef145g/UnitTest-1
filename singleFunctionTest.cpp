/**
 * @file   singleTestFunction.cpp
 * @Author Jonathan Bedard
 * @date   8/14/2016
 * @brief  Single test function implementation
 * @bug No known bugs.
 *
 * This file contains implementation for a single
 * unit test as defined by a function.
 * Consult singeFunctionTest.h for details.
 *
 */

///@cond INTERNAL

#ifndef SINGLE_TEST_FUNCTION_CPP
#define SINGLE_TEST_FUNCTION_CPP

#include "UnitTest.h"

using namespace os;
using namespace std;
using namespace test;

/*================================================================
	singleFunctionTest
================================================================*/

	//Single function test constructor
	singleFunctionTest::singleFunctionTest(std::string tn, testFunction f):
		singleTest(tn)
	{
		func = f;
	}
	//Run test
	void singleFunctionTest::test() throw(os::errorPointer)
	{
		if(func==NULL) throw os::errorPointer(new nullFunctionException("singleTest.cpp, 55"),shared_type);
		else func();
	}

#endif

///@endcond