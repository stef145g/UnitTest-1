/**
 * @file   testSuite.cpp
 * @Author Jonathan Bedard
 * @date   8/14/2016
 * @brief  Single test class
 * @bug No known bugs.
 *
 * This file contains declarations for a
 * test suite.  Consult testSuite.h for
 * details.
 *
 */

///@cond INTERNAL

#ifndef TEST_SUITE_CPP
#define TEST_SUITE_CPP

#include "UnitTest.h"

using namespace os;
using namespace std;
using namespace test;

/*================================================================
	DatastructuresLibraryTest
================================================================*/

	//Constructor
	testSuite::testSuite(std::string sn)
	{
		suiteName = sn;

		testsCompleted = 0;
		testsRun = 0;
	}
	//Run all tests
	void testSuite::runTests() throw(os::errorPointer)
	{
		testsCompleted = 0;
		testsRun = 0;

		//Test loop
		try
		{
			for(auto it = testList.first();it;++it)
			{
				os::errorPointer grabbed_exception;
				it->logBegin();
                testsRun++;
                
                //Setup
                try
                {
                    it->setupTest();
                }
                catch (os::errorPointer e1){grabbed_exception = e1;}
				catch (os::descriptiveException de){grabbed_exception = os::errorPointer(new os::descriptiveException(de),os::shared_type);}
                catch (exception e2){grabbed_exception = os::errorPointer(new exception(e2),os::shared_type);}
                catch (...){grabbed_exception = os::errorPointer(new test::unknownException("TestSuite.cpp, testSuite::runTests() (setup)"),shared_type);}
                
                //Only run test and teardown if the test was successful
                if(!grabbed_exception)
                {
                    //Run Test
                    try
                    {
                        it->test();
                    }
                    catch (os::errorPointer e1){grabbed_exception = e1;}
					catch (os::descriptiveException de){grabbed_exception = os::errorPointer(new os::descriptiveException(de),os::shared_type);}
                    catch (exception e2){grabbed_exception = os::errorPointer(new exception(e2),os::shared_type);}
                    catch (...){grabbed_exception = os::errorPointer(new test::unknownException("TestSuite.cpp, testSuite::runTests() (test)"),shared_type);}
                
                    //Teardown
                    if(grabbed_exception)
                    {
                        try
                        {
                            it->teardownTest();
                        }
                        catch (os::errorPointer e1){grabbed_exception = e1;}
						catch (os::descriptiveException de){grabbed_exception = os::errorPointer(new os::descriptiveException(de),os::shared_type);}
                        catch (exception e2){grabbed_exception = os::errorPointer(new exception(e2),os::shared_type);}
                        catch (...){grabbed_exception = os::errorPointer(new test::unknownException("TestSuite.cpp, testSuite::runTests() (teardown)"),shared_type);}
                    }
                    else
                    {
                        try
                        {
                            it->teardownTest();
                        }
                        catch (...){}
                    }
                }

				if(it->logEnd(grabbed_exception))
					testsCompleted++;
			}
		}
		catch (os::errorPointer e1){throw e1;}
		catch (os::descriptiveException de){throw os::errorPointer(new os::descriptiveException(de),os::shared_type);}
        catch (exception e2){throw os::errorPointer(new exception(e2),os::shared_type);}
		catch (...){throw os::errorPointer(new test::unknownException("TestSuite.cpp, testSuite::runTests()"),shared_type);}
	}
	#define SUITE_DIV   "\t\t--------------------------------------------------"
	//Print header
	void testSuite::logBegin()
	{
		testout<<SUITE_DIV<<endl;
		testout<<"\t\t\t"<<suiteName<<" Suite"<<endl;
		testout<<SUITE_DIV<<endl<<endl;
	}
	//Log end of test suite
	bool testSuite::logEnd(os::errorPointer except)
	{
		int state=0;
		if(getNumTests()-getNumSuccess()>0) state = 1;
		if(except!=NULL) state = 2;

		testout<<endl<<SUITE_DIV<<endl;

		//Successful run
		if(state==0) testout<<"\t\t\t"<<suiteName<<" Tests success!"<<endl;
		if(state==1) testout<<"\t\t\t"<<suiteName<<" Tests completed, with errors"<<endl;
		if(state==2)
		{
			testout<<"\t\t\tERROR in "<<suiteName<<endl;
			testout<<"\t\t\t"<<except->what()<<endl;
		}

		//Result
		testout<<endl<<"\t\t\tResults:"<<endl;
		testout<<"\t\t\t\tRan "<<getNumRun()<<" tests"<<endl;
		testout<<"\t\t\t\tof "<<getNumTests()<<" tested"<<endl;
		testout<<"\t\t\t\twith "<<getNumSuccess()<<" successful"<<endl;
		testout<<SUITE_DIV<<endl<<endl;

		//Return case
		if(state) return false;
		return true;
	}

#endif

///@endcond