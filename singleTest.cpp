/**
 * @file   singleTest.cpp
 * @Author Jonathan Bedard
 * @date   5/14/2016
 * @brief  Single test class implementation
 * @bug No known bugs.
 *
 * This file contains implementation for a single
 * unit test.  Consult singeTest.h for details.
 *
 */

///@cond INTERNAL

#ifndef SINGLE_TEST_CPP
#define SINGLE_TEST_CPP

#include "UnitTest.h"

using namespace os;
using namespace std;
using namespace test;

/*================================================================
	singleTest
================================================================*/

	//Constructor
	singleTest::singleTest(std::string tn)
	{
		testName = tn;
	}
	//Run test
	void singleTest::test() throw(os::errorPointer){}
	//Log begining
	void singleTest::logBegin()
	{
		testout<<"\t\t\t"<<testName<<endl;
	}
	//Log ending
	bool singleTest::logEnd(os::errorPointer except)
	{
		if(except)
		{
			testout<<"\t\t\tERROR:"<<endl;
			testout<<"\t\t\t\t"<<except->what()<<endl;
			return false;
		}
		else
			return true;
	}

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