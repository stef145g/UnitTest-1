//Confirmed Working 10/25/2015
//Primary Author: Jonathan Bedard

#ifndef UNIT_TEST_CPP
#define UNIT_TEST_CPP

#include <iostream>
#include "UnitTest.h"

	//Log conversion functions
	std::ostream& test::testout_func() {return *testout_ptr;}
	std::ostream& test::testerr_func() {return *testerr_ptr;}

	//Global Streams
	os::smart_ptr<std::ostream> test::testout_ptr(&(std::cout));
    os::smart_ptr<std::ostream> test::testerr_ptr(&(std::cerr));

using namespace std;
using namespace os;
using namespace test;

//Global Status Functions----------------------------------------------------------

#define DIV_BLOCK "========================================"
	//Starts the tests
	void test::startTests()
	{
		testout<<DIV_BLOCK<<endl;
		testout<<"\tUnit Test Battery"<<endl;
		testout<<DIV_BLOCK<<endl<<endl;
	}
	//General end test function. serves as a sub-routine
	static void endTest()
	{
		//For testing sanity
		#ifdef WIN32
		system("pause");
		#endif
	}
	//Ends tests, logging the error
	void test::endTestsError()
	{
		testout<<endl<<DIV_BLOCK<<endl;
		testout<<"\tERROR"<<endl;
		testout<<"\tFailure in Test Battery!"<<endl;
		testout<<DIV_BLOCK<<endl;
		endTest();
	}
	//Ends tests, no error
	void test::endTestsSuccess()
	{
		testout<<endl<<DIV_BLOCK<<endl;
		testout<<"\tTest Battery Completed"<<endl;
		testout<<DIV_BLOCK<<endl;
		endTest();
	}

#endif
