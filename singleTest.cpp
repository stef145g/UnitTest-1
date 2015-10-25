//Confirmed Working 10/25/2015
//Primary Author: Jonathan Bedard

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
	void singleTest::test() throw(os::smart_ptr<std::exception>){}
	//Log begining
	void singleTest::logBegin()
	{
		testout<<"\t\t\t"<<testName<<endl;
	}
	//Log ending
	bool singleTest::logEnd(os::smart_ptr<std::exception> except)
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
	void singleFunctionTest::test() throw(os::smart_ptr<std::exception>)
	{
		if(func==NULL) throw os::smart_ptr<std::exception>(new nullFunctionException("singleTest.cpp, 55"),shared_type);
		else func();
	}

#endif