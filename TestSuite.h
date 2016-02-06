/**
 * @file   testSuite.h
 * @Author Jonathan Bedard
 * @date   2/6/2016
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

#include "Datastructures.h"
#include "UnitTestExceptions.h"
#include "UnitTestLog.h"
#include "singleTest.h"

namespace test
{
	//Datastructures Library Test
	class testSuite
	{
		/** @brief Name of test suite
		 */
		std::string suiteName;
		/** @brief Set of tests
		 */
		os::smartSet<singleTest> testList;

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
		void runTests() throw(os::smart_ptr<std::exception>);

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
		bool logEnd(os::smart_ptr<std::exception> except = NULL);

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
		void removeTest(os::smart_ptr<singleTest> tst){testList.findDelete(tst);}
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

		/** @brief Equality comparison
		 *
		 * Compares two test::testSuite based on the suite
		 * name.  If the two names are equal, the suites are
		 * equal.
		 *
		 * @param [in] lt Reference to test::testSuite to be compared against
		 * @return this->suiteName==lt.suiteName
		 */
		bool operator==(const testSuite& lt) const {return suiteName==lt.suiteName;}
		/** @brief Not-equals comparison
		 *
		 * Compares two test::testSuite based on the library
		 * name.  If the two names are not-equal, the suites are
		 * not-equal.
		 *
		 * @param [in] lt Reference to test::testSuite to be compared against
		 * @return this->suiteName!=lt.suiteName
		 */
		bool operator!=(const testSuite& lt) const {return suiteName!=lt.suiteName;}
		/** @brief Greater-than comparison
		 *
		 * Compares two test::testSuite based on the library
		 * name.  If the name of this object is greater than
		 * the name of the reference object, return true.
		 *
		 * @param [in] lt Reference to test::testSuite to be compared against
		 * @return this->suiteName>lt.suiteName
		 */
		bool operator>(const testSuite& lt) const {return suiteName>lt.suiteName;}
		/** @brief Less-than comparison
		 *
		 * Compares two test::testSuite based on the library
		 * name.  If the name of this object is less than
		 * the name of the reference object, return true.
		 *
		 * @param [in] lt Reference to test::testSuite to be compared against
		 * @return this->suiteName<lt.suiteName
		 */
		bool operator<(const testSuite& lt) const {return suiteName<lt.suiteName;}
		/** @brief Greater-than or equal to comparison
		 *
		 * Compares two test::testSuite based on the library
		 * name.  If the name of this object is greater than or equal to
		 * the name of the reference object, return true.
		 *
		 * @param [in] lt Reference to test::testSuite to be compared against
		 * @return this->suiteName>=lt.suiteName
		 */
		bool operator>=(const testSuite& lt) const {return suiteName>=lt.suiteName;}
		/** @brief Less-than or equal to comparison
		 *
		 * Compares two test::testSuite based on the library
		 * name.  If the name of this object is less than or equal to
		 * the name of the reference object, return true.
		 *
		 * @param [in] lt Reference to test::testSuite to be compared against
		 * @return this->suiteName<=lt.suiteName
		 */
		bool operator<=(const testSuite& lt) const {return suiteName<=lt.suiteName;}
	};
}

#endif