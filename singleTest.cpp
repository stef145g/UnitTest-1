/**
 * @file   singleTest.cpp
 * @Author Jonathan Bedard
 * @date   7/9/2016
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
	void singleTest::test() {}
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
#endif

///@endcond