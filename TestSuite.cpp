//Confirmed Working 12/20/2015
//Primary Author: Jonathan Bedard

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
	void testSuite::runTests() throw(os::smart_ptr<std::exception>)
	{
		testsCompleted = 0;
		testsRun = 0;

		//Test loop
		try
		{
			testList.resetTraverse();
			for(auto it = testList.getFirst();it;it=it->getNext())
			{
				os::smart_ptr<exception> grabbed_exception;
				it->getData()->logBegin();
                testsRun++;
                
                //Setup
                try
                {
                    it->getData()->setupTest();
                }
                catch (os::smart_ptr<exception> e1){grabbed_exception = e1;}
                catch (exception& e2){grabbed_exception = os::smart_ptr<exception>(new exception(e2),os::shared_type);}
                catch (...){grabbed_exception = os::smart_ptr<exception>(new test::unknownException("TestSuite.cpp, testSuite::runTests() (setup)"),shared_type);}
                
                //Only run test and teardown if the test was successful
                if(!grabbed_exception)
                {
                    //Run Test
                    try
                    {
                        it->getData()->test();
                    }
                    catch (os::smart_ptr<exception> e1){grabbed_exception = e1;}
                    catch (exception& e2){grabbed_exception = os::smart_ptr<exception>(new exception(e2),os::shared_type);}
                    catch (...){grabbed_exception = os::smart_ptr<exception>(new test::unknownException("TestSuite.cpp, testSuite::runTests() (test)"),shared_type);}
                
                    //Teardown
                    if(grabbed_exception)
                    {
                        try
                        {
                            it->getData()->teardownTest();
                        }
                        catch (os::smart_ptr<exception> e1){grabbed_exception = e1;}
                        catch (exception& e2){grabbed_exception = os::smart_ptr<exception>(new exception(e2),os::shared_type);}
                        catch (...){grabbed_exception = os::smart_ptr<exception>(new test::unknownException("TestSuite.cpp, testSuite::runTests() (teardown)"),shared_type);}
                    }
                    else
                    {
                        try
                        {
                            it->getData()->teardownTest();
                        }
                        catch (...){}
                    }
                }

				if(it->getData()->logEnd(grabbed_exception))
					testsCompleted++;
			}
		}
		catch (os::smart_ptr<exception> e1){throw e1;}
        catch (exception& e2){throw os::smart_ptr<exception>(new exception(e2),os::shared_type);}
		catch (...){throw os::smart_ptr<exception>(new test::unknownException("TestSuite.cpp, testSuite::runTests()"),shared_type);}
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
	bool testSuite::logEnd(os::smart_ptr<std::exception> except)
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