//Confirmed Working 10/25/2015
//Primary Author: Jonathan Bedard

#ifndef DATASTRUCTURES_TEST_CPP
#define DATASTRUCTURES_TEST_CPP

#include "DatastructuresTest.h"

using namespace os;
using namespace std;
using namespace test;

/*================================================================
	Test Functions
================================================================*/

	void test1() throw(os::smart_ptr<std::exception>)
	{
	}
	void test2() throw(os::smart_ptr<std::exception>)
	{
		throw os::smart_ptr<std::exception>(new test::unknownException("DatastructuresTest.cpp, test2()"),shared_type);
	}

/*================================================================
	DatastructuresLibraryTest
================================================================*/

	//Constructor
	DatastructuresLibraryTest::DatastructuresLibraryTest():
		libraryTests("Datastructures")
	{
		os::smart_ptr<testSuite> trc = smart_ptr<testSuite>(new testSuite("smart_ptr"));
			trc->pushTest("test1",&test1);
			trc->pushTest("test2",&test2);
			trc->pushTest("null demo",NULL);
		pushSuite(trc);

		trc = smart_ptr<testSuite>(new testSuite("list"));
		pushSuite(trc);
	}

#endif