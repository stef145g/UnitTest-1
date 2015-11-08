//Confirmed Working 11/7/2015
//Primary Author: Jonathan Bedard

#ifndef SINGLE_TEST_H
#define SINGLE_TEST_H

#include "Datastructures.h"
#include "UnitTestExceptions.h"
#include "UnitTestLog.h"

namespace test
{
	typedef void (*testFunction)();

	//Single test
	class singleTest: public os::ptrComp
	{
		std::string testName;
	public:
		singleTest(std::string tn);
        virtual ~singleTest(){}

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
        virtual ~singleFunctionTest(){}
		void test() throw(os::smart_ptr<std::exception>);
	};
}

#endif