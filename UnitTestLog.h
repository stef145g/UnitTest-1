//Confirmed Working 10/25/2015
//Primary Author: Jonathan Bedard

#ifndef UNIT_TEST_LOG_H
#define UNIT_TEST_LOG_H

#include "Datastructures.h"
#include <iostream>

namespace test
{
	//OS Logger Streams
	extern os::smart_ptr<std::ostream> testout_ptr;
    extern os::smart_ptr<std::ostream> testerr_ptr;
	std::ostream& testout_func();
	std::ostream& testerr_func();
}

#ifndef testout
#define testout osout_func()
#endif
#ifndef testerr
#define testerr oserr_func()
#endif

#endif