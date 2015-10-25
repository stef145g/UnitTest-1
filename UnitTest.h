//Confirmed Working 10/25/2015
//Primary Author: Jonathan Bedard

#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "Datastructures.h"
#include "UnitTestLog.h"
#include "masterTestHolder.h"
#include "UnitTestExceptions.h"
#include "TestSuite.h"
#include <iostream>
#include <exception>

namespace test
{
	//Global Status Functions
	void startTests();
	void endTestsError(os::smart_ptr<std::exception> except);
	void endTestsSuccess();

	void testInit();
}

#endif