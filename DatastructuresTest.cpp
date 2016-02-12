/**
 * @file   DatastructuresTest.cpp
 * @author Jonathan Bedard
 * @date   2/12/2016
 * @brief  Datastructures library test implementation
 * @bug No known bugs.
 *
 * Implements the Datastructures library test.
 * These tests are designed to guarantee the functionality
 * of each of the elements in the Datastructures library.
 */

 ///@cond INTERNAL
 
#ifndef DATASTRUCTURES_TEST_CPP
#define DATASTRUCTURES_TEST_CPP

#include "DatastructuresTest.h"
#include <string>
#include <list>

using namespace os;
using namespace std;
using namespace test;

/*================================================================
	smart_ptr Test
================================================================*/

	//Demonstrate C deletion
	void c_deletion(void *v){delete (int*)v;}
	void c_str_deletin(void *v){delete (string*) v;}

	void refCountTest(smart_pointer_type typ) throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, refCountTest(smart_pointer_type typ), ";
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

	void comparisonTest(smart_pointer_type typ) throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, comparisonTest(smart_pointer_type typ), ";
		if(typ==raw_type) locString+="raw_type";
		else if(typ==shared_type) locString+="shared_type";
		else if(typ==shared_type_array) locString+="shared_type_array";
		else if(typ==shared_type_dynamic_delete) locString+="shared_type_dynamic_delete";
		else locString+="null_type";

		smart_ptr<int> master;
		int temp_raw = 1;
		if(typ==raw_type) master = smart_ptr<int>(&temp_raw);
		else if(typ==shared_type) master = smart_ptr<int>(new int(1),shared_type);
		else if(typ==shared_type_array) master = smart_ptr<int>(new int[5],shared_type_array);
		else if(typ==shared_type_dynamic_delete) master = smart_ptr<int>(new int(1),&c_deletion);

		//Test with self first
		if(master!=master)
			throw os::smart_ptr<std::exception>(new generalTestException("!= with self returned unexpected value",locString),shared_type);
		if(!(master==master))
			throw os::smart_ptr<std::exception>(new generalTestException("== with self returned unexpected value",locString),shared_type);

		srand (time(NULL));

		//Preform 20 iterations to test
		for(int i=0;i<20;i++)
		{
			unsigned long cur_comp = rand();
			void* ptr_comp = (void*) cur_comp;

			//REALLY BAD PRACTICE
				//This is only to test comparison operators!
			smart_ptr<int> comp_ptr(cur_comp);

			//General == test
			bool v = (unsigned long)master.get()==cur_comp;
			bool rv = cur_comp==(unsigned long)master.get();
			if(v!=(master==cur_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr == long failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master==ptr_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr == void* failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master==comp_ptr))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr == smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(cur_comp==master))
				throw os::smart_ptr<std::exception>(new generalTestException("long == smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(ptr_comp==master))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr == void* failed: "+to_string(cur_comp),locString),shared_type);
			
			//General != test
			v = (unsigned long)master.get()!=cur_comp;
			rv = cur_comp!=(unsigned long)master.get();
			if(v!=(master!=cur_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr != long failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master!=ptr_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr != void* failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master!=comp_ptr))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr != smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(cur_comp!=master))
				throw os::smart_ptr<std::exception>(new generalTestException("long != smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(ptr_comp!=master))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr != void* failed: "+to_string(cur_comp),locString),shared_type);

			//General < test
			v = (unsigned long)master.get()<cur_comp;
			rv = cur_comp<(unsigned long)master.get();
            //cout<<v<<endl;
            //cout<<(master<cur_comp)<<endl;
			if(v!=(master<cur_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr < long failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master<ptr_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr < void* failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master<comp_ptr))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr < smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(cur_comp<master))
				throw os::smart_ptr<std::exception>(new generalTestException("long < smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(ptr_comp<master))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr < void* failed: "+to_string(cur_comp),locString),shared_type);

			//General > test
			v = (unsigned long)master.get()>cur_comp;
			rv = cur_comp>(unsigned long)master.get();
			if(v!=(master>cur_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr > long failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master>ptr_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr > void* failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master>comp_ptr))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr > smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(cur_comp>master))
				throw os::smart_ptr<std::exception>(new generalTestException("long > smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(ptr_comp>master))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr > void* failed: "+to_string(cur_comp),locString),shared_type);

			//General <= test
			v = (unsigned long)master.get()<=cur_comp;
			rv = cur_comp<=(unsigned long)master.get();
			if(v!=(master<=cur_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr <= long failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master<=ptr_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr <= void* failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master<=comp_ptr))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr <= smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(cur_comp<=master))
				throw os::smart_ptr<std::exception>(new generalTestException("long <= smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(ptr_comp<=master))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr <= void* failed: "+to_string(cur_comp),locString),shared_type);

			//General >= test
			v = (unsigned long)master.get()>=cur_comp;
			rv = cur_comp>=(unsigned long)master.get();
			if(v!=(master>=cur_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr >= long failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master>=ptr_comp))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr >= void* failed: "+to_string(cur_comp),locString),shared_type);
			if(v!=(master>=comp_ptr))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr >= smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(cur_comp>=master))
				throw os::smart_ptr<std::exception>(new generalTestException("long >= smart_ptr failed: "+to_string(cur_comp),locString),shared_type);
			if(rv!=(ptr_comp>=master))
				throw os::smart_ptr<std::exception>(new generalTestException("smart_ptr >= void* failed: "+to_string(cur_comp),locString),shared_type);
		}
	}
	void comparisonTest_null() throw(os::smart_ptr<std::exception>){comparisonTest(null_type);}
	void comparisonTest_raw() throw(os::smart_ptr<std::exception>){comparisonTest(raw_type);}
	void comparisonTest_shared() throw(os::smart_ptr<std::exception>){comparisonTest(shared_type);}
	void comparisonTest_array() throw(os::smart_ptr<std::exception>){comparisonTest(shared_type_array);}
    void comparisonTest_dyndel() throw(os::smart_ptr<std::exception>){comparisonTest(shared_type_dynamic_delete);}

	void derefTest(smart_pointer_type typ) throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, derefTest(smart_pointer_type typ), ";
		if(typ==raw_type) locString+="raw_type";
		else if(typ==shared_type) locString+="shared_type";
		else if(typ==shared_type_array) locString+="shared_type_array";
		else if(typ==shared_type_dynamic_delete) locString+="shared_type_dynamic_delete";
		else throw os::smart_ptr<std::exception>(new generalTestException("Cannot run this function with this type",locString+"null_type"),shared_type);

		smart_ptr<string> ptr;
		string obj;

		if(typ == raw_type) ptr = smart_ptr<string>(&obj);
		else if(typ==shared_type_array) ptr = smart_ptr<string>(new string[5],shared_type_array);
		else if(typ==shared_type_dynamic_delete) ptr = smart_ptr<string>(new string(""),&c_deletion);
		else ptr = smart_ptr<string>(new string(""),shared_type);

		if(!ptr)
			throw os::smart_ptr<std::exception>(new generalTestException("Pointer unexpected NULL",locString),shared_type);

		for(int i = 0;i<3;i++)
		{
			string lInfo=", init with ";
			if(i==1)
			{
				*ptr="test";
				lInfo+="operator";
			}
			else if(i==2)
			{
				ptr[0]="test";
				lInfo+="array";
			}
			else
			{
				*ptr.get()="test";
				lInfo+="raw";
			}

			if(*ptr.get()!="test")
				throw os::smart_ptr<std::exception>(new generalTestException("Error at raw deref"+lInfo,locString),shared_type);
			if(*ptr!="test")
				throw os::smart_ptr<std::exception>(new generalTestException("Error at operator deref"+lInfo,locString),shared_type);
			if(ptr[0]!="test")
				throw os::smart_ptr<std::exception>(new generalTestException("Error at array deref"+lInfo,locString),shared_type);

			if(ptr->substr(0,2)!="te")
				throw os::smart_ptr<std::exception>(new generalTestException("Error at -> operator"+lInfo,locString),shared_type);
		}
	}
	void derefTest_raw() throw(os::smart_ptr<std::exception>){derefTest(raw_type);}
	void derefTest_shared() throw(os::smart_ptr<std::exception>){derefTest(shared_type);}
	void derefTest_array() throw(os::smart_ptr<std::exception>){derefTest(shared_type_array);}
	void derefTest_dyndel() throw(os::smart_ptr<std::exception>){derefTest(shared_type_dynamic_delete);}

/*================================================================
	ADS Tests
================================================================*/

	#define GETBIT(d,p) ((d) & (1 << (p)))
	#define SETBIT(d,p,t) (t==0 ? d = (d)&~(1<<(p)):d = (d)|(1<<(p)))

	void singleInsertion(smart_ptr<ads<int> > dataStruct, string ads_type, int id) throw(os::smart_ptr<std::exception>)
	{
		smart_ptr<int> intptr = smart_ptr<int>(new int(5),shared_type);
		string locString = "DatastructuresTest.cpp, singleInsertion(...), "+ads_type;

		if(!dataStruct->insert(intptr))
			throw os::smart_ptr<std::exception>(new generalTestException("ADS Insertion failed",locString),shared_type);
		
		//Attempt to re-insert (two cases)
		if(GETBIT(id,0))
		{
			if(!dataStruct->insert(intptr))
				throw os::smart_ptr<std::exception>(new generalTestException("ADS re-insertion failed",locString),shared_type);
			if(!dataStruct->findDelete(intptr))
				throw os::smart_ptr<std::exception>(new generalTestException("ADS delete after re-insertion failed",locString),shared_type);
		}
		else
		{
			if(dataStruct->insert(intptr))
				throw os::smart_ptr<std::exception>(new generalTestException("ADS re-insertion succeeded, it should not have",locString),shared_type);
		}

		//Check, there should be one element in the ADS
		if(dataStruct->size()!=1)
			throw os::smart_ptr<std::exception>(new generalTestException("ADS should have 1 element, it has "+to_string(dataStruct->size()),locString),shared_type);

		//Find
		if(!dataStruct->find(intptr))
			throw os::smart_ptr<std::exception>(new generalTestException("Could not find inserted element",locString),shared_type);
		int comp = 5;
		if(!dataStruct->find(&comp))
			throw os::smart_ptr<std::exception>(new generalTestException("Could not find alias to inserted element",locString),shared_type);

		//Shouldn't be able to find "bad" elements
		comp = 7;
		if(dataStruct->find(&comp))
			throw os::smart_ptr<std::exception>(new generalTestException("Found item that was not inserted",locString),shared_type);
	}
	void singleTestADSDeletion(smart_ptr<ads<int> > dataStruct, string ads_type, int id) throw(os::smart_ptr<std::exception>)
	{
		smart_ptr<int> intptr = smart_ptr<int>(new int(5),shared_type);
		string locString = "DatastructuresTest.cpp, singleTestADSDeletion(...), "+ads_type;

		if(intptr.getRefCount()==NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("NULL reference count",locString),shared_type);
		if(*intptr.getRefCount()!=1)
			throw os::smart_ptr<std::exception>(new generalTestException("Expected reference count of 1, but found "+to_string(*intptr.getRefCount()),locString),shared_type);
		if(!dataStruct->insert(intptr))
			throw os::smart_ptr<std::exception>(new generalTestException("ADS Insertion failed",locString),shared_type);
		if(*intptr.getRefCount()!=2)
			throw os::smart_ptr<std::exception>(new generalTestException("Expected reference count of 2, but found "+to_string(*intptr.getRefCount()),locString),shared_type);
	}
	void singleTestDeletion(smart_ptr<ads<int> > dataStruct, string ads_type, int id) throw(os::smart_ptr<std::exception>)
	{
		smart_ptr<int> intptr = smart_ptr<int>(new int(5),shared_type);
		string locString = "DatastructuresTest.cpp, singleTestDeletion(...), "+ads_type;

		if(intptr.getRefCount()==NULL)
			throw os::smart_ptr<std::exception>(new generalTestException("NULL reference count",locString),shared_type);
		if(*intptr.getRefCount()!=1)
			throw os::smart_ptr<std::exception>(new generalTestException("Expected reference count of 1, but found "+to_string(*intptr.getRefCount()),locString),shared_type);
		if(!dataStruct->insert(intptr))
			throw os::smart_ptr<std::exception>(new generalTestException("ADS Insertion failed",locString),shared_type);
		if(*intptr.getRefCount()!=2)
			throw os::smart_ptr<std::exception>(new generalTestException("Expected reference count of 2, but found "+to_string(*intptr.getRefCount()),locString),shared_type);
		
		//Find delete
		if(!dataStruct->findDelete(intptr))
			throw os::smart_ptr<std::exception>(new generalTestException("Could not find element to delete",locString),shared_type);

		if(*intptr.getRefCount()!=1)
			throw os::smart_ptr<std::exception>(new generalTestException("Expected reference count of 1, but found "+to_string(*intptr.getRefCount())+" after ADS deletion",locString),shared_type);
        dataStruct = NULL;
	}
	void checkSorted(smart_ptr<ads<int> > dataStruct, string ads_type) throw(os::smart_ptr<std::exception>)
	{
		string locString = "DatastructuresTest.cpp, checkSorted(...), "+ads_type;

		auto last = dataStruct->getFirst();
		for(auto it = dataStruct->getFirst();it;it=it->getNext())
		{
            
            
			if(*(it->getData())<*(last->getData()))
				throw smart_ptr<std::exception>(new generalTestException("ADS is out of order",locString),shared_type);
			last = it;
		}
	}
    void randomInsertionTest(smart_ptr<ads<int> > dataStruct, string ads_type, int id) throw(os::smart_ptr<std::exception>)
    {
        string locString = "DatastructuresTest.cpp, randomInsertionTest(...), "+ads_type;
        srand(time(NULL));

        //Insert 100 elements
        for(int i = 0; i<100;i++)
        {
            //Create insertion pointer
            smart_ptr<int> intptr = smart_ptr<int>(new int(rand()%1000),shared_type);
            if(intptr.getRefCount()==NULL)
                throw os::smart_ptr<std::exception>(new generalTestException("NULL reference count",locString),shared_type);
            if(*intptr.getRefCount()!=1)
                throw os::smart_ptr<std::exception>(new generalTestException("Expected reference count of 1, but found "+to_string(*intptr.getRefCount()),locString),shared_type);
            
            //Attempt to insert
            if(!dataStruct->find(intptr))
            {
                if(!dataStruct->insert(intptr))
                    throw os::smart_ptr<std::exception>(new generalTestException("ADS Insertion failed",locString),shared_type);
                if(!dataStruct->find(intptr))
                    throw os::smart_ptr<std::exception>(new generalTestException("Could not find inserted node",locString),shared_type);
                
                if(id&2) checkSorted(dataStruct,ads_type);
            }
            else
                i--;
        }
    }
    void randomInsertionDeletionTest(smart_ptr<ads<int> > dataStruct, string ads_type, int id) throw(os::smart_ptr<std::exception>)
    {
        string locString = "DatastructuresTest.cpp, randomInsertionDeletionTest(...), "+ads_type;
        srand(time(NULL));
        
        //Insert 100 elements
        for(int i = 0; i<100;i++)
        {
            //Create insertion pointer
            smart_ptr<int> intptr = smart_ptr<int>(new int(rand()%1000),shared_type);
            if(intptr.getRefCount()==NULL)
            throw os::smart_ptr<std::exception>(new generalTestException("NULL reference count",locString),shared_type);
            if(*intptr.getRefCount()!=1)
            throw os::smart_ptr<std::exception>(new generalTestException("Expected reference count of 1, but found "+to_string(*intptr.getRefCount()),locString),shared_type);
            
            //Attempt to insert
            if(!dataStruct->find(intptr))
            {
                if(!dataStruct->insert(intptr))
                throw os::smart_ptr<std::exception>(new generalTestException("ADS Insertion failed",locString),shared_type);
                if(!dataStruct->find(intptr))
                throw os::smart_ptr<std::exception>(new generalTestException("Could not find inserted node",locString),shared_type);
                
                if(id&2) checkSorted(dataStruct,ads_type);
                
                //Every so often, delete what we just inserted
                if(rand()%4)
                {
                    if(!dataStruct->findDelete(intptr))
                    throw os::smart_ptr<std::exception>(new generalTestException("ADS Deletion failed",locString),shared_type);
                    if(id&2) checkSorted(dataStruct,ads_type);
                }
            }
            else
                i--;
        }
    }
    void randomForwardTraverseTest(smart_ptr<ads<int> > dataStruct, string ads_type, int id) throw(os::smart_ptr<std::exception>)
    {
        string locString = "DatastructuresTest.cpp, randomForwardTraverseTest(...), "+ads_type;
        srand(time(NULL));
    
        //Insert 100 elements
        for(int i = 0; i<100;i++)
        {
            //Create insertion pointer
            smart_ptr<int> intptr = smart_ptr<int>(new int(rand()%1000),shared_type);
            if(intptr.getRefCount()==NULL)
            throw os::smart_ptr<std::exception>(new generalTestException("NULL reference count",locString),shared_type);
            if(*intptr.getRefCount()!=1)
            throw os::smart_ptr<std::exception>(new generalTestException("Expected reference count of 1, but found "+to_string(*intptr.getRefCount()),locString),shared_type);
        
            //Attempt to insert
            if(!dataStruct->find(intptr))
            {
                if(!dataStruct->insert(intptr))
                throw os::smart_ptr<std::exception>(new generalTestException("ADS Insertion failed",locString),shared_type);
                if(!dataStruct->find(intptr))
                throw os::smart_ptr<std::exception>(new generalTestException("Could not find inserted node",locString),shared_type);
            
                if(id&2) checkSorted(dataStruct,ads_type);
            }
            else
            i--;
        }
        
        //Iterate through
        int trace = 0;
        for(auto it = dataStruct->getFirst();it;it=it->getNext())
        {
            trace++;
            if(!it->getData())
            throw os::smart_ptr<std::exception>(new generalTestException("Could not find node "+to_string(trace),locString),shared_type);
        }
        if(trace!=dataStruct->size())
        throw os::smart_ptr<std::exception>(new generalTestException("Traverse failed, expected "+std::to_string(dataStruct->size())+" but found "+std::to_string(trace),locString),shared_type);
    }
    void randomReverseTraverseTest(smart_ptr<ads<int> > dataStruct, string ads_type, int id) throw(os::smart_ptr<std::exception>)
    {
        string locString = "DatastructuresTest.cpp, randomReverseTraverseTest(...), "+ads_type;
        srand(time(NULL));
    
        //Insert 100 elements
        for(int i = 0; i<100;i++)
        {
            //Create insertion pointer
            smart_ptr<int> intptr = smart_ptr<int>(new int(rand()%1000),shared_type);
            if(intptr.getRefCount()==NULL)
            throw os::smart_ptr<std::exception>(new generalTestException("NULL reference count",locString),shared_type);
            if(*intptr.getRefCount()!=1)
            throw os::smart_ptr<std::exception>(new generalTestException("Expected reference count of 1, but found "+to_string(*intptr.getRefCount()),locString),shared_type);
        
            //Attempt to insert
            if(!dataStruct->find(intptr))
            {
                if(!dataStruct->insert(intptr))
                throw os::smart_ptr<std::exception>(new generalTestException("ADS Insertion failed",locString),shared_type);
                if(!dataStruct->find(intptr))
                throw os::smart_ptr<std::exception>(new generalTestException("Could not find inserted node",locString),shared_type);
            
                if(id&2) checkSorted(dataStruct,ads_type);
            }
            else
            i--;
        }
    
        //Iterate through
        int trace = 0;
        for(auto it = dataStruct->getLast();it;it=it->getPrev())
        {
            trace++;
            if(!it->getData())
            throw os::smart_ptr<std::exception>(new generalTestException("Could not find node "+to_string(trace),locString),shared_type);
        }
        if(trace!=dataStruct->size())
        throw os::smart_ptr<std::exception>(new generalTestException("Traverse failed, expected "+std::to_string(dataStruct->size())+" but found "+std::to_string(trace),locString),shared_type);
}

	//adsSuite test
	typedef void (*adsTestFunc)(smart_ptr<ads<int> > dataStruct, string ads_type, int id);
	template <class adsType, class nodeType>
	class adsTest:public singleTest
	{
	private:
		string ads_name;
		adsTestFunc adfunc;
		int _id;
        
    protected:
        virtual smart_ptr<ads<int> > newADS(){return smart_ptr<ads<int> >(new adsType(),shared_type);}
        void setID(int id){_id=id;};
	public:
		adsTest(std::string tn,std::string ads_n,adsTestFunc func, int id):
			singleTest(tn)
		{
			ads_name = ads_n;
			adfunc = func;
            _id = id;
		}
        virtual ~adsTest(){}
        
		//Run the specified test function
		void test() throw(os::smart_ptr<std::exception>)
		{
			if(adfunc!=NULL)
                adfunc(newADS(),ads_name,_id);
			else
				throw os::smart_ptr<std::exception>(new nullFunctionException("DatastructuresTest.cpp, adsTest::test()"),shared_type);
		}
	};
	//adsSuite
	template <class adsType, class nodeType>
	class adsSuite:public testSuite
	{
	public:
		adsSuite(string adst, int id):
			testSuite(adst)
		{
            //Bind the tests
			pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("Insertion Test",adst,&singleTestDeletion,id),shared_type));
			pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("Deletion Test",adst,&singleTestDeletion,id),shared_type));
			pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("ADS Deletion Test",adst,&singleTestADSDeletion,id),shared_type));
            pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("Random Insertion Test",adst,&randomInsertionTest,id),shared_type));
            pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("Random Insertion/Deletion Test",adst,&randomInsertionDeletionTest,id),shared_type));
            pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("Forward Traverse Test",adst,&randomForwardTraverseTest,id),shared_type));
            pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("Reverse Traverse Test",adst,&randomReverseTraverseTest,id),shared_type));
		}
        virtual ~adsSuite(){}
	};
    //Set Test
    class setTest: public adsTest<smartSet<int>,adnode<int> >
    {
        setTypes set_type;
    protected:
        virtual smart_ptr<ads<int> > newADS(){return smart_ptr<ads<int> >(new smartSet<int>(set_type),shared_type);}
    public:
        setTest(string testName,setTypes st, adsTestFunc func):
            adsTest(testName,"Smart Set",func, 0)
        {
            set_type = st;
            int temp_id = 0;
            if(st==sorted_set) temp_id = temp_id | 2;
            
            setID(temp_id);
        }
        virtual ~setTest(){}
    };
    //Set suite
    class setSuite: public testSuite
    {
    public:
        setSuite():
            testSuite("Smart Set")
        {
            for(int i = 0;i<=sorted_set;i++)
            {
                string addition=": ";
                if(i==small_set) addition+="Small Set";
                else if(i==sorted_set) addition+="Sorted Set";
                else addition+="Default Set";
                pushTest(smart_ptr<singleTest>(new setTest("Insertion Test"+addition,(setTypes)i,&singleTestDeletion),shared_type));
                pushTest(smart_ptr<singleTest>(new setTest("Deletion Test"+addition,(setTypes)i,&singleTestDeletion),shared_type));
                pushTest(smart_ptr<singleTest>(new setTest("ADS Deletetion Test"+addition,(setTypes)i,&singleTestADSDeletion),shared_type));
                pushTest(smart_ptr<singleTest>(new setTest("Random Insertion Test"+addition,(setTypes)i,&randomInsertionTest),shared_type));
                pushTest(smart_ptr<singleTest>(new setTest("Random Insertion/Deletion Test"+addition,(setTypes)i,&randomInsertionDeletionTest),shared_type));
                pushTest(smart_ptr<singleTest>(new setTest("Forward Traverse Test"+addition,(setTypes)i,&randomForwardTraverseTest),shared_type));
                pushTest(smart_ptr<singleTest>(new setTest("Reverse Traverse Test"+addition,(setTypes)i,&randomReverseTraverseTest),shared_type));
            }
        }
        virtual ~setSuite(){}
    };

/*================================================================
	MatrixTest
 ================================================================*/

    //Array access test
    void matrixArrayAccessTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixArrayAccessTest()";
        
        matrix<int>mat1(4,4);
        matrix<int>mat2(4,4);
        matrix<int>mat3(mat1);
        int compArray[16];
        
        //Check size
        if(mat1.getWidth()!=4 || mat2.getWidth()!=4 || mat3.getWidth()!=4) throw os::smart_ptr<std::exception>(new generalTestException("Matrix width failure",locString),shared_type);
        if(mat1.getHeight()!=4 || mat2.getHeight()!=4 || mat3.getHeight()!=4) throw os::smart_ptr<std::exception>(new generalTestException("Matrix height failure",locString),shared_type);
        
        //Random init
        srand(time(NULL));
        for(int x=0;x<4;x++)
        {
            for(int y=0;y<4;y++)
            {
                compArray[y*4+x] = rand()%100;
                mat1(x,y)=compArray[y*4+x];
                mat2(x,y)=compArray[y*4+x];
            }
        }
        mat3 = mat1;
        
        //Compare mat1 with comp array
        for(int i = 0;i<16;i++)
        {
            if(compArray[i] != mat1.getArray()[i])
                throw os::smart_ptr<std::exception>(new generalTestException("Matrix init failed",locString),shared_type);
        }
        
        //Compare mat1 and mat2 (raw array)
        for(int i = 0;i<16;i++)
        {
            if(mat1.getArray()[i] != mat2.getArray()[i])
            throw os::smart_ptr<std::exception>(new generalTestException("Matrix direct compare failed",locString),shared_type);
        }
        
        //Compare mat1 and mat3 (raw array)
        for(int i = 0;i<16;i++)
        {
            if(mat2.getArray()[i] != mat3.getArray()[i])
            throw os::smart_ptr<std::exception>(new generalTestException("Matrix copy compare failed",locString),shared_type);
        }
    }
    //Equality test
    void matrixEqualityTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixEqualityTest()";
        matrix<int>mat1(4,4);
        matrix<int>mat2(4,4);
        matrix<int>mat3(4,4);
        matrix<int>mat4(mat1);
        int compArray[16];
        
        //Random init
        srand(time(NULL));
        for(int x=0;x<4;x++)
        {
            for(int y=0;y<4;y++)
            {
                compArray[y*4+x] = rand()%100;
                mat1(x,y)=compArray[y*4+x];
                mat2(x,y)=compArray[y*4+x];
                mat3(x,y)=compArray[y*4+x]+1;
            }
        }
        mat4 = mat1;
        
        //Compare mat1 and 2
        if(!(mat1==mat2))
        throw os::smart_ptr<std::exception>(new generalTestException("Equals failed (same init)",locString),shared_type);
        if(mat1!=mat2)
        throw os::smart_ptr<std::exception>(new generalTestException("Not equals failed (same init)",locString),shared_type);
        
        //Compare mat2 and 4
        if(!(mat2==mat4))
        throw os::smart_ptr<std::exception>(new generalTestException("Equals failed (copy constructor)",locString),shared_type);
        if(mat2!=mat4)
        throw os::smart_ptr<std::exception>(new generalTestException("Not equals failed (copy constructor)",locString),shared_type);
        
        //Compare mat1 and 3
        if(mat1==mat3)
        throw os::smart_ptr<std::exception>(new generalTestException("Equals failed (different mats)",locString),shared_type);
        if(!(mat1!=mat3))
        throw os::smart_ptr<std::exception>(new generalTestException("Not equals failed (different mats)",locString),shared_type);
    }
    //Addition test
    void matrixAdditionTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdditionTest()";
        matrix<int> mat1(2,2);
        matrix<int> mat2(2,2);
        matrix<int> out(2,2);
        matrix<int> ans(2,2);
        
        //Init mat1 and mat2
        mat1(0,0)=1;    mat1(1,0)=2;
        mat1(0,1)=3;    mat1(1,1)=4;
        
        mat2(0,0)=5;    mat2(1,0)=6;
        mat2(0,1)=7;    mat2(1,1)=8;
        
        //Hard-coded answer
        ans(0,0)=6;    ans(1,0)=8;
        ans(0,1)=10;    ans(1,1)=12;
        
        out = mat1+mat2;
        if(out!=ans)
        throw os::smart_ptr<std::exception>(new generalTestException("Addition failed!",locString),shared_type);
        out = mat2+mat1;
        if(out!=ans)
        throw os::smart_ptr<std::exception>(new generalTestException("Addition transitivity failed!",locString),shared_type);
    }
    //Subtraction test
    void matrixSubtractionTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixSubtractionTest()";
        matrix<int> mat1(2,2);
        matrix<int> mat2(2,2);
        matrix<int> out(2,2);
        matrix<int> ans(2,2);
        
        //Init mat1 and mat2
        mat1(0,0)=1;    mat1(1,0)=2;
        mat1(0,1)=3;    mat1(1,1)=4;
        
        mat2(0,0)=5;    mat2(1,0)=6;
        mat2(0,1)=7;    mat2(1,1)=8;
        
        //Hard-coded answer
        ans(0,0)=4;    ans(1,0)=4;
        ans(0,1)=4;    ans(1,1)=4;
        
        out = mat2-mat1;
        if(out!=ans)
        throw os::smart_ptr<std::exception>(new generalTestException("Subtraction failed!",locString),shared_type);
        out = mat1-mat2;
        if(out==ans)
        throw os::smart_ptr<std::exception>(new generalTestException("Subtraction not respecting order!",locString),shared_type);
    }
    //Dot product test
    void matrixDotProductTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixDotProductTest()";
        matrix<int> mat1(2,2);
        matrix<int> mat2(2,2);
        matrix<int> out(2,2);
        matrix<int> ans(2,2);
        
        //Init mat1 and mat2
        mat1(0,0)=1;    mat1(1,0)=2;
        mat1(0,1)=3;    mat1(1,1)=4;
        
        mat2(0,0)=5;    mat2(1,0)=6;
        mat2(0,1)=7;    mat2(1,1)=8;
        
        //Hard-coded answer
        ans(0,0)=19;    ans(1,0)=22;
        ans(0,1)=43;    ans(1,1)=50;
        
        out = mat1*mat2;
        if(out!=ans)
        throw os::smart_ptr<std::exception>(new generalTestException("Dot Product failed!",locString),shared_type);
        out = mat2*mat1;
        if(out==ans)
        throw os::smart_ptr<std::exception>(new generalTestException("Dot Product not respecting order!",locString),shared_type);
    }
    //Advanced construction test
    void matrixAdvancedConstructionTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedConstructionTest()";
        
        //Preform this test 10 times
        srand(time(NULL));
        for(int i=0;i<10;i++)
        {
            matrix<int> mast1(10,10);
            matrix<int> cop1;
            matrix<int> bridge1;
            indirectMatrix<int> mast2(10,10);
            indirectMatrix<int> cop2;
            indirectMatrix<int> bridge2;
            int compsrc[100];
            
            for(int i=0;i<100;i++)
            {
                compsrc[i]=rand();
                mast1.getArray()[i]=compsrc[i];
                mast2.getArray()[i]=&(compsrc[i]);
            }
            cop1=mast1;
            cop2=mast2;
            bridge1=mast2;
            bridge2=mast1;
            
            //Compare everyone to comp
            for(int i=0;i<100;i++)
            {
                if(mast1.getArray()[i]!=compsrc[i])
                    throw os::smart_ptr<std::exception>(new generalTestException("Matrix init failed (direct matrix)",locString),shared_type);
                if(*(mast2.getArray()[i])!=compsrc[i])
                    throw os::smart_ptr<std::exception>(new generalTestException("Matrix init failed (indirect matrix)",locString),shared_type);
                
                if(cop1.getArray()[i]!=compsrc[i])
                    throw os::smart_ptr<std::exception>(new generalTestException("Matrix standard equals failed (direct matrix)",locString),shared_type);
                if(*(cop2.getArray()[i])!=compsrc[i])
                    throw os::smart_ptr<std::exception>(new generalTestException("Matrix standard equals failed (indirect matrix)",locString),shared_type);
                
                if(bridge1.getArray()[i]!=compsrc[i])
                    throw os::smart_ptr<std::exception>(new generalTestException("Matrix bridge equals failed (direct matrix)",locString),shared_type);
                if(*(bridge2.getArray()[i])!=compsrc[i])
                    throw os::smart_ptr<std::exception>(new generalTestException("Matrix bridge equals failed (indirect matrix)",locString),shared_type);
            }
        }
    }
    //Advanced equality test
    void matrixAdvancedEqualityTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedEqualityTest()";
        
        //Preform this test 10 times
        srand(time(NULL));
        for(int i=0;i<10;i++)
        {
            matrix<int> mast1(10,10);
            matrix<int> wrong1(10,10);
            matrix<int> cop1;
            indirectMatrix<int> mast2(10,10);
            indirectMatrix<int> wrong2(10,10);
            indirectMatrix<int> cop2;
            int compsrc[100];
            
            for(int i=0;i<100;i++)
            {
                compsrc[i]=rand();
                mast1.getArray()[i]=compsrc[i];
                mast2.getArray()[i]=&(compsrc[i]);
                wrong1.getArray()[i]=compsrc[i]+1;
                wrong2.getArray()[i]=os::smart_ptr<int>(new int(compsrc[i]+1),os::shared_type);
            }
            cop1=mast1;
            cop2=mast2;
            
            //Standard to standard
            if(!(mast1==cop1)) throw os::smart_ptr<std::exception>(new generalTestException("S-S equals failed",locString),shared_type);
            if(!(cop1==mast1)) throw os::smart_ptr<std::exception>(new generalTestException("Transitive S-S equals failed",locString),shared_type);
            if(mast1!=cop1) throw os::smart_ptr<std::exception>(new generalTestException("S-S not equals failed",locString),shared_type);
            if(cop1!=mast1) throw os::smart_ptr<std::exception>(new generalTestException("Transitive S-S not equals failed",locString),shared_type);
            
            //Indirect to indirect
            if(!(mast2==cop2)) throw os::smart_ptr<std::exception>(new generalTestException("I-I equals failed",locString),shared_type);
            if(!(cop2==mast2)) throw os::smart_ptr<std::exception>(new generalTestException("Transitive I-I equals failed",locString),shared_type);
            if(mast2!=cop2) throw os::smart_ptr<std::exception>(new generalTestException("I-I not equals failed",locString),shared_type);
            if(cop2!=mast2) throw os::smart_ptr<std::exception>(new generalTestException("Transitive I-I not equals failed",locString),shared_type);
            
            //Standard to indirect
            if(!(mast1==cop2)) throw os::smart_ptr<std::exception>(new generalTestException("S-I equals failed",locString),shared_type);
            if(!(cop1==mast2)) throw os::smart_ptr<std::exception>(new generalTestException("Transitive S-I equals failed",locString),shared_type);
            if(mast1!=cop2) throw os::smart_ptr<std::exception>(new generalTestException("S-I not equals failed",locString),shared_type);
            if(cop1!=mast2) throw os::smart_ptr<std::exception>(new generalTestException("Transitive S-I not equals failed",locString),shared_type);
            
            //Indirect to standard
            if(!(mast2==cop1)) throw os::smart_ptr<std::exception>(new generalTestException("I-S equals failed",locString),shared_type);
            if(!(cop2==mast1)) throw os::smart_ptr<std::exception>(new generalTestException("Transitive I-S equals failed",locString),shared_type);
            if(mast2!=cop1) throw os::smart_ptr<std::exception>(new generalTestException("I-S not equals failed",locString),shared_type);
            if(cop2!=mast1) throw os::smart_ptr<std::exception>(new generalTestException("Transitive I-S not equals failed",locString),shared_type);
        }
    }
    //Advanced addition test
    void matrixAdvancedAdditionTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedAdditionTest()";
        
        //Preform this test 10 times
        srand(time(NULL));
        for(int i=0;i<10;i++)
        {
            matrix<int> smat1(10,10);
            matrix<int> smat2(10,10);
            for(int x=0;x<10;x++)
            {
                for(int y=0;y<10;y++)
                {
                    smat1(x,y)=rand()%100;
                    smat2(x,y)=rand()%100;
                }
            }
            indirectMatrix<int> imat1(smat1);
            indirectMatrix<int> imat2(smat2);
            
            //Compares
            if(imat1+imat2 != smat1+smat2) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: i1+i2 != s1+s2",locString),shared_type);
            if(imat2+imat1 != smat2+smat1) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: i2+i1 != s2+s1",locString),shared_type);
            if(imat1+smat2 != smat1+smat2) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: i1+s2 != s1+s2",locString),shared_type);
            if(imat2+smat1 != smat2+smat1) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: i2+s1 != s2+s1",locString),shared_type);
            if(smat1+imat2 != smat1+smat2) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: s1+i2 != s1+s2",locString),shared_type);
            if(smat2+imat1 != smat2+smat1) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: s2+i1 != s2+s1",locString),shared_type);
            
            //Transitive tests
            if(imat1+imat2 != smat2+smat1) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: i1+i2 != s2+s1",locString),shared_type);
            if(imat2+imat1 != smat1+smat2) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: i2+i1 != s1+s2",locString),shared_type);
            if(imat1+smat2 != smat2+smat1) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: i1+s2 != s2+s1",locString),shared_type);
            if(imat2+smat1 != smat1+smat2) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: i2+s1 != s1+s2",locString),shared_type);
            if(smat1+imat2 != smat2+smat1) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: s1+i2 != s2+s1",locString),shared_type);
            if(smat2+imat1 != smat1+smat2) throw os::smart_ptr<std::exception>(new generalTestException("Addition failed: s2+i1 != s1+s2",locString),shared_type);
        }
    }
    //Advanced subtraction test
    void matrixAdvancedSubtractionTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedSubtractionTest()";
        
        //Preform this test 10 times
        srand(time(NULL));
        for(int i=0;i<10;i++)
        {
            matrix<int> smat1(10,10);
            matrix<int> smat2(10,10);
            for(int x=0;x<10;x++)
            {
                for(int y=0;y<10;y++)
                {
                    smat1(x,y)=rand()%100;
                    smat2(x,y)=rand()%100;
                }
            }
            indirectMatrix<int> imat1(smat1);
            indirectMatrix<int> imat2(smat2);
            
            //Compares
            if(imat1-imat2 != smat1-smat2) throw os::smart_ptr<std::exception>(new generalTestException("Subtraction failed: i1-i2 != s1-s2",locString),shared_type);
            if(imat2-imat1 != smat2-smat1) throw os::smart_ptr<std::exception>(new generalTestException("Subtraction failed: i2-i1 != s2-s1",locString),shared_type);
            if(imat1-smat2 != smat1-smat2) throw os::smart_ptr<std::exception>(new generalTestException("Subtraction failed: i1-s2 != s1-s2",locString),shared_type);
            if(imat2-smat1 != smat2-smat1) throw os::smart_ptr<std::exception>(new generalTestException("Subtraction failed: i2-s1 != s2-s1",locString),shared_type);
            if(smat1-imat2 != smat1-smat2) throw os::smart_ptr<std::exception>(new generalTestException("Subtraction failed: s1-i2 != s1-s2",locString),shared_type);
            if(smat2-imat1 != smat2-smat1) throw os::smart_ptr<std::exception>(new generalTestException("Subtraction failed: s2-i1 != s2-s1",locString),shared_type);
        }
    }
    //Advanced dot product test
    void matrixAdvancedDotProductTest()throw(os::smart_ptr<std::exception>)
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedDotProductTest()";
        
        //Preform this test 10 times
        srand(time(NULL));
        for(int i=0;i<10;i++)
        {
            matrix<int> smat1(10,10);
            matrix<int> smat2(10,10);
            for(int x=0;x<10;x++)
            {
                for(int y=0;y<10;y++)
                {
                    smat1(x,y)=rand()%100;
                    smat2(x,y)=rand()%100;
                }
            }
            indirectMatrix<int> imat1(smat1);
            indirectMatrix<int> imat2(smat2);
            
            //Compares
            if(imat1*imat2 != smat1*smat2) throw os::smart_ptr<std::exception>(new generalTestException("Dot Product failed: i1*i2 != s1*s2",locString),shared_type);
            if(imat2*imat1 != smat2*smat1) throw os::smart_ptr<std::exception>(new generalTestException("Dot Product failed: i2*i1 != s2*s1",locString),shared_type);
            if(imat1*smat2 != smat1*smat2) throw os::smart_ptr<std::exception>(new generalTestException("Dot Product failed: i1*s2 != s1*s2",locString),shared_type);
            if(imat2*smat1 != smat2*smat1) throw os::smart_ptr<std::exception>(new generalTestException("Dot Product failed: i2*s1 != s2*s1",locString),shared_type);
            if(smat1*imat2 != smat1*smat2) throw os::smart_ptr<std::exception>(new generalTestException("Dot Product failed: s1*i2 != s1*s2",locString),shared_type);
            if(smat2*imat1 != smat2*smat1) throw os::smart_ptr<std::exception>(new generalTestException("Dot Product failed: s2*i1 != s2*s1",locString),shared_type);
        }
    }

/*================================================================
	Vector Tests
 ================================================================*/

	//Tests the copy constructor and equality constructor
	void vector2dConstructorTest()throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector2dConstructorTest()";
		vector2d_d v1;
		
		//Test default init values
		if(v1.x!=0 || v1.y!=0)
			throw os::smart_ptr<std::exception>(new generalTestException("Vector default init failed",locString),shared_type);

		//Tests the value init
		vector2d_d v2(.5,1.5);
		if(v2.x!=.5 || v2.y!=1.5)
			throw os::smart_ptr<std::exception>(new generalTestException("Vector init failed",locString),shared_type);

		//Tests the copy constructor
		vector2d_d v3(v2);
		if(v3.x!=.5 || v3.y!=1.5)
			throw os::smart_ptr<std::exception>(new generalTestException("Vector copy init failed",locString),shared_type);
		v1=v3;
		if(v1.x!=.5 || v1.y!=1.5)
			throw os::smart_ptr<std::exception>(new generalTestException("Vector copy init failed",locString),shared_type);
	}
	void vector3dConstructorTest()throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector3dConstructorTest()";
		vector3d_d v1;
		
		//Test default init values
		if(v1.x!=0 || v1.y!=0 || v1.z!=0)
			throw os::smart_ptr<std::exception>(new generalTestException("Vector default init failed",locString),shared_type);

		//Tests the value init
		vector3d_d v2(.5,1.5,2.5);
		if(v2.x!=.5 || v2.y!=1.5 || v2.z!=2.5)
			throw os::smart_ptr<std::exception>(new generalTestException("Vector init failed",locString),shared_type);

		//Tests the copy constructor
		vector3d_d v3(v2);
		if(v3.x!=.5 || v3.y!=1.5 || v3.z!=2.5)
			throw os::smart_ptr<std::exception>(new generalTestException("Vector copy init failed",locString),shared_type);
		v1=v3;
		if(v1.x!=.5 || v1.y!=1.5 || v1.z!=2.5)
			throw os::smart_ptr<std::exception>(new generalTestException("Vector equals init failed",locString),shared_type);

		//Tests the 2d constructor
		vector2d_d t(1,2);
		vector3d_d v4(t);
		if(v4.x!=1 || v4.y!=2 || v4.z !=0)
			throw os::smart_ptr<std::exception>(new generalTestException("Vector 2d init failed",locString),shared_type);
	}
	//Tests equality functions
	void vector2dEqualityTest() throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector2dEqualityTest()";

		for(int i=0;i<30;i++)
		{
			vector2d_16 v1(rand(),rand());
			vector2d_16 v2(rand(),rand());
			if(i==0)
			{
				v1=vector2d_16();
				v2=vector2d_16();
			}
			
			//Find type
			int v=-1;
			if(v1.x>v2.x) v=1;
			else if(v1.x==v2.x && v1.y>v2.y) v=1;
			else if(v1.x==v2.x && v1.y==v2.y) v=0;

			if(v!=v1.compare(v2))
				throw os::smart_ptr<std::exception>(new generalTestException("Compare failed.  Cycle: "+to_string(i),locString),shared_type);
			
			//Test all cases
			if(v!=0 && v1==v2) throw os::smart_ptr<std::exception>(new generalTestException("< failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v==0 && v1!=v2) throw os::smart_ptr<std::exception>(new generalTestException("<= failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v!=-1 && v1<v2) throw os::smart_ptr<std::exception>(new generalTestException("< failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v==1 && v1<=v2) throw os::smart_ptr<std::exception>(new generalTestException("<= failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v!=1 && v1>v2) throw os::smart_ptr<std::exception>(new generalTestException("> failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v==-1 && v1>=v2) throw os::smart_ptr<std::exception>(new generalTestException(">= failed.  Cycle: "+to_string(i),locString),shared_type);
		}
	}
	void vector3dEqualityTest() throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector3dEqualityTest()";

		for(int i=0;i<30;i++)
		{
			vector3d_16 v1(rand(),rand(),rand());
			vector3d_16 v2(rand(),rand(),rand());
			if(i==0)
			{
				v1=vector3d_16();
				v2=vector3d_16();
			}
			
			//Find type
			int v=-1;
			if(v1.x>v2.x) v=1;
			else if(v1.x==v2.x && v1.y>v2.y) v=1;
			else if(v1.x==v2.x && v1.y==v2.y) v=0;

			if(v!=v1.compare(v2))
				throw os::smart_ptr<std::exception>(new generalTestException("Compare failed.  Cycle: "+to_string(i),locString),shared_type);
			
			//Test all cases
			if(v!=0 && v1==v2) throw os::smart_ptr<std::exception>(new generalTestException("< failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v==0 && v1!=v2) throw os::smart_ptr<std::exception>(new generalTestException("<= failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v!=-1 && v1<v2) throw os::smart_ptr<std::exception>(new generalTestException("< failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v==1 && v1<=v2) throw os::smart_ptr<std::exception>(new generalTestException("<= failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v!=1 && v1>v2) throw os::smart_ptr<std::exception>(new generalTestException("> failed.  Cycle: "+to_string(i),locString),shared_type);
			if(v==-1 && v1>=v2) throw os::smart_ptr<std::exception>(new generalTestException(">= failed.  Cycle: "+to_string(i),locString),shared_type);
		}
	}
	//Addition
	void vector2dAdditionTest() throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector2dAdditionTest()";

		//Simple addition
		vector2d_d v1(3,9);
		vector2d_d v2(7,2);
		vector2d_d ans(10,11);

		if(v1.add(v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple addition failed",locString),shared_type);
		if(v1+v2!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple + failed",locString),shared_type);
		if(v2+v1!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("+ reverse failed",locString),shared_type);
		if((v1+=v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple += failed",locString),shared_type);
		if(v1!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("+= after failed",locString),shared_type);

		//Increment and decrement
		vector2d_d raw(0,1);
		raw++;
		if(raw.x!=0 && raw.y!=2)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple increment failed",locString),shared_type);
		++raw;
		if(raw.x!=0 && raw.y!=3)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple increment (2) failed",locString),shared_type);
		
		raw=vector2d_d(3,4);
		if(raw.length()!=5)
			throw os::smart_ptr<std::exception>(new generalTestException("Length failed",locString),shared_type);
		raw++;
		if(raw.length()!=6)
			throw os::smart_ptr<std::exception>(new generalTestException("Complex increment failed",locString),shared_type);
		raw++;
		if(raw.length()!=7)
			throw os::smart_ptr<std::exception>(new generalTestException("Complex increment (2) failed",locString),shared_type);
	}
	void vector3dAdditionTest() throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector3dAdditionTest()";

		//Simple addition
		vector3d_d v1(3,9,4);
		vector3d_d v2(7,2,1);
		vector3d_d ans(10,11,5);

		if(v1.add(v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple addition failed",locString),shared_type);
		if(v1+v2!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple + failed",locString),shared_type);
		if(v2+v1!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("+ reverse failed",locString),shared_type);
		if((v1+=v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple += failed",locString),shared_type);
		if(v1!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("+= after failed",locString),shared_type);

		//Increment and decrement
		vector3d_d raw(0,1,0);
		raw++;
		if(raw.x!=0 || raw.y!=2 || raw.z!=0)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple increment failed",locString),shared_type);
		++raw;
		if(raw.x!=0 || raw.y!=3 || raw.z!=0)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple increment (2) failed",locString),shared_type);
		
		raw=vector3d_d(1,1,1);
		if(raw.length()!=sqrt(3))
			throw os::smart_ptr<std::exception>(new generalTestException("Length failed",locString),shared_type);
		raw++;

		if(raw.length() < sqrt(3)+.9 || raw.length() > sqrt(3)+1.1)
			throw os::smart_ptr<std::exception>(new generalTestException("Complex increment failed",locString),shared_type);
		raw++;
		if(raw.length() < sqrt(3)+1.9 || raw.length() > sqrt(3)+2.1)
			throw os::smart_ptr<std::exception>(new generalTestException("Complex increment (2) failed",locString),shared_type);
	}
	//Subtraction
	void vector2dSubtractionTest() throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector2dSubtractionTest()";

		//Simple addition
		vector2d_d v1(3,9);
		vector2d_d v2(7,2);
		vector2d_d ans(-4,7);

		if(v1.subtract(v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple subtract failed",locString),shared_type);
		if(v1-v2!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple - failed",locString),shared_type);
		if((v2-v1) != (-ans))
			throw os::smart_ptr<std::exception>(new generalTestException("- reverse failed",locString),shared_type);
		if((v1-=v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple -= failed",locString),shared_type);
		if(v1!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("-= after failed",locString),shared_type);

		//Increment and decrement
		vector2d_d raw(0,5);
		raw--;
		if(raw.x!=0 && raw.y!=4)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple decrement failed",locString),shared_type);
		--raw;
		if(raw.x!=0 && raw.y!=3)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple decrement (2) failed",locString),shared_type);
		
		raw=vector2d_d(3,4);
		if(raw.length()!=5)
			throw os::smart_ptr<std::exception>(new generalTestException("Length failed",locString),shared_type);
		raw--;
		if(raw.length()!=4)
			throw os::smart_ptr<std::exception>(new generalTestException("Complex decrement failed",locString),shared_type);
		raw--;
		if(raw.length()!=3)
			throw os::smart_ptr<std::exception>(new generalTestException("Complex decrement (2) failed",locString),shared_type);
	}
	void vector3dSubtractionTest() throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector3dSubtractionTest()";

		//Simple addition
		vector3d_d v1(3,9,4);
		vector3d_d v2(7,2,1);
		vector3d_d ans(-4,7,3);

		if(v1.subtract(v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple subtraction failed",locString),shared_type);
		if(v1-v2!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple - failed",locString),shared_type);
		if((v2-v1)!=(-ans))
			throw os::smart_ptr<std::exception>(new generalTestException("- reverse failed",locString),shared_type);
		if((v1-=v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple -= failed",locString),shared_type);
		if(v1!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("-= after failed",locString),shared_type);

		//Increment and decrement
		vector3d_d raw(0,5,0);
		raw--;
		if(raw.x!=0 || raw.y!=4 || raw.z!=0)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple increment failed",locString),shared_type);
		--raw;
		if(raw.x!=0 || raw.y!=3 || raw.z!=0)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple increment (2) failed",locString),shared_type);
		
		raw=vector3d_d(4,4,4);
		if(raw.length()!=sqrt(3*16))
			throw os::smart_ptr<std::exception>(new generalTestException("Length failed",locString),shared_type);
		raw--;

		if(raw.length() > sqrt(3*16)-.9 || raw.length() < sqrt(3*16)-1.1)
			throw os::smart_ptr<std::exception>(new generalTestException("Complex decrement failed",locString),shared_type);
		raw--;
		if(raw.length() > sqrt(3*16)-1.9 || raw.length() < sqrt(3*16)-2.1)
			throw os::smart_ptr<std::exception>(new generalTestException("Complex decrement (2) failed",locString),shared_type);
	}
	//Dot product
	void vector2dDotProductTest() throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector2dDotProductTest()";
		vector2d_d v1(4,8);
		vector2d_d v2(-3,10);

		if(v1.dotProduct(v2)!=68)
			throw os::smart_ptr<std::exception>(new generalTestException("Initial dot-product failed!",locString),shared_type);
		v1(0,1);
		v2(1,0);
		if(v1.dotProduct(v2)!=0)
			throw os::smart_ptr<std::exception>(new generalTestException("Dot-product zero failed!",locString),shared_type);
	}
	void vector3dDotProductTest() throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector3dDotProductTest()";
		vector3d_d v1(4,8,3);
		vector3d_d v2(-3,10,-4);

		if(v1.dotProduct(v2)!=56)
			throw os::smart_ptr<std::exception>(new generalTestException("Initial dot-product failed!",locString),shared_type);
		v1(0,1,0);
		v2(0,0,1);
		if(v1.dotProduct(v2)!=0)
			throw os::smart_ptr<std::exception>(new generalTestException("Dot-product zero failed!",locString),shared_type);
	}
	//Cross product
	void vector3dCrossProductTest() throw(os::smart_ptr<std::exception>)
	{
		std::string locString = "DatastructuresTest.cpp, vector3dCrossProductTest()";
		vector3d_d v1(-1,7,4);
		vector3d_d v2(-5,8,4);
		vector3d_d ans(-4,-16,27);

		if(v1.crossProduct(v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple cross-product failed",locString),shared_type);
		if(v1*v2!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple * failed",locString),shared_type);
		if((v2*v1)!=(-ans))
			throw os::smart_ptr<std::exception>(new generalTestException("* reverse failed",locString),shared_type);
		if((v1*=v2)!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("Simple *= failed",locString),shared_type);
		if(v1!=ans)
			throw os::smart_ptr<std::exception>(new generalTestException("*= after failed",locString),shared_type);

	}

/*================================================================
	DatastructuresLibraryTest
================================================================*/

	//Constructor
	DatastructuresLibraryTest::DatastructuresLibraryTest():
		libraryTests("Datastructures")
	{
		//smart_ptr Test Suite
		os::smart_ptr<testSuite> trc = smart_ptr<testSuite>(new testSuite("smart_ptr"),shared_type);
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
			trc->pushTest("Comparison: NULL",&comparisonTest_null);
			trc->pushTest("Comparison: Raw",&comparisonTest_raw);
			trc->pushTest("Comparison: Shared",&comparisonTest_shared);
			trc->pushTest("Comparison: Array",&comparisonTest_array);
			trc->pushTest("Comparison: Dynamic Delete",&comparisonTest_dyndel);
			trc->pushTest("Dereference: Raw",&derefTest_raw);
			trc->pushTest("Dereference: Shared",&derefTest_shared);
			trc->pushTest("Dereference: Array",&derefTest_array);
			trc->pushTest("Dereference: Dynamic Delete",&derefTest_dyndel);
		pushSuite(trc);

		//ADS Test Suite
			//Unique element, unsorted
		pushSuite(smart_ptr<testSuite>(new adsSuite<unsortedList<int>,unsortedListNode<int> >("list",0),shared_type));
			//Unique element, sorted
		pushSuite(smart_ptr<testSuite>(new adsSuite<AVLTree<int>,AVLNode<int> >("AVL Tree",2),shared_type));
        pushSuite(smart_ptr<testSuite>(new adsSuite<asyncAVLTree<int>,asyncAVLNode<int> >("Async AVL Tree",2),shared_type));
			//Unique element, unsorted, set
		pushSuite(smart_ptr<testSuite>(new setSuite(),shared_type));
        
        //Matrix Test Suite
        trc = smart_ptr<testSuite>(new testSuite("matrix"),shared_type);
            trc->pushTest("Array Access",&matrixArrayAccessTest);
            trc->pushTest("Equality",&matrixEqualityTest);
            trc->pushTest("Addition",&matrixAdditionTest);
            trc->pushTest("Subtraction",&matrixSubtractionTest);
            trc->pushTest("Dot Product",&matrixDotProductTest);
            trc->pushTest("Advanced Construction",&matrixAdvancedConstructionTest);
            trc->pushTest("Advanced Equality",&matrixAdvancedEqualityTest);
            trc->pushTest("Advanced Addition",&matrixAdvancedAdditionTest);
            trc->pushTest("Advanced Subtraction",&matrixAdvancedSubtractionTest);
            trc->pushTest("Advanced Dot Product",&matrixAdvancedDotProductTest);
        pushSuite(trc);

		//2-d vector tests
		trc = smart_ptr<testSuite>(new testSuite("2-d Vector"),shared_type);
			trc->pushTest("Constructor",&vector2dConstructorTest);
			trc->pushTest("Comparison",&vector2dEqualityTest);
			trc->pushTest("Addition",&vector2dAdditionTest);
			trc->pushTest("Subtraction",&vector2dSubtractionTest);
			trc->pushTest("Dot-Product",&vector2dDotProductTest);
		pushSuite(trc);

		//3-d vector tests
		trc = smart_ptr<testSuite>(new testSuite("3-d Vector"),shared_type);
			trc->pushTest("Constructor",&vector3dConstructorTest);
			trc->pushTest("Comparison",&vector3dEqualityTest);
			trc->pushTest("Addition",&vector3dAdditionTest);
			trc->pushTest("Subtraction",&vector3dSubtractionTest);
			trc->pushTest("Dot-Product",&vector3dDotProductTest);
			trc->pushTest("Cross-Product",&vector3dCrossProductTest);
		pushSuite(trc);
	}

#endif

///@endcond