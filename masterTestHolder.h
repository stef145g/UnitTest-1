/**
 * @file   masterTestHolder.h
 * @Author Jonathan Bedard
 * @date   2/6/2016
 * @brief  Library tests, masterTestHolder singleton
 * @bug No known bugs.
 *
 * This file contains declarations for the library
 * test base class and test::masterTestHolder singleton
 * class.  This file represents the top level of the Unit
 * Test driver classes.
 *
 */

#ifndef MASTER_TEST_HOLDER_H
#define MASTER_TEST_HOLDER_H

#include "Datastructures.h"
#include "UnitTestLog.h"
#include "TestSuite.h"
#include <iostream>
#include <string>

namespace test
{
	///@cond INTERNAL
	class masterTestHolder;
	///@endcond

	/** @brief Library test group
	 *
	 * This class contains a set of test suites
	 * which are designed to a specific library.
	 * Each library must define it's own version
	 * of this class in-order to be tested.
	 */
	class libraryTests
	{
	private:
		/** @brief Name of library to be tested
		 */
		std::string libName;
		/** @brief Set of test suites
		 */
		os::smartSet<testSuite> suiteList;
		/** @brief Number of suites successfully completed
		 */
		int suitesCompleted;
		/** @brief Number of suites attempted to run
		 */
		int suitesRun;

	public:
		/** @brief Library test constructor
		 *
		 * This constructor initializes the
		 * number of suites completed and
		 * number of suites run to 0, along with
		 * sets the name of library being tested.
		 *
		 * @param [in] ln Name of library to be tested
		 */
		libraryTests(std::string ln);
		/** @brief Virtual destructor
		 *
		 * Destructor must be virtual, if an object
		 * of this type is deleted, the destructor
		 * of the type which inherits this class should
		 * be called.
		 */
        virtual ~libraryTests(){}
		/** @brief Runs all of the test suites
		 *
		 * Runs all test suites bound to this class.
		 * Each suite should manage its own errors,
		 * but it is possible that this function
		 * will throw an error of type
		 * os::smart_ptr<std::exception>.
		 *
		 * @return void
		 */
		void runTests() throw(os::smart_ptr<std::exception>);

		/** @brief Logs the beginning of a library test
		 *
		 * Outputs the name of the library to be tested
		 * along with a line break made of '+' characters.
		 *
		 * @return void
		 */
		void logBegin();
		/** @brief Logs the end of a library test
		 *
		 * Outputs the number of suites run and how many
		 * of these suites were both successful and how
		 * many of these suites failed.
		 *
		 * @return True if all suites successful, else false 
		 */
		bool logEnd(os::smart_ptr<std::exception> except = NULL);

		/** @brief Number of suites in the set
		 * @return test::libraryTests::suiteList.size()
		 */
		int getNumSuites() const {return suiteList.size();}
		/** @brief Number of suites successfully completed
		 * @return test::libraryTests::suitesCompleted
		 */
		int getNumSuccess() const {return suitesCompleted;}
		/** @brief Number of suites attempted to run
		 * @return test::libraryTests::suitesRun
		 */
		int getNumRun() const {return suitesRun;}

		/** @brief Add suite to the set
		 *
		 * Adds a test::testSuite to the set of
		 * suites to be tested.
		 *
		 * @param [in] suite Test suite to be added to set
		 * @return void
		 */
		void pushSuite(os::smart_ptr<testSuite> suite){suiteList.insert(suite);}
		/** @brief Remove suite from the set
		 *
		 * Removes a test::testSuite from the set of
		 * suites to be tested.
		 *
		 * @param [in] suite Test suite to be removed from the set
		 * @return void
		 */
		void removeSuite(os::smart_ptr<testSuite> suite){suiteList.findDelete(suite);}

		/** @brief Equality comparison
		 *
		 * Compares two test::libraryTest based on the library
		 * name.  If the two names are equal, the library tests are
		 * equal.
		 *
		 * @param [in] lt Reference to test::libraryTest to be compared against
		 * @return this->libName==lt.libName
		 */
		bool operator==(const libraryTests& lt) const {return libName==lt.libName;}
		/** @brief Not-equals comparison
		 *
		 * Compares two test::libraryTest based on the library
		 * name.  If the two names are not-equal, the library tests are
		 * not-equal.
		 *
		 * @param [in] lt Reference to test::libraryTest to be compared against
		 * @return this->libName!=lt.libName
		 */
		bool operator!=(const libraryTests& lt) const {return libName!=lt.libName;}
		/** @brief Greater-than comparison
		 *
		 * Compares two test::libraryTest based on the library
		 * name.  If the name of this object is greater than
		 * the name of the reference object, return true.
		 *
		 * @param [in] lt Reference to test::libraryTest to be compared against
		 * @return this->libName>lt.libName
		 */
		bool operator>(const libraryTests& lt) const {return libName>lt.libName;}
		/** @brief Less-than comparison
		 *
		 * Compares two test::libraryTest based on the library
		 * name.  If the name of this object is less than
		 * the name of the reference object, return true.
		 *
		 * @param [in] lt Reference to test::libraryTest to be compared against
		 * @return this->libName<lt.libName
		 */
		bool operator<(const libraryTests& lt) const {return libName<lt.libName;}
		/** @brief Greater-than or equal to comparison
		 *
		 * Compares two test::libraryTest based on the library
		 * name.  If the name of this object is greater than or equal to
		 * the name of the reference object, return true.
		 *
		 * @param [in] lt Reference to test::libraryTest to be compared against
		 * @return this->libName>=lt.libName
		 */
		bool operator>=(const libraryTests& lt) const {return libName>=lt.libName;}
		/** @brief Less-than or equal to comparison
		 *
		 * Compares two test::libraryTest based on the library
		 * name.  If the name of this object is less than or equal to
		 * the name of the reference object, return true.
		 *
		 * @param [in] lt Reference to test::libraryTest to be compared against
		 * @return this->libName<=lt.libName
		 */
		bool operator<=(const libraryTests& lt) const {return libName<=lt.libName;}
	};
	/** @brief Unit Test singleton
	 *
	 * This class contains a set of library tests.
	 * Every library test must add itself to this class
	 * in-order to be tested.  The test::masterTestHolder::runTests()
	 * function runs all of the library tests.
	 */
	class masterTestHolder
	{
	private:
		/** @brief Set of library tests
		 */
		os::smartSet<libraryTests> libraryList;
		/** @brief Number of libraries successfully completed
		 */
		int libsCompleted;
		/** @brief Number of libraries attempted to run
		 */
		int libsRun;

		/** @brief Private constructor
		 *
		 * The test::masterTestHolder class
		 * is a singleton class.  This constructor
		 * initializes the number of libraries completed
		 * and number of libraries run to 0.
		 */
		masterTestHolder();
	public:
		/** @brief Virtual destructor
		 *
		 * Destructor must be virtual, if an object
		 * of this type is deleted, the destructor
		 * of the type which inherits this class should
		 * be called.
		 */
        virtual ~masterTestHolder(){}
        
		/** @brief Singleton access
		 *
		 * This function constructs the single reference
		 * to the test::masterTestHolder class if needed.
		 * Then, it returns a pointer to this single reference.
		 *
		 * @return Singleton reference to test::masterTestHolder
		 */
		static os::smart_ptr<masterTestHolder> singleton();
		/** @brief Runs all of the library tests
		 *
		 * Runs all library tests bound to this class.
		 * Each library should manage its own errors,
		 * but it is possible that this function
		 * will throw an error of type
		 * os::smart_ptr<std::exception>.
		 *
		 * @return True if all the tests were successful, else, false
		 */
		bool runTests() throw(os::smart_ptr<std::exception>);
		/** @brief Number of libraries in the set
		 * @return test::masterTestHolder::libraryList.size()
		 */
		int getNumLibs() const {return libraryList.size();}
		/** @brief Number of libraries successfully completed
		 * @return test::masterTestHolder::libsCompleted
		 */
		int getNumSuccess() const {return libsCompleted;}
		/** @brief Number of libraries attempted to run
		 * @return test::masterTestHolder::libsRun
		 */
		int getNumRun() const {return libsRun;}
		/** @brief Add library to the set
		 *
		 * Adds a test::libraryTests to the set of
		 * library tests to be tested.
		 *
		 * @param [in] lib Library test to be added to set
		 * @return void
		 */
		void pushLibrary(os::smart_ptr<libraryTests> lib){libraryList.insert(lib);}
		/** @brief Remove library from the set
		 *
		 * Removes a test::libraryTests from the set of
		 * library tests to be tested.
		 *
		 * @param [in] lib Library test to be removed from the set
		 * @return void
		 */
		void removeLibrary(os::smart_ptr<libraryTests> lib){libraryList.findDelete(lib);}
	};
}

#endif