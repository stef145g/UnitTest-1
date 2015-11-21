//Confirmed Working 11/21/2015
//Primary Author: Jonathan Bedard

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

		dataStruct->resetTraverse();
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
			pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("Deletetion Test",adst,&singleTestDeletion,id),shared_type));
			pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("ADS Deletion Test",adst,&singleTestADSDeletion,id),shared_type));
            pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("Random Insertion Test",adst,&randomInsertionTest,id),shared_type));
            pushTest(smart_ptr<singleTest>(new adsTest<adsType,nodeType>("Random Insertion/Deletion Test",adst,&randomInsertionDeletionTest,id),shared_type));
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
                pushTest(smart_ptr<singleTest>(new setTest("Deletetion Test"+addition,(setTypes)i,&singleTestDeletion),shared_type));
                pushTest(smart_ptr<singleTest>(new setTest("ADS Deletetion Test"+addition,(setTypes)i,&singleTestADSDeletion),shared_type));
                pushTest(smart_ptr<singleTest>(new setTest("Random Insertion Test"+addition,(setTypes)i,&randomInsertionTest),shared_type));
                pushTest(smart_ptr<singleTest>(new setTest("Random Insertion/Deletion Test"+addition,(setTypes)i,&randomInsertionDeletionTest),shared_type));
            }
        }
        virtual ~setSuite(){}
    };

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
			//Unique element, unsorted, set
		pushSuite(smart_ptr<testSuite>(new setSuite(),shared_type));
	}

#endif