//Confirmed Working 10/25/2015
//Primary Author: Jonathan Bedard

#ifndef UNIT_TEST_CPP
#define UNIT_TEST_CPP

#include <iostream>
#include "UnitTest.h"

using namespace std;
using namespace os;
using namespace test;

#ifndef MAIN
#define MAIN

//Entry Function
int main(int argc,char** argv)
{
	startTests();

	endTestsSuccess();
	return 0;
}

#endif

#endif
