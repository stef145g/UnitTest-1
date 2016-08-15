/**
 * @file   libraryTests.h
 * @Author Jonathan Bedard
 * @date   8/14/2016
 * @brief  Library tests class
 * @bug No known bugs.
 *
 * This file contains declarations for the library
 * test base class, which each library should
 * re-implement to provide testing functionality.
 *
 */

#ifndef LIBRARY_TESTS_H
#define LIBRARY_TESTS_H

#include "Datastructures/Datastructures.h"
#include "unitTestLog.h"
#include "testSuite.h"
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
		os::pointerAVLTree<testSuite> suiteList;
		/** @brief Number of suites successfully completed
		 */
		size_t suitesCompleted;
		/** @brief Number of suites attempted to run
		 */
		size_t suitesRun;

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
		 * os::errorPointer.
		 *
		 * @return void
		 */
		void runTests() throw(os::errorPointer);
		/** @brief Runs on shutdown of the group
		 *
		 * Each library group calls this funciton as
		 * it starts up, allowing groups to
		 * define actions performed to setup
		 * the group.
		 *
		 * @return void
		 */
		virtual void onSetup(){}
		/** @brief Runs on teardown of the group
		 *
		 * Guranteed to run even if the group itself
		 * fails.  A custom tear-down for the group
		 * can re-impliment this class.
		 *
		 * @return void
		 */
		virtual void onTeardown(){}

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
		bool logEnd(os::errorPointer except = NULL);

		/** @brief Number of suites in the set
		 * @return test::libraryTests::suiteList.size()
		 */
		size_t getNumSuites() const {return suiteList.size();}
		/** @brief Number of suites successfully completed
		 * @return test::libraryTests::suitesCompleted
		 */
		size_t getNumSuccess() const {return suitesCompleted;}
		/** @brief Number of suites attempted to run
		 * @return test::libraryTests::suitesRun
		 */
		size_t getNumRun() const {return suitesRun;}

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
		void removeSuite(os::smart_ptr<testSuite> suite){suiteList.remove(suite);}

		#undef CURRENT_CLASS
		#define CURRENT_CLASS libraryTests
		/** @brief Compares two library test suites
		 * @param [in] cmp Element to compare
		 * @return 0 if equal, 1 if greater than, -1 if less than
		 */
		inline int compare(const libraryTests& cmp) const {return libName.compare(cmp.libName);}
		/** @brief size_t cast for the library
		 * @return size_t hash of the library
		 */
		inline operator size_t() const {return os::hashData(libName.c_str(),libName.length());}
		COMPARE_OPERATORS
	};
}

#endif