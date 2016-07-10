/**
 * @file   testSuite.h
 * @Author Jonathan Bedard
 * @date   7/9/2016
 * @brief  Single test class
 * @bug No known bugs.
 *
 * This file contains declarations for a
 * test suite.  Test suites contain
 * lists of unit tests.
 *
 */

#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "Datastructures/Datastructures.h"
#include "Exceptions/Exceptions.h"
#include "UnitTestLog.h"
#include "singleTest.h"
#include "singleFunctionTest.h"

namespace test
{
	/** @brief Test suite
	 *
	 * Defines a named test suite
	 * which has a selection of
	 * tests to run.
	 */
	class testSuite
	{
		/** @brief Name of test suite
		 */
		std::string suiteName;
		/** @brief Set of tests
		 */
		os::pointerUnsortedList<singleTest> testList;

		/** @brief Number of tests successfully completed
		 */
		int testsCompleted;
		/** @brief Number of tests attempted to run
		 */
		int testsRun;
	public:
		/** @brief Test suite constructor
		 *
		 * This constructor initializes the
		 * number of tests completed and
		 * number of tests run to 0, along with
		 * sets the name of suite being tested.
		 *
		 * @param [in] sn Name of suite to be tested
		 */
		testSuite(std::string sn);
		/** @brief Virtual destructor
		 *
		 * Destructor must be virtual, if an object
		 * of this type is deleted, the destructor
		 * of the type which inherits this class should
		 * be called.
		 */
        virtual ~testSuite(){}
		/** @brief Runs all of the tests
		 *
		 * Runs all tests bound to this class.
		 * This function catches exceptions thrown
		 * by test::singleTest and logs the results.
		 *
		 * @return void
		 */
		void runTests() throw(os::errorPointer);
		/** @brief Runs on shutdown
		 *
		 * Each suite calls this funciton as
		 * it starts up, allowing suites to
		 * define actions performed to setup
		 * the suite.
		 *
		 * @return void
		 */
		virtual void onSetup(){}
		/** @brief Runs on teardown of the suite
		 *
		 * Guranteed to run even if the suite itself
		 * fails.  A custom tear-down for the suite
		 * can re-impliment this class.
		 *
		 * @return void
		 */
		virtual void onTeardown(){}

		/** @brief Logs the beginning of a suite test
		 *
		 * Outputs the name of the suite to be tested
		 * along with a line break made of '-' characters.
		 *
		 * @return void
		 */
		void logBegin();
		/** @brief Logs the end of a suite test
		 *
		 * Outputs the number of tests run and how many
		 * of these tests were both successful and how
		 * many of these tests failed.
		 *
		 * @return True if all tests successful, else false 
		 */
		bool logEnd(os::errorPointer except = NULL);

		/** @brief Number of tests in the set
		 * @return test::testSuite::testList.size()
		 */
		int getNumTests() const {return testList.size();}
		/** @brief Number of tests successfully completed
		 * @return test::testSuite::testsCompleted
		 */
		int getNumSuccess() const {return testsCompleted;}
		/** @brief Number of tests attempted to run
		 * @return test::testSuite::testsRun
		 */
		int getNumRun() const {return testsRun;}

		/** @brief Add test to the set
		 *
		 * Adds a test::singleTest to the set of
		 * tests to be tested.
		 *
		 * @param [in] tst Test to be added to set
		 * @return void
		 */
		void pushTest(os::smart_ptr<singleTest> tst){testList.insert(tst);}
		/** @brief Remove test to the set
		 *
		 * Removes a test::singleTest from the set of
		 * tests to be tested.
		 *
		 * @param [in] tst Test to be removed from the set
		 * @return void
		 */
		void removeTest(os::smart_ptr<singleTest> tst){testList.remove(tst);}
		/** @brief Add test to the set
		 *
		 * Adds a test::testFunction to the set of
		 * tests to be tested.  Constructs a test::singleTest
		 * from a function and a test name
		 *
		 * @param [in] str Test name
		 * @param [in] tst Function which defines test
		 * @return void
		 */
		virtual void pushTest(std::string str,testFunction tst){pushTest(os::smart_ptr<singleTest>(new singleFunctionTest(str,tst),os::shared_type));}

		#undef CURRENT_CLASS
		#define CURRENT_CLASS testSuite
		/** @brief Compares two library test suites
		 * @param [in] cmp Element to compare
		 * @return 0 if equal, 1 if greater than, -1 if less than
		 */
		inline int compare(const testSuite& cmp) const {return suiteName.compare(cmp.suiteName);}
		/** @brief size_t cast for the library
		 * @return size_t hash of the library
		 */
		operator size_t() const;
		COMPARE_OPERATORS
	};
}

#endif