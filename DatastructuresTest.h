/**
 * @file   DatastructuresTest.h
 * @author Jonathan Bedard
 * @date   7/9/2016
 * @brief  Datastructures library test
 * @bug No known bugs.
 *
 * Contains the declaration of the Datastructures
 * library test.  Note that this library test
 * is automatically added to all Unit Test executables.
 */

 ///@cond INTERNAL
 
#ifndef DATASTRUCTURES_TEST_H
#define DATASTRUCTURES_TEST_H

#include "Datastructures/Datastructures.h"
#include "UnitTest.h"

namespace test
{
	//Datastructures Library Test
	class DatastructuresLibraryTest: public libraryTests
	{
	public:
		DatastructuresLibraryTest();
        virtual ~DatastructuresLibraryTest(){}
	};
}

#endif

///@endcond