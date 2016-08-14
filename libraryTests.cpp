/**
 * @file   libraryTests.cpp
 * @Author Jonathan Bedard
 * @date   8/12/2016
 * @brief  Library tests implementations
 * @bug No known bugs.
 *
 * This file contains implementations for the library
 * test base class.  Consult libraryTests.h for details.
 *
 */

///@cond INTERNAL
  
#ifndef LIBRARY_TESTS_CPP
#define LIBRARY_TESTS_CPP

#include "libraryTests.h"
#include "masterTestHolder.h"

using namespace std;
using namespace os;
using namespace test;

/*================================================================
	libraryTests
================================================================*/

#define LIB_DIV   "\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	//Constructor
	libraryTests::libraryTests(std::string ln)
	{
		libName = ln;
		suitesCompleted=0;
		suitesRun=0;
	}
	//Run the test battery
	void libraryTests::runTests() throw(os::errorPointer)
	{
		suitesCompleted=0;
		suitesRun=0;

		//Suite loop
		try
		{
			for(auto it = suiteList.first();it;++it)
			{
				os::errorPointer grabbed_exception;
				it->logBegin();
				it->onSetup();
				try
				{
					it->runTests();
					suitesRun++;
				}
				catch (os::errorPointer e1){grabbed_exception = e1;}
				catch (exception& e2){grabbed_exception = os::errorPointer(&e2);}
				catch (...){grabbed_exception = os::errorPointer(new test::unknownException("masterTestHolder.cpp, libraryTests::runTests()"),shared_type);}
				
				it->onTeardown();
				if(it->logEnd(grabbed_exception))
					suitesCompleted++;
			}
		}
		catch (os::errorPointer e1){throw e1;}
		catch (exception& e2){throw os::errorPointer(&e2);}
		catch (...){throw os::errorPointer(new test::unknownException("masterTestHolder.cpp, libraryTests::runTests()"),shared_type);}
	}
	//Begin the library tests
	void libraryTests::logBegin()
	{
		testout<<LIB_DIV<<endl;
		testout<<"\t\t"<<libName<<endl;
		testout<<LIB_DIV<<endl<<endl;
	}
	//End and log end of library tests
	bool libraryTests::logEnd(os::errorPointer except)
	{
		int state=0;
		if(getNumSuites()-getNumSuccess()>0) state = 1;
		if(except!=NULL) state = 2;

		testout<<endl<<LIB_DIV<<endl;

		//Successful run
		if(state==0) testout<<"\t\t"<<libName<<" Tests success!"<<endl;
		if(state==1) testout<<"\t\t"<<libName<<" Tests completed, with errors"<<endl;
		if(state==2)
		{
			testout<<"\t\tERROR in "<<libName<<endl;
			testout<<"\t\t"<<except->what()<<endl;
		}

		//Result
		testout<<endl<<"\t\tResults:"<<endl;
		testout<<"\t\t\tRan "<<getNumRun()<<" suites"<<endl;
		testout<<"\t\t\tof "<<getNumSuites()<<" tested"<<endl;
		testout<<"\t\t\twith "<<getNumSuccess()<<" successful"<<endl;
		testout<<LIB_DIV<<endl;

		//Return case
		if(state) return false;
		return true;
	}
	

#endif

///@endcond