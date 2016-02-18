/**
 * @file   UnitTestExe/defaultTestInit.cpp
 * @author Jonathan Bedard
 * @date   2/12/2016
 * @brief  Default UnitTest initializer function
 * @bug No known bugs.
 *
 * By default, this is the implementation of the
 * UnitTest initializer function which binds
 * UnitTest libraries to the test battery.  This
 * function should be defined by a file in the
 * library of the main entry point of the
 * application.
 */

 ///@cond INTERNAL

#ifndef DEFAULT_TEST_INIT_CPP
#define DEFAULT_TEST_INIT_CPP

#include "UnitTest.h"

void test::testInit()
{
	test::testout<<"Pulled in the default test init."<<std::endl;
	test::testout<<"This is likely an error!"<<std::endl;
}

#endif

///@endcond