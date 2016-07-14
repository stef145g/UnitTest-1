/**
 * @file   masterTestHolder.h
 * @Author Jonathan Bedard
 * @date   7/12/2016
 * @brief  masterTestHolder singleton
 * @bug No known bugs.
 *
 * This file contains declarations for the
 * test::masterTestHolder singleton class.
 * This file represents the top level of the Unit
 * Test driver classes.
 *
 */

#ifndef MASTER_TEST_HOLDER_H
#define MASTER_TEST_HOLDER_H

#include "Datastructures/Datastructures.h"
#include "UnitTestLog.h"
#include "TestSuite.h"
#include "libraryTests.h"
#include <iostream>
#include <string>

namespace test
{
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
		os::pointerAVLTree<libraryTests> libraryList;
		/** @brief Number of libraries successfully completed
		 */
		size_t libsCompleted;
		/** @brief Number of libraries attempted to run
		 */
		size_t libsRun;

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
		static masterTestHolder& singleton();
		/** @brief Runs all of the library tests
		 *
		 * Runs all library tests bound to this class.
		 * Each library should manage its own errors,
		 * but it is possible that this function
		 * will throw an error of type
		 * os::errorPointer.
		 *
		 * @return True if all the tests were successful, else, false
		 */
		bool runTests() throw(os::errorPointer);
		/** @brief Number of libraries in the set
		 * @return test::masterTestHolder::libraryList.size()
		 */
		size_t getNumLibs() const {return libraryList.size();}
		/** @brief Number of libraries successfully completed
		 * @return test::masterTestHolder::libsCompleted
		 */
		size_t getNumSuccess() const {return libsCompleted;}
		/** @brief Number of libraries attempted to run
		 * @return test::masterTestHolder::libsRun
		 */
		size_t getNumRun() const {return libsRun;}
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
		void removeLibrary(os::smart_ptr<libraryTests> lib){libraryList.remove(lib);}
	};
}

#endif