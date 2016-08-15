/**
 * @file   UnitTest.cpp
 * @author Jonathan Bedard
 * @date   8/14/2016
 * @brief  Unit Test logging and global functions
 * @bug No known bugs.
 *
 * Implements logging in the test namespace.  Implements
 * a number of global test functions used for initializing
 * and ending a Unit Test battery.
 */

 ///@cond INTERNAL
 
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

#define DIV_BLOCK "=================================================================="
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
		#ifdef _WIN32
		#if _DEBUG
		system("pause");
		#endif
		#endif
	}
	//Ends tests, logging the error
	void test::endTestsError(os::errorPointer except)
	{
		testout<<endl<<DIV_BLOCK<<endl;
		testout<<"\tERROR"<<endl;
		testout<<"\tResults:"<<endl;
		testout<<"\t\t"<<masterTestHolder::singleton().getNumRun()<<" libraries"<<endl;
		testout<<"\t\tof "<<masterTestHolder::singleton().getNumLibs()<<" tested"<<endl;
		testout<<"\t\twith "<<masterTestHolder::singleton().getNumSuccess()<<" successful"<<endl<<endl;

		testout<<"\tFailure in Test Battery!"<<endl;
		testout<<"\t"<<except->what()<<endl;
		testout<<DIV_BLOCK<<endl;
		endTest();
	}
	//Ends tests, no error
	void test::endTestsSuccess()
	{
		testout<<endl<<DIV_BLOCK<<endl;
		testout<<"\tTest Battery Completed"<<endl;
		testout<<"\tResults:"<<endl;
		testout<<"\t\t"<<masterTestHolder::singleton().getNumRun()<<" libraries"<<endl;
		testout<<"\t\tof "<<masterTestHolder::singleton().getNumLibs()<<" tested"<<endl;
		testout<<"\t\twith "<<masterTestHolder::singleton().getNumSuccess()<<" successful"<<endl;
		testout<<DIV_BLOCK<<endl;
		endTest();
	}

#endif

///@endcond