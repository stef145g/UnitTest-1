/**
 * @file   masterTestHolder.cpp
 * @Author Jonathan Bedard
 * @date   5/14/2016
 * @brief  Library tests, masterTestHolder singleton implementations
 * @bug No known bugs.
 *
 * This file contains implementations for the library
 * test base class and test::masterTestHolder singleton
 * class.  Consult masterTestHolder.h for details.
 *
 */

///@cond INTERNAL
  
#ifndef MASTER_TEST_HOLDER_CPP
#define MASTER_TEST_HOLDER_CPP

#include "UnitTest.h"
#include "masterTestHolder.h"
#include "DatastructuresTest.h"

using namespace std;
using namespace os;
using namespace test;

/*================================================================
	libraryTests
================================================================*/

#define LIB_DIV   "\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

	//Constructor
	libraryTests::libraryTests(std::string ln):
		suiteList(sorted_set)
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
			for(auto it = suiteList.getFirst();it;it=it->getNext())
			{
				os::errorPointer grabbed_exception;
				it->getData()->logBegin();
				it->getData()->onSetup();
				try
				{
					it->getData()->runTests();
					suitesRun++;
				}
				catch (os::errorPointer e1){grabbed_exception = e1;}
				catch (exception& e2){grabbed_exception = os::errorPointer(&e2);}
				catch (...){grabbed_exception = os::errorPointer(new test::unknownException("masterTestHolder.cpp, libraryTests::runTests()"),shared_type);}
				
				it->getData()->onTeardown();
				if(it->getData()->logEnd(grabbed_exception))
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

/*================================================================
	masterTestHolder
================================================================*/

	static os::smart_ptr<masterTestHolder> self=NULL;
	//Constructor (private!)
	masterTestHolder::masterTestHolder():
		libraryList(sorted_set)
	{
		libsCompleted = 0;
		libsRun = 0;
	}
	//Return the singleton instance
	os::smart_ptr<masterTestHolder> masterTestHolder::singleton()
	{
		if(self==NULL)
		{
			self = os::smart_ptr<masterTestHolder>(new masterTestHolder(),shared_type);
			self->pushLibrary(os::smart_ptr<libraryTests>(new DatastructuresLibraryTest(),os::shared_type));
		};
		return self;
	}
	//Runs all tests
	bool masterTestHolder::runTests() throw(os::errorPointer)
	{
		libsCompleted = 0;
		libsRun = 0;

		//Main Loop
		try
		{
			for(auto it = libraryList.getFirst();it;it=it->getNext())
			{
				os::errorPointer grabbed_exception;
				it->getData()->logBegin();
				it->getData()->onSetup();
				try
				{
					it->getData()->runTests();
					libsRun++;
				}
				catch (os::errorPointer e1){grabbed_exception = e1;}
				catch (exception& e2){grabbed_exception = os::errorPointer(&e2);}
				catch (...){grabbed_exception = os::errorPointer(new test::unknownException("masterTestHolder.cpp, masterTestHolder::runTests()"),shared_type);}

				it->getData()->onTeardown();
				if(it->getData()->logEnd(grabbed_exception))
					libsCompleted++;
			}
		}
		catch (os::errorPointer e1){throw e1;}
		catch (exception& e2){throw os::errorPointer(&e2);}
		catch (...){throw os::errorPointer(new test::unknownException("masterTestHolder.cpp, masterTestHolder::runTests()"),shared_type);}

		return !(libsCompleted-libraryList.size());
	}
	

#endif

///@endcond