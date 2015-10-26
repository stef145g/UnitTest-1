//Confirmed Working 10/26/2015
//Primary Author: Jonathan Bedard

#ifndef DATASTRUCTURES_TEST_CPP
#define DATASTRUCTURES_TEST_CPP

#include "DatastructuresTest.h"
#include <string>

using namespace os;
using namespace std;
using namespace test;

/*================================================================
	smart_ptr Test
================================================================*/

	//Demonstrate C deletion
	void c_deletion(void *v){delete (int*)v;}

	void refCountTest(smart_pointer_type typ) throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, refCountTest(), ";
		if(typ==shared_type) locString+="shared_type";
		else if(typ==shared_type_array) locString+="shared_type_array";
		else if(typ==shared_type_dynamic_delete) locString+="shared_type_dynamic_delete";
		else throw os::smart_ptr<std::exception>(new generalTestException("Cannot run this function with this type",locString+"null_type"),shared_type);

		smart_ptr<int> temp1,temp2;

		//NULL pointer should have NULL ref count
		if(temp1.getRefCount()!=NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("Non-NULL reference count",locString),shared_type);

		if(typ==shared_type_array) temp1 = smart_ptr<int>(new int[5],shared_type_array);
		else if(typ==shared_type_dynamic_delete) temp1 = smart_ptr<int>(new int(1),&c_deletion);
		else temp1 = smart_ptr<int>(new int(1),shared_type);

		//Should have a reference count
		if(temp1.getRefCount()==NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("NULL reference count",locString),shared_type);

		//Reference count should be 1
		if(*(temp1.getRefCount())!=1)
			throw os::smart_ptr<std::exception>(new generalTestException("Reference count is "+to_string(*(temp1.getRefCount()))+" expected 1",locString),shared_type);

		//Reference count should be 2
		temp2 = temp1;
		if(*(temp1.getRefCount())!=2)
			throw os::smart_ptr<std::exception>(new generalTestException("Reference count is "+to_string(*(temp1.getRefCount()))+" expected 2",locString),shared_type);

		//Reference count should be 1
		temp1=NULL;
		if(*(temp2.getRefCount())!=1)
			throw os::smart_ptr<std::exception>(new generalTestException("Reference count is "+to_string(*(temp2.getRefCount()))+" expected 1",locString),shared_type);

		//NULL pointer should have NULL ref count
		if(temp1.getRefCount()!=NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("Non-NULL reference count",locString),shared_type);

		//Should have a reference count
		if(temp2.getRefCount()==NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("NULL reference count",locString),shared_type);

		//NULL pointer should have NULL ref count
		temp2=NULL;
		if(temp2.getRefCount()!=NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("Non-NULL reference count",locString),shared_type);
	}
	void refCountTest_shared()throw(os::smart_ptr<std::exception>){refCountTest(shared_type);}
	void refCountTest_array()throw(os::smart_ptr<std::exception>){refCountTest(shared_type_array);}
	void refCountTest_dyndel()throw(os::smart_ptr<std::exception>){refCountTest(shared_type_dynamic_delete);}
	
	void compareNULL_type(smart_pointer_type typ) throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, compareNULL_type(smart_pointer_type typ), ";
		if(typ==raw_type) locString+="raw_type";
		else if(typ==shared_type) locString+="shared_type";
		else if(typ==shared_type_array) locString+="shared_type_array";
		else if(typ==shared_type_dynamic_delete) locString+="shared_type_dynamic_delete";
		else throw os::smart_ptr<std::exception>(new generalTestException("Cannot run this function with this type",locString+"null_type"),shared_type);
		
		smart_ptr<int> temp1;

		//Ensure it is NULL
		if(temp1.get()!=NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("Expected initial NULL",locString),shared_type);

		//Other methods of detecting NULL
		if(temp1)
			throw os::smart_ptr<std::exception>(new generalTestException("NULL comparison failed (cast int)",locString),shared_type);
		if(temp1!=NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("NULL comparison failed (comp null)",locString),shared_type);
		if(temp1.constGet()!=NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("NULL comparison failed (constGet)",locString),shared_type);

		//Attempt different methods of NULL casting
		int raw_val=1;
		for(int i=0;i<3;i++)
		{
			std::string cast_type;
			if(i==0)
				cast_type="Default Construct";
			else if(i==1)
				cast_type="Construct NULL";
			else if(i==2)
				cast_type="Set NULL";

			//Instantiate
			if(typ==raw_type) temp1 = smart_ptr<int>(&raw_val);
			else if(typ==shared_type_array) temp1 = smart_ptr<int>(new int[5],shared_type_array);
			else if(typ==shared_type_dynamic_delete) temp1 = smart_ptr<int>(new int(1),&c_deletion);
			else temp1 = smart_ptr<int>(new int(1),shared_type);

			//Ensure it isn't NULL
			if(temp1.get()==NULL)
				throw os::smart_ptr<std::exception>(new generalTestException("Expected instantiaze not NULL ("+cast_type+")",locString),shared_type);

			//Other methods of detecting not NULL
			if(!temp1)
				throw os::smart_ptr<std::exception>(new generalTestException("NULL comparison failed (cast int, "+cast_type,locString+")"),shared_type);
			if(temp1==NULL)
				throw os::smart_ptr<std::exception>(new generalTestException("NULL comparison failed (comp null, "+cast_type,locString+")"),shared_type);
			if(temp1.constGet()==NULL)
				throw os::smart_ptr<std::exception>(new generalTestException("NULL comparison failed (constGet, "+cast_type,locString+")"),shared_type);

			//Set NULL (3 ways)
			if(i==0) temp1=smart_ptr<int>();
			else if(i==1) temp1=smart_ptr<int>(NULL);
			else temp1=NULL;

			//Ensure it is NULL
			if(temp1.get()!=NULL)
				throw os::smart_ptr<std::exception>(new generalTestException("Expected NULL, "+cast_type,locString),shared_type);

			//Other methods of detecting NULL
			if(temp1)
				throw os::smart_ptr<std::exception>(new generalTestException("NULL comparison failed, "+cast_type+"(cast int)",locString),shared_type);
			if(temp1!=NULL)
				throw os::smart_ptr<std::exception>(new generalTestException("NULL comparison failed, "+cast_type+"(comp null)",locString),shared_type);
			if(temp1.constGet()!=NULL)
				throw os::smart_ptr<std::exception>(new generalTestException("NULL comparison failed, "+cast_type+"(constGet)",locString),shared_type);
			}
	}
	void compareNULL_raw() throw(os::smart_ptr<std::exception>){compareNULL_type(raw_type);}
	void compareNULL_shared() throw(os::smart_ptr<std::exception>){compareNULL_type(shared_type);}
	void compareNULL_array() throw(os::smart_ptr<std::exception>){compareNULL_type(shared_type_array);}
	void compareNULL_dyndel() throw(os::smart_ptr<std::exception>){compareNULL_type(shared_type_dynamic_delete);}

	void copyConstructor(smart_pointer_type typ) throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, copyConstructor(smart_pointer_type typ), ";
		if(typ==raw_type) locString+="raw_type";
		else if(typ==shared_type) locString+="shared_type";
		else if(typ==shared_type_array) locString+="shared_type_array";
		else if(typ==shared_type_dynamic_delete) locString+="shared_type_dynamic_delete";
		else locString+="null_type";

		smart_ptr<int> master,temp1;
		int temp_raw = 1;
		if(typ==raw_type) master = smart_ptr<int>(&temp_raw);
		else if(typ==shared_type) master = smart_ptr<int>(new int(1),shared_type);
		else if(typ==shared_type_array) master = smart_ptr<int>(new int[5],shared_type_array);
		else if(typ==shared_type_dynamic_delete) master = smart_ptr<int>(new int(1),&c_deletion);

		//Compare type with declared type
		if(master.getType()!=typ)
			throw os::smart_ptr<std::exception>(new generalTestException("Type bound improperly",locString),shared_type);

		//Check if temp1 is NULL
		if(temp1)
			throw os::smart_ptr<std::exception>(new generalTestException("Expected initial NULL",locString),shared_type);

		//Set temp1 and master
		temp1=master;

		//Compare types
		if(master.getType()!=temp1.getType())
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity type mis-match (=)",locString),shared_type);
		if(master.getRefCount()!=temp1.getRefCount())
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity ref-count mis-match (=)",locString),shared_type);
		if(master.getFunc()!=temp1.getFunc())
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity delete function mis-match (=)",locString),shared_type);
		if(master.get()!=temp1.get())
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity pointer mis-match (=)",locString),shared_type);
		if(master!=temp1)
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity compare mis-match (=)",locString),shared_type);

		//Set temp1 and master
		temp1=smart_ptr<int>(master);

		//Compare types
		if(master.getType()!=temp1.getType())
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity type mis-match (copy)",locString),shared_type);
		if(master.getRefCount()!=temp1.getRefCount())
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity ref-count mis-match (copy)",locString),shared_type);
		if(master.getFunc()!=temp1.getFunc())
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity delete function mis-match (copy)",locString),shared_type);
		if(master.get()!=temp1.get())
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity pointer mis-match (copy)",locString),shared_type);
		if(master!=temp1)
			throw os::smart_ptr<std::exception>(new generalTestException("Equalitity compare mis-match (copy)",locString),shared_type);
	}
	void copyConstructor_null() throw(os::smart_ptr<std::exception>){copyConstructor(null_type);}
	void copyConstructor_raw() throw(os::smart_ptr<std::exception>){copyConstructor(raw_type);}
	void copyConstructor_shared() throw(os::smart_ptr<std::exception>){copyConstructor(shared_type);}
	void copyConstructor_array() throw(os::smart_ptr<std::exception>){copyConstructor(shared_type_array);}
	void copyConstructor_dyndel() throw(os::smart_ptr<std::exception>){copyConstructor(shared_type_dynamic_delete);}

/*================================================================
	DatastructuresLibraryTest
================================================================*/

	//Constructor
	DatastructuresLibraryTest::DatastructuresLibraryTest():
		libraryTests("Datastructures")
	{
		os::smart_ptr<testSuite> trc = smart_ptr<testSuite>(new testSuite("smart_ptr"));
			trc->pushTest("Ref Count: Shared",&refCountTest_shared);
			trc->pushTest("Ref Count: Array",&refCountTest_array);
			trc->pushTest("Ref Count: Dynamic Delete",&refCountTest_shared);
			trc->pushTest("Compare NULL: Raw",&compareNULL_raw);
			trc->pushTest("Compare NULL: Shared",&compareNULL_shared);
			trc->pushTest("Compare NULL: Array",&compareNULL_array);
			trc->pushTest("Compare NULL: Dynamic Delete",&compareNULL_dyndel);
			trc->pushTest("Copy Constructor: NULL",&copyConstructor_null);
			trc->pushTest("Copy Constructor: Raw",&copyConstructor_raw);
			trc->pushTest("Copy Constructor: Shared",&copyConstructor_shared);
			trc->pushTest("Copy Constructor: Array",&copyConstructor_array);
			trc->pushTest("Copy Constructor: Dynamic Delete",&copyConstructor_dyndel);
		pushSuite(trc);

		trc = smart_ptr<testSuite>(new testSuite("list"));
		pushSuite(trc);
	}

#endif