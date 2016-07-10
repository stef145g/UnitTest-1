/**
 * @file   masterTestHolder.cpp
 * @Author Jonathan Bedard
 * @date   7/9/2016
 * @brief  masterTestHolder singleton implementations
 * @bug No known bugs.
 *
 * This file contains implementations for the
 * test::masterTestHolder singleton
 * class.  Consult masterTestHolder.h for details.
 *
 */

///@cond INTERNAL
  
#ifndef MASTER_TEST_HOLDER_CPP
#define MASTER_TEST_HOLDER_CPP

#include "masterTestHolder.h"

#include "UnitTest.h"
#include "DatastructuresTest.h"

using namespace std;
using namespace os;
using namespace test;

/*================================================================
	masterTestHolder
================================================================*/

	//Constructor (private!)
	masterTestHolder::masterTestHolder()
	{
		libsCompleted = 0;
		libsRun = 0;
	}
	//Return the singleton instance
	masterTestHolder& masterTestHolder::singleton()
	{
		static masterTestHolder sing;
		static bool flag=false;
		if(!flag)
		{
			sing.pushLibrary(os::smart_ptr<libraryTests>(new DatastructuresLibraryTest(),os::shared_type));
			flag=true;
		}
		return sing;
	}
	//Runs all tests
	bool masterTestHolder::runTests() throw(os::errorPointer)
	{
		libsCompleted = 0;
		libsRun = 0;

		//Main Loop
		try
		{
			for(auto it = libraryList.first();it;++it)
			{
				os::errorPointer grabbed_exception;
				it->logBegin();
				it->onSetup();
				try
				{
					it->runTests();
					libsRun++;
				}
				catch (os::errorPointer e1){grabbed_exception = e1;}
				catch (exception& e2){grabbed_exception = os::errorPointer(&e2);}
				catch (...){grabbed_exception = os::errorPointer(new test::unknownException("masterTestHolder.cpp, masterTestHolder::runTests()"),shared_type);}

				it->onTeardown();
				if(it->logEnd(grabbed_exception))
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