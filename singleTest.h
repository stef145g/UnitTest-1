//Confirmed Working 10/25/2015
//Primary Author: Jonathan Bedard

#ifndef SINGLE_TEST_H
#define SINGLE_TEST_H

#include "Datastructures.h"
#include "UnitTestExceptions.h"
#include "UnitTestLog.h"

namespace test
{
	typedef void (*testFunction)() throw(os::smart_ptr<std::exception>);

	//Single test
	class singleTest: public os::ptrComp
	{
		std::string testName;
	public:
		singleTest(std::string tn);

		virtual void test() throw(os::smart_ptr<std::exception>);
		void logBegin();
		bool logEnd(os::smart_ptr<std::exception> except = NULL);
	};
	//Single Function test
	class singleFunctionTest:public singleTest
	{
		testFunction func;
	public:
		singleFunctionTest(std::string tn, testFunction f);
		void test() throw(os::smart_ptr<std::exception>);
	};
}

#endif