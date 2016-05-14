/**
 * @file   UnitTestExe/UnitTestMain.cpp
 * @author Jonathan Bedard
 * @date   5/14/2016
 * @brief  UnitTest entry point
 * @bug No known bugs.
 *
 * This file is the entry point
 * to a UnitTestExe application.
 * The application created with this
 * file will initialize and run the 
 * test battery.  If successful, the
 * application will return 0, else,
 * it will return -1.
 */

#ifndef UNIT_TEST_CPP
#define UNIT_TEST_CPP

#include <iostream>
#include "UnitTest.h"
#include "DatastructuresTest.h"

using namespace std;
using namespace os;
using namespace test;

#ifndef MAIN
#define MAIN

//Entry Function
int main(int argc,char** argv)
{
	testInit(argc,argv);
	startTests();

	try
	{
		masterTestHolder::singleton()->runTests();

	}
	//Exception Catching
	catch (os::errorPointer e1)
	{
		endTestsError(e1);
		return -1;
	}
	catch (exception& e2)
	{
		endTestsError(os::errorPointer(&e2));
		return -1;
	}
	catch (...)
	{
		endTestsError(os::errorPointer(new test::unknownException("UnitTestMain.cpp, 55"),shared_type));
		return -1;
	}
	endTestsSuccess();

	return 0;
}

#endif

#endif
