//Confirmed Working 10/25/2015
//Primary Author: Jonathan Bedard

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
	testInit();

	startTests();
	try
	{
		masterTestHolder::singleton()->runTests();
	}
	//Exception Catching
	catch (os::smart_ptr<exception> e1)
	{
		endTestsError(e1);
		return -1;
	}
	catch (exception& e2)
	{
		endTestsError(os::smart_ptr<exception>(&e2));
		return -1;
	}
	catch (...)
	{
		endTestsError(os::smart_ptr<exception>(new test::unknownException("UnitTestMain.cpp, 39"),shared_type));
		return -1;
	}
	endTestsSuccess();
	return 0;
}

#endif

#endif
