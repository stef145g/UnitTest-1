//Confirmed Working 12/20/2015
//Primary Author: Jonathan Bedard

#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "Datastructures.h"
#include "UnitTestExceptions.h"
#include "UnitTestLog.h"
#include "singleTest.h"

namespace test
{
	//Datastructures Library Test
	class testSuite
	{
		std::string suiteName;
		os::smartSet<singleTest> testList;

		int testsCompleted;
		int testsRun;
	public:
		testSuite(std::string sn);
        virtual ~testSuite(){}
		void runTests() throw(os::smart_ptr<std::exception>);

		void logBegin();
		bool logEnd(os::smart_ptr<std::exception> except = NULL);

		int getNumTests() const {return testList.size();}
		int getNumSuccess() const {return testsCompleted;}
		int getNumRun() const {return testsRun;}

		
		void pushTest(os::smart_ptr<singleTest> tst){testList.insert(tst);}
		void removeTest(os::smart_ptr<singleTest> tst){testList.findDelete(tst);}
		virtual void pushTest(std::string str,testFunction tst){pushTest(os::smart_ptr<singleTest>(new singleFunctionTest(str,tst),os::shared_type));}

		bool operator==(const testSuite& lt) const {return suiteName==lt.suiteName;}
		bool operator>(const testSuite& lt) const {return suiteName>lt.suiteName;}
		bool operator<(const testSuite& lt) const {return suiteName<lt.suiteName;}
		bool operator>=(const testSuite& lt) const {return suiteName>=lt.suiteName;}
		bool operator<=(const testSuite& lt) const {return suiteName<=lt.suiteName;}
	};
}

#endif