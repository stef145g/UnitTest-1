//Confirmed Working 11/2/2015
//Primary Author: Jonathan Bedard

#ifndef MASTER_TEST_HOLDER_H
#define MASTER_TEST_HOLDER_H

#include "Datastructures.h"
#include "UnitTestLog.h"
#include "TestSuite.h"
#include <iostream>
#include <string>

namespace test
{
	class masterTestHolder;

	//Library
	class libraryTests
	{
	private:
		std::string libName;
		os::smartSet<testSuite> suiteList;
		int suitesCompleted;
		int suitesRun;

	public:
		libraryTests(std::string ln);
		void runTests() throw(os::smart_ptr<std::exception>);

		void logBegin();
		bool logEnd(os::smart_ptr<std::exception> except = NULL);

		int getNumSuites() const {return suiteList.size();}
		int getNumSuccess() const {return suitesCompleted;}
		int getNumRun() const {return suitesRun;}

		void pushSuite(os::smart_ptr<testSuite> suite){suiteList.insert(suite);}
		void removeSuite(os::smart_ptr<testSuite> suite){suiteList.findDelete(suite);}

		bool operator==(const libraryTests& lt) const {return libName==lt.libName;}
		bool operator>(const libraryTests& lt) const {return libName>lt.libName;}
		bool operator<(const libraryTests& lt) const {return libName<lt.libName;}
		bool operator>=(const libraryTests& lt) const {return libName>=lt.libName;}
		bool operator<=(const libraryTests& lt) const {return libName<=lt.libName;}
	};
	//Master Test Holder
	class masterTestHolder
	{
	private:
		os::smartSet<libraryTests> libraryList;
		int libsCompleted;
		int libsRun;

		masterTestHolder();
	public:
		static os::smart_ptr<masterTestHolder> singleton();
		bool runTests() throw(os::smart_ptr<std::exception>);
		int getNumLibs() const {return libraryList.size();}
		int getNumSuccess() const {return libsCompleted;}
		int getNumRun() const {return libsRun;}
		void pushLibrary(os::smart_ptr<libraryTests> lib){libraryList.insert(lib);}
		void removeLibrary(os::smart_ptr<libraryTests> lib){libraryList.findDelete(lib);}
	};
}

#endif