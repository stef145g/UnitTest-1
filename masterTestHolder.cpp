//Confirmed Working 11/7/2015
//Primary Author: Jonathan Bedard

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
	void libraryTests::runTests() throw(os::smart_ptr<std::exception>)
	{
		suitesCompleted=0;
		suitesRun=0;

		//Suite loop
		try
		{
			suiteList.resetTraverse();
			for(auto it = suiteList.getFirst();it;it=it->getNext())
			{
				os::smart_ptr<exception> grabbed_exception;
				it->getData()->logBegin();
				try
				{
					it->getData()->runTests();
					suitesRun++;
				}
				catch (os::smart_ptr<exception> e1){grabbed_exception = e1;}
				catch (exception& e2){grabbed_exception = os::smart_ptr<exception>(&e2);}
				catch (...){grabbed_exception = os::smart_ptr<exception>(new test::unknownException("masterTestHolder.cpp, libraryTests::runTests()"),shared_type);}

				if(it->getData()->logEnd(grabbed_exception))
					suitesCompleted++;
			}
		}
		catch (os::smart_ptr<exception> e1){throw e1;}
		catch (exception& e2){throw os::smart_ptr<exception>(&e2);}
		catch (...){throw os::smart_ptr<exception>(new test::unknownException("masterTestHolder.cpp, libraryTests::runTests()"),shared_type);}
	}
	//Begin the library tests
	void libraryTests::logBegin()
	{
		testout<<LIB_DIV<<endl;
		testout<<"\t\t"<<libName<<endl;
		testout<<LIB_DIV<<endl<<endl;
	}
	//End and log end of library tests
	bool libraryTests::logEnd(os::smart_ptr<std::exception> except)
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
	bool masterTestHolder::runTests() throw(os::smart_ptr<std::exception>)
	{
		libsCompleted = 0;
		libsRun = 0;

		//Main Loop
		try
		{
			libraryList.resetTraverse();
			for(auto it = libraryList.getFirst();it;it=it->getNext())
			{
				os::smart_ptr<exception> grabbed_exception;
				it->getData()->logBegin();
				try
				{
					it->getData()->runTests();
					libsRun++;
				}
				catch (os::smart_ptr<exception> e1){grabbed_exception = e1;}
				catch (exception& e2){grabbed_exception = os::smart_ptr<exception>(&e2);}
				catch (...){grabbed_exception = os::smart_ptr<exception>(new test::unknownException("masterTestHolder.cpp, masterTestHolder::runTests()"),shared_type);}

				if(it->getData()->logEnd(grabbed_exception))
					libsCompleted++;
			}
		}
		catch (os::smart_ptr<exception> e1){throw e1;}
		catch (exception& e2){throw os::smart_ptr<exception>(&e2);}
		catch (...){throw os::smart_ptr<exception>(new test::unknownException("masterTestHolder.cpp, masterTestHolder::runTests()"),shared_type);}

		return !(libsCompleted-libraryList.size());
	}
	

#endif
