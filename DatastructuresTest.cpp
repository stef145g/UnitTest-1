/**
 * @file   DatastructuresTest.cpp
 * @author Jonathan Bedard
 * @date   8/6/2016
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
#include <chrono>
#include <thread>

using namespace os;
using namespace std;
using namespace test;

/*================================================================
	smart_ptr Test
================================================================*/

	//Demonstrate C deletion
	void c_deletion(void *v){delete (int*)v;}
	void c_str_deletin(void *v){delete (string*) v;}

	void refCountTest(smart_pointer_type typ) 
	{
		std::string locString = "DatastructuresTest.cpp, refCountTest(smart_pointer_type typ), ";
		if(typ==shared_type) locString+="shared_type";
		else if(typ==shared_type_array) locString+="shared_type_array";
		else if(typ==shared_type_dynamic_delete) locString+="shared_type_dynamic_delete";
		else throwGeneralTestException("Cannot run this function with this type",locString+"null_type");

		smart_ptr<int> temp1,temp2;

		//NULL pointer should have NULL ref count
		if(temp1.getRefCount()!=NULL)
			throwGeneralTestException("Non-NULL reference count",locString);

		if(typ==shared_type_array) temp1 = smart_ptr<int>(new int[5],shared_type_array);
		else if(typ==shared_type_dynamic_delete) temp1 = smart_ptr<int>(new int(1),&c_deletion);
		else temp1 = smart_ptr<int>(new int(1),shared_type);

		//Should have a reference count
		if(temp1.getRefCount()==NULL)
			throwGeneralTestException("NULL reference count",locString);

		//Reference count should be 1
		if(*(temp1.getRefCount())!=1)
			throwGeneralTestException("Reference count is "+to_string((long long unsigned)*(temp1.getRefCount()))+" expected 1",locString);

		//Reference count should be 2
		temp2 = temp1;
		if(*(temp1.getRefCount())!=2)
			throwGeneralTestException("Reference count is "+to_string((long long unsigned)*(temp1.getRefCount()))+" expected 2",locString);

		//Reference count should be 1
		temp1=NULL;
		if(*(temp2.getRefCount())!=1)
			throwGeneralTestException("Reference count is "+to_string((long long unsigned)*(temp2.getRefCount()))+" expected 1",locString);

		//NULL pointer should have NULL ref count
		if(temp1.getRefCount()!=NULL)
			throwGeneralTestException("Non-NULL reference count",locString);

		//Should have a reference count
		if(temp2.getRefCount()==NULL)
			throwGeneralTestException("NULL reference count",locString);

		//NULL pointer should have NULL ref count
		temp2=NULL;
		if(temp2.getRefCount()!=NULL)
			throwGeneralTestException("Non-NULL reference count",locString);
	}
	void refCountTest_shared(){refCountTest(shared_type);}
	void refCountTest_array(){refCountTest(shared_type_array);}
	void refCountTest_dyndel(){refCountTest(shared_type_dynamic_delete);}
	
	void compareNULL_type(smart_pointer_type typ) 
	{
		std::string locString = "DatastructuresTest.cpp, compareNULL_type(smart_pointer_type typ), ";
		if(typ==raw_type) locString+="raw_type";
		else if(typ==shared_type) locString+="shared_type";
		else if(typ==shared_type_array) locString+="shared_type_array";
		else if(typ==shared_type_dynamic_delete) locString+="shared_type_dynamic_delete";
		else throwGeneralTestException("Cannot run this function with this type",locString+"null_type");
		
		smart_ptr<int> temp1;

		//Ensure it is NULL
		if(temp1.get()!=NULL)
			throwGeneralTestException("Expected initial NULL",locString);

		//Other methods of detecting NULL
		if(temp1)
			throwGeneralTestException("NULL comparison failed (cast int)",locString);
		if(temp1!=NULL)
			throwGeneralTestException("NULL comparison failed (comp null)",locString);
		if(temp1.constGet()!=NULL)
			throwGeneralTestException("NULL comparison failed (constGet)",locString);

		//Attempt different methods of NULL casting
		int raw_val=1;
		for(int i=0;i<3;++i)
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
				throwGeneralTestException("Expected instantiaze not NULL ("+cast_type+")",locString);

			//Other methods of detecting not NULL
			if(!temp1)
				throwGeneralTestException("NULL comparison failed (cast int, "+cast_type,locString+")");
			if(temp1==NULL)
				throwGeneralTestException("NULL comparison failed (comp null, "+cast_type,locString+")");
			if(temp1.constGet()==NULL)
				throwGeneralTestException("NULL comparison failed (constGet, "+cast_type,locString+")");

			//Set NULL (3 ways)
			if(i==0) temp1=smart_ptr<int>();
			else if(i==1) temp1=smart_ptr<int>(NULL);
			else temp1=NULL;

			//Ensure it is NULL
			if(temp1.get()!=NULL)
				throwGeneralTestException("Expected NULL, "+cast_type,locString);

			//Other methods of detecting NULL
			if(temp1)
				throwGeneralTestException("NULL comparison failed, "+cast_type+"(cast int)",locString);
			if(temp1!=NULL)
				throwGeneralTestException("NULL comparison failed, "+cast_type+"(comp null)",locString);
			if(temp1.constGet()!=NULL)
				throwGeneralTestException("NULL comparison failed, "+cast_type+"(constGet)",locString);
			}
	}
	void compareNULL_raw() {compareNULL_type(raw_type);}
	void compareNULL_shared() {compareNULL_type(shared_type);}
	void compareNULL_array() {compareNULL_type(shared_type_array);}
	void compareNULL_dyndel() {compareNULL_type(shared_type_dynamic_delete);}

	void copyConstructor(smart_pointer_type typ) 
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
			throwGeneralTestException("Type bound improperly",locString);

		//Check if temp1 is NULL
		if(temp1)
			throwGeneralTestException("Expected initial NULL",locString);

		//Set temp1 and master
		temp1=master;

		//Compare types
		if(master.getType()!=temp1.getType())
			throwGeneralTestException("Equalitity type mis-match (=)",locString);
		if(master.getRefCount()!=temp1.getRefCount())
			throwGeneralTestException("Equalitity ref-count mis-match (=)",locString);
		if(master.getFunc()!=temp1.getFunc())
			throwGeneralTestException("Equalitity delete function mis-match (=)",locString);
		if(master.get()!=temp1.get())
			throwGeneralTestException("Equalitity pointer mis-match (=)",locString);
		if(master!=temp1)
			throwGeneralTestException("Equalitity compare mis-match (=)",locString);

		//Set temp1 and master
		temp1=smart_ptr<int>(master);

		//Compare types
		if(master.getType()!=temp1.getType())
			throwGeneralTestException("Equalitity type mis-match (copy)",locString);
		if(master.getRefCount()!=temp1.getRefCount())
			throwGeneralTestException("Equalitity ref-count mis-match (copy)",locString);
		if(master.getFunc()!=temp1.getFunc())
			throwGeneralTestException("Equalitity delete function mis-match (copy)",locString);
		if(master.get()!=temp1.get())
			throwGeneralTestException("Equalitity pointer mis-match (copy)",locString);
		if(master!=temp1)
			throwGeneralTestException("Equalitity compare mis-match (copy)",locString);
	}
	void copyConstructor_null() {copyConstructor(null_type);}
	void copyConstructor_raw() {copyConstructor(raw_type);}
	void copyConstructor_shared() {copyConstructor(shared_type);}
	void copyConstructor_array() {copyConstructor(shared_type_array);}
	void copyConstructor_dyndel() {copyConstructor(shared_type_dynamic_delete);}

	void comparisonTest(smart_pointer_type typ) 
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
			throwGeneralTestException("!= with self returned unexpected value",locString);
		if(!(master==master))
			throwGeneralTestException("== with self returned unexpected value",locString);

		srand((unsigned)time(NULL));

		//Preform 20 iterations to test
		for(int i=0;i<20;++i)
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
				throwGeneralTestException("smart_ptr == long failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master==ptr_comp))
				throwGeneralTestException("smart_ptr == void* failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master==comp_ptr))
				throwGeneralTestException("smart_ptr == smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(cur_comp==master))
				throwGeneralTestException("long == smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(ptr_comp==master))
				throwGeneralTestException("smart_ptr == void* failed: "+to_string((long long unsigned)cur_comp),locString);
			
			//General != test
			v = (unsigned long)master.get()!=cur_comp;
			rv = cur_comp!=(unsigned long)master.get();
			if(v!=(master!=cur_comp))
				throwGeneralTestException("smart_ptr != long failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master!=ptr_comp))
				throwGeneralTestException("smart_ptr != void* failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master!=comp_ptr))
				throwGeneralTestException("smart_ptr != smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(cur_comp!=master))
				throwGeneralTestException("long != smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(ptr_comp!=master))
				throwGeneralTestException("smart_ptr != void* failed: "+to_string((long long unsigned)cur_comp),locString);

			//General < test
			v = (unsigned long)master.get()<cur_comp;
			rv = cur_comp<(unsigned long)master.get();
            //cout<<v<<endl;
            //cout<<(master<cur_comp)<<endl;
			if(v!=(master<cur_comp))
				throwGeneralTestException("smart_ptr < long failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master<ptr_comp))
				throwGeneralTestException("smart_ptr < void* failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master<comp_ptr))
				throwGeneralTestException("smart_ptr < smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(cur_comp<master))
				throwGeneralTestException("long < smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(ptr_comp<master))
				throwGeneralTestException("smart_ptr < void* failed: "+to_string((long long unsigned)cur_comp),locString);

			//General > test
			v = (unsigned long)master.get()>cur_comp;
			rv = cur_comp>(unsigned long)master.get();
			if(v!=(master>cur_comp))
				throwGeneralTestException("smart_ptr > long failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master>ptr_comp))
				throwGeneralTestException("smart_ptr > void* failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master>comp_ptr))
				throwGeneralTestException("smart_ptr > smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(cur_comp>master))
				throwGeneralTestException("long > smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(ptr_comp>master))
				throwGeneralTestException("smart_ptr > void* failed: "+to_string((long long unsigned)cur_comp),locString);

			//General <= test
			v = (unsigned long)master.get()<=cur_comp;
			rv = cur_comp<=(unsigned long)master.get();
			if(v!=(master<=cur_comp))
				throwGeneralTestException("smart_ptr <= long failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master<=ptr_comp))
				throwGeneralTestException("smart_ptr <= void* failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master<=comp_ptr))
				throwGeneralTestException("smart_ptr <= smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(cur_comp<=master))
				throwGeneralTestException("long <= smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(ptr_comp<=master))
				throwGeneralTestException("smart_ptr <= void* failed: "+to_string((long long unsigned)cur_comp),locString);

			//General >= test
			v = (unsigned long)master.get()>=cur_comp;
			rv = cur_comp>=(unsigned long)master.get();
			if(v!=(master>=cur_comp))
				throwGeneralTestException("smart_ptr >= long failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master>=ptr_comp))
				throwGeneralTestException("smart_ptr >= void* failed: "+to_string((long long unsigned)cur_comp),locString);
			if(v!=(master>=comp_ptr))
				throwGeneralTestException("smart_ptr >= smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(cur_comp>=master))
				throwGeneralTestException("long >= smart_ptr failed: "+to_string((long long unsigned)cur_comp),locString);
			if(rv!=(ptr_comp>=master))
				throwGeneralTestException("smart_ptr >= void* failed: "+to_string((long long unsigned)cur_comp),locString);
		}
	}
	void comparisonTest_null() {comparisonTest(null_type);}
	void comparisonTest_raw() {comparisonTest(raw_type);}
	void comparisonTest_shared() {comparisonTest(shared_type);}
	void comparisonTest_array() {comparisonTest(shared_type_array);}
    void comparisonTest_dyndel() {comparisonTest(shared_type_dynamic_delete);}

	void derefTest(smart_pointer_type typ) 
	{
		std::string locString = "DatastructuresTest.cpp, derefTest(smart_pointer_type typ), ";
		if(typ==raw_type) locString+="raw_type";
		else if(typ==shared_type) locString+="shared_type";
		else if(typ==shared_type_array) locString+="shared_type_array";
		else if(typ==shared_type_dynamic_delete) locString+="shared_type_dynamic_delete";
		else throwGeneralTestException("Cannot run this function with this type",locString+"null_type");

		smart_ptr<string> ptr;
		string obj;

		if(typ == raw_type) ptr = smart_ptr<string>(&obj);
		else if(typ==shared_type_array) ptr = smart_ptr<string>(new string[5],shared_type_array);
		else if(typ==shared_type_dynamic_delete) ptr = smart_ptr<string>(new string(""),&c_deletion);
		else ptr = smart_ptr<string>(new string(""),shared_type);

		if(!ptr)
			throwGeneralTestException("Pointer unexpected NULL",locString);

		for(int i = 0;i<3;++i)
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
				throwGeneralTestException("Error at raw deref"+lInfo,locString);
			if(*ptr!="test")
				throwGeneralTestException("Error at operator deref"+lInfo,locString);
			if(ptr[0]!="test")
				throwGeneralTestException("Error at array deref"+lInfo,locString);

			if(ptr->substr(0,2)!="te")
				throwGeneralTestException("Error at -> operator"+lInfo,locString);
		}
	}
	void derefTest_raw() {derefTest(raw_type);}
	void derefTest_shared() {derefTest(shared_type);}
	void derefTest_array() {derefTest(shared_type_array);}
	void derefTest_dyndel() {derefTest(shared_type_dynamic_delete);}

/*================================================================
	Simple Hash
  ================================================================*/

	void basicHashInsertionTest() 
	{
		std::string locString = "DatastructuresTest.cpp, basicHashInsertionTest()";
		os::simpleHash<int> hashTable;

		//Basic insertion
		if(hashTable.exists(4))
			throwGeneralTestException("Integer inserted unexpectedly",locString);
		hashTable.insert(4);
		if(!hashTable.exists(4))
			throwGeneralTestException("Integer failed to insert",locString);
		hashTable.remove(4);
		if(hashTable.exists(4))
			throwGeneralTestException("Integer failed to remove",locString);
	}
	void emptyHashTest() 
	{
		std::string locString = "DatastructuresTest.cpp, emptyHashTest()";
		os::simpleHash<int> hashTable;

		//Insert
		if(hashTable.exists(4)||hashTable.exists(8))
			throwGeneralTestException("Integer inserted unexpectedly",locString);
		hashTable.insert(4);
		hashTable.insert(8);
		if(!hashTable.exists(4)||!hashTable.exists(8))
			throwGeneralTestException("Integer failed to insert",locString);

		hashTable.empty();
		if(hashTable.exists(4)||hashTable.exists(8))
			throwGeneralTestException("Empty failed",locString);
	}
	void conflictHashTest() 
	{
		std::string locString = "DatastructuresTest.cpp, conflictHashTest()";
		os::simpleHash<int> hashTable;
		hashTable.setSize(10);

		hashTable.insert(2);
		hashTable.insert(22);
		if(!hashTable.exists(2))
			throwGeneralTestException("Initial insertion failed",locString);
		if(!hashTable.exists(22))
			throwGeneralTestException("Secondary insertion failed",locString);

		hashTable.remove(2);
		if(hashTable.exists(2))
			throwGeneralTestException("Initial deletion failed",locString);
		if(!hashTable.exists(22))
			throwGeneralTestException("Secondary find after deletion failed",locString);
		hashTable.remove(22);
		if(hashTable.exists(22))
			throwGeneralTestException("Secondary deletion failed",locString);
	}
	void resizeHashTest() 
	{
		std::string locString = "DatastructuresTest.cpp, resizeHashTest()";
		os::simpleHash<int> hashTable;
		try
		{
			hashTable.setSize(0);
			throw -1;
		}
		catch(descriptiveException de){}
		catch(...)
		{throwGeneralTestException("Failed to throw error when setting illegal size",locString);}

		hashTable.insert(2);
		hashTable.insert(12);
		hashTable.insert(22);

		hashTable.setSize(10);

		if(hashTable.size()!=10)
			throwGeneralTestException("Failed to set size",locString);

		if(!hashTable.exists(2))
			throwGeneralTestException("Basic insertion failed",locString);
		if(!hashTable.exists(22))
			throwGeneralTestException("Overlap insertsion failed",locString);
		hashTable.remove(12);
		if(hashTable.exists(12))
			throwGeneralTestException("Remove failed",locString);
		if(!hashTable.exists(2))
			throwGeneralTestException("Basic find failed after remove",locString);
		if(!hashTable.exists(22))
			throwGeneralTestException("Overlap find failed after remove",locString);
	}
	void rawAccessTest()
	{
		std::string locString = "DatastructuresTest.cpp, rawAccessTest()";
		os::simpleHash<int> hashTable;
		hashTable.setSize(10);

		hashTable.insert(4);
		hashTable.insert(5);
		hashTable.insert(14);

		if(hashTable.atPosition(3))
			throwGeneralTestException("Position 3 has no data, should disallow access",locString);
		if(!hashTable.atPosition(4))
			throwGeneralTestException("Position 4 should have data",locString);

		if(hashTable[4]!=4)
			throwGeneralTestException("Expected 4 in position 4",locString);
		if(hashTable[5]!=5)
			throwGeneralTestException("Expected 5 in position 5",locString);
		if(hashTable[6]!=14)
			throwGeneralTestException("Expected 14 in position 6",locString);
	}

/*================================================================
	Lock Tests
  ================================================================*/

	void multithreadLock(os::lockable* lck)
	{
		lck->lock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		lck->unlock();
	}
		
	void basicLockTest() 
	{
		std::string locString = "DatastructuresTest.cpp, basicLockTest()";
		os::basicLock lck;

		//Single thread case
		if(lck.locked())
			throwGeneralTestException("Expected lock to be unlocked, never locked",locString);
		if(!lck.attemptLock())
			throwGeneralTestException("Expected lock to succeed",locString);
		if(lck.attemptLock())
			throwGeneralTestException("Expected lock to fail",locString);
		if(!lck.locked())
			throwGeneralTestException("Expected lock to be locked",locString);
		lck.unlock();
		if(lck.locked())
			throwGeneralTestException("Expected lock to be unlocked, finished locking",locString);

		//Multiple thread case
		std::thread thr(multithreadLock,&lck);
		try
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			if(!lck.locked())
				throwGeneralTestException("Expected lock to be locked, thread case",locString);
			lck.lock();
			if(!lck.locked())
				throwGeneralTestException("Expected lock to be locked, thread finished case",locString);
			lck.unlock();
		} catch(os::errorPointer erp)
		{
			thr.join();
			throw erp;
		}
		catch(descriptiveException de){
			thr.join();
			throwGeneralTestException("Lock threw unexpected error",locString);
		}
		thr.join();
	}
	void threadLockTest()
	{
		std::string locString = "DatastructuresTest.cpp, threadLockTest()";
		os::threadLock lck;

		//Single thread case
		if(lck.locked())
			throwGeneralTestException("Expected lock to be unlocked, never locked",locString);
		if(!lck.attemptLock())
			throwGeneralTestException("Expected lock to succeed",locString);
		if(!lck.attemptLock())
			throwGeneralTestException("Expected lock to succeed again",locString);
		if(!lck.locked())
			throwGeneralTestException("Expected lock to be locked",locString);
		lck.unlock();
		if(!lck.locked())
			throwGeneralTestException("Expected lock to be locked, single unlock case",locString);
		lck.unlock();
		if(lck.locked())
			throwGeneralTestException("Expected lock to be unlocked, finished locking",locString);

		//Multiple thread case
		std::thread thr(multithreadLock,&lck);
		try
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			if(!lck.locked())
				throwGeneralTestException("Expected lock to be locked, thread case",locString);
			lck.lock();
			if(!lck.locked())
				throwGeneralTestException("Expected lock to be locked, thread finished case",locString);
			lck.unlock();
		} catch(os::errorPointer erp)
		{
			thr.join();
			throw erp;
		}
		catch(descriptiveException de){
			thr.join();
			throwGeneralTestException("Lock threw unexpected error",locString);
		}
		thr.join();
	}
	void threadCounterTest() 
	{
		std::string locString = "DatastructuresTest.cpp, threadCounterTest()";
		os::threadCounter thrcnt(std::this_thread::get_id());
		os::threadCounter thrcnt2(thrcnt);

		if(thrcnt!=thrcnt2)
			throwGeneralTestException("Thread comparisons do not match",locString);
		if((size_t) thrcnt!=(size_t) thrcnt2)
			throwGeneralTestException("Thread hashes do not match",locString);

		if(thrcnt.count()!=0)
			throwGeneralTestException("Thread initialized with the wrong count",locString);
		++thrcnt;
		if(thrcnt.count()!=1)
			throwGeneralTestException("Thread failed to increment",locString);
		--thrcnt;
		if(thrcnt.count()!=0)
			throwGeneralTestException("Thread failed to decrement",locString);

		try
		{
			--thrcnt;
		}
		catch(descriptiveException de) {}
		catch(...)
		{throwGeneralTestException("Failed to throw error when illegally decrementing",locString);}
	}
	void basicMultiLockTest()
	{
		std::string locString = "DatastructuresTest.cpp, basicMultiLockTest()";
		os::readWriteLock lck;

		//Locking
		lck.lock();
		if(!lck.locked())
			throwGeneralTestException("Lock failed",locString);
		if(lck.try_lock())
			throwGeneralTestException("Double-lock unexpectantly succeeded",locString);
		lck.unlock();
		if(lck.locked())
			throwGeneralTestException("Lock failed to unlock",locString);

		//Increment
		++lck;
		if(lck.numReaders()!=1)
			throwGeneralTestException("Number of readers failed (1st time)",locString);
		if(lck.counter()!=1)
			throwGeneralTestException("Number of counters failed (1st time)",locString);
		if(!lck.try_increment())
			throwGeneralTestException("Double increment fialed",locString);
		if(lck.numReaders()!=2)
			throwGeneralTestException("Number of readers failed (2nd time)",locString);
		if(lck.counter()!=2)
			throwGeneralTestException("Number of counters failed (2nd time)",locString);
		if(lck.try_lock())
			throwGeneralTestException("Lock succeeded after read increment",locString);
		--lck;
		--lck;
		if(lck.numReaders()!=0)
			throwGeneralTestException("Failed on last reader query",locString);
		if(lck.counter()!=0)
			throwGeneralTestException("Failed on last counter query",locString);

		//Multiple thread case (first)
		std::thread thr(multithreadLock,&lck);
		try
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			if(!lck.locked())
				throwGeneralTestException("Expected lock to be locked, thread case",locString);
			lck.lock();
			if(!lck.locked())
				throwGeneralTestException("Expected lock to be locked, thread finished case",locString);
			lck.unlock();
		} catch(os::errorPointer erp)
		{
			thr.join();
			throw erp;
		}
		catch(descriptiveException de){
			thr.join();
			throwGeneralTestException("Lock threw unexpected error",locString);
		}
		thr.join();
	}
	void threadMultiLockTest()
	{
		std::string locString = "DatastructuresTest.cpp, threadMultiLockTest()";
		os::readWriteLock lck(os::readWriteLock::RECURSIVE);

		//Locking
		lck.lock();
		if(!lck.locked())
			throwGeneralTestException("Lock failed",locString);
		if(!lck.try_lock())
			throwGeneralTestException("Double-lock failed",locString);
		lck.unlock();
		lck.unlock();
		if(lck.locked())
			throwGeneralTestException("Lock failed to unlock",locString);

		//Increment
		lck++;
		if(lck.numReaders()!=1)
			throwGeneralTestException("Number of readers failed (1st time)",locString);
		if(lck.counter()!=1)
			throwGeneralTestException("Number of counters failed (1st time)",locString);
		if(!lck.try_increment())
			throwGeneralTestException("Double increment fialed",locString);
		if(lck.numReaders()!=1)
			throwGeneralTestException("Number of readers failed (2nd time)",locString);
		if(lck.counter()!=2)
			throwGeneralTestException("Number of counters failed (2nd time)",locString);
		if(!lck.try_lock())
			throwGeneralTestException("Lock succeeded after read increment",locString);
		lck.unlock();
		--lck;
		--lck;
		if(lck.numReaders()!=0)
			throwGeneralTestException("Failed on last reader query",locString);
		if(lck.counter()!=0)
			throwGeneralTestException("Failed on last counter query",locString);

		//Multiple thread case (first)
		std::thread thr(multithreadLock,&lck);
		try
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			if(!lck.locked())
				throwGeneralTestException("Expected lock to be locked, thread case",locString);
			lck.lock();
			if(!lck.locked())
				throwGeneralTestException("Expected lock to be locked, thread finished case",locString);
			lck.unlock();
		} catch(os::errorPointer erp)
		{
			thr.join();
			throw erp;
		}
		catch(descriptiveException de){
			thr.join();
			throwGeneralTestException("Lock threw unexpected error",locString);
		}
		thr.join();
	}

/*================================================================
	Node Testing
  ================================================================*/

	struct dummyInt
	{
		int data;
		dummyInt(int d=0){data=d;}
		dummyInt(const dummyInt& d){data=d.data;}
		dummyInt& operator=(int d)
		{
			data=d;
			return *this;
		}
		dummyInt& operator=(const dummyInt d)
		{
			data=d.data;
			return *this;
		}
		inline int compare(const dummyInt& di) const {return data-di.data;}
		inline operator size_t() const {return (size_t) data;}

		#undef CURRENT_CLASS
		#define CURRENT_CLASS dummyInt
		COMPARE_OPERATORS
	};

	void objectNodeTest()
	{
		std::string locString = "DatastructuresTest.cpp, objectNodeTest()";
		os::objectNode<int> nd1(1);
		os::objectNode<int> nd2(3);
		if(!nd1 || !nd2)
			throwGeneralTestException("Validity check failure",locString);
		if(nd1>=nd2)
			throwGeneralTestException("Node 2 should be greater than node 1",locString);
		if((size_t)nd1 != 1)
			throwGeneralTestException("Size cast failure: node 1",locString);
		if((size_t)nd2 != 3)
			throwGeneralTestException("Size cast failure: node 2",locString);
	}
	void pointerNodeTest()
	{
		std::string locString = "DatastructuresTest.cpp, pointerNodeTest()";
		os::pointerNode<dummyInt> nd1;
		os::pointerNode<dummyInt> nd2;
		if(nd1 || nd2)
			throwGeneralTestException("Validity check failure",locString);
		if(nd1!=nd2)
			throwGeneralTestException("Nodes should be equal",locString);

		dummyInt arr[2];
		arr[0].data=3;
		arr[1].data=1;

		nd1=os::pointerNode<dummyInt>(arr);
		nd2=os::pointerNode<dummyInt>(arr+1);
		if(nd1<=nd2)
			throwGeneralTestException("Node 1 should be greater than node 2",locString);
		if((size_t)nd1 != 3)
			throwGeneralTestException("Size cast failure: node 1",locString);
		if((size_t)nd2 != 1)
			throwGeneralTestException("Size cast failure: node 2",locString);
	}
	void rawPointerNodeTest()
	{
		std::string locString = "DatastructuresTest.cpp, rawPointerNodeTest()";
		os::rawPointerNode<int> nd1;
		os::rawPointerNode<int> nd2;
		if(nd1 || nd2)
			throwGeneralTestException("Validity check failure",locString);
		if(nd1!=nd2)
			throwGeneralTestException("Nodes should be equal",locString);

		int arr[2];
		arr[0]=3;
		arr[1]=1;
		nd1=os::rawPointerNode<int>(arr);
		nd2=os::rawPointerNode<int>(arr+1);

		if(nd1>=nd2)
			throwGeneralTestException("Node 2 should be greater than node 1",locString);
		if((size_t)nd1 != (size_t)arr)
			throwGeneralTestException("Size cast failure: node 1",locString);
		if((size_t)nd2 != (size_t)(arr+1))
			throwGeneralTestException("Size cast failure: node 2",locString);
	}

/*================================================================
	Custom Tests
  ================================================================*/

    template<class datastruct>
    void customTest(std::string className,datastruct& ds)
    {}

    //Vector object test
    template<class datastruct>
    void vectorObjectTest(std::string className,datastruct& ds)
    {
        std::string locString = "DatastructuresTest.cpp, vectorObjectTest<"+className+">()";
        for(int i=0;i<100;++i)
            ds.insert(100-i);
        
        bool sorted=true;
        for(size_t i=0;i<99 && sorted;++i)
        {
            if(ds[i]>ds[i+1])
                sorted=false;
        }
        if(sorted)
            throwGeneralTestException("Unexpectantly sorted",locString);
        
        ds.sort();
        sorted=true;
        for(size_t i=0;i<99 && sorted;++i)
        {
            if(ds[i]>ds[i+1])
                sorted=false;
        }
        if(!sorted)
            throwGeneralTestException("Unsorted vector error",locString);
    }
    //Vector pointer test
    template<class datastruct>
    void vectorPointerTest(std::string className,datastruct& ds)
    {
        std::string locString = "DatastructuresTest.cpp, vectorPointerTest<"+className+">()";
        os::smart_ptr<dummyInt> arr[100];
        dummyInt rawArr[100];
        for(size_t i=100;i>0;--i)
        {
            rawArr[i-1]=(int)i-1;
            arr[100-i]=os::smart_ptr<dummyInt>(rawArr+(i-1));
        }
        for(size_t i=0;i<100;++i)
            ds.insert(arr[i]);
        
        bool sorted=true;
        for(size_t i=0;i<99 && sorted;++i)
        {
            if(ds[i]>ds[i+1])
                sorted=false;
        }
        if(sorted)
            throwGeneralTestException("Unexpectantly sorted",locString);
        
        ds.sort();
        sorted=true;
        for(size_t i=0;i<99;++i)
        {
            if(ds[i]>ds[i+1])
                sorted=false;
        }
        if(!sorted)
            throwGeneralTestException("Unsorted vector error",locString);
        
    }
    //Vector tests
    void customTest(std::string className, objectVectorThreadSafe<dummyInt>& ds){vectorObjectTest<objectVectorThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, objectVector<dummyInt>& ds){vectorObjectTest<objectVector<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerVectorThreadSafe<dummyInt>& ds){vectorPointerTest<pointerVectorThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerVector<dummyInt>& ds){vectorPointerTest<pointerVector<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerVectorThreadSafe<dummyInt>& ds){vectorPointerTest<rawPointerVectorThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerVector<dummyInt>& ds){vectorPointerTest<rawPointerVector<dummyInt> >(className,ds);}

    //Stack object test
    template<class datastruct>
    void stackObjectTest(std::string className,datastruct& ds)
    {
    	std::string locString = "DatastructuresTest.cpp, stackObjectTest<"+className+">()";
    	ds.insert(dummyInt(3));
    	ds.insert(dummyInt(2));
    	ds.insert(dummyInt(1));

    	if(ds.top()!=dummyInt(1))
    		throwGeneralTestException("Top value unexpected (1)",locString);
    	ds.pop();
    	if(ds.top()!=dummyInt(2))
    		throwGeneralTestException("Top value unexpected (2)",locString);
    	ds.pop();
    	if(ds.top()!=dummyInt(3))
    		throwGeneralTestException("Top value unexpected (3)",locString);
    	ds.pop();

    	bool threw=false;
    	try
    	{ds.pop();}
    	catch(...){threw=true;}
    	if(!threw)
    		throwGeneralTestException("Expected exception",locString);

    	for(int i=0;i<100;++i)
    		ds.insert(dummyInt(i));
    	if(ds.size()!=100)
    		throwGeneralTestException("Mass insertion failed",locString);
    	for(int i=99;i>=0;--i)
    	{
    		if(ds.top()!=dummyInt(i))
    			throwGeneralTestException("Mass access failed",locString);
    		ds.pop();
    	}
    	if(ds.size()!=0)
    		throwGeneralTestException("Mass removal failed",locString);
    }
    //Stack pointer test
    template<class datastruct>
    void stackPointerTest(std::string className,datastruct& ds)
    {
    	std::string locString = "DatastructuresTest.cpp, stackPointerTest<"+className+">()";
    	os::smart_ptr<dummyInt> pt1(new dummyInt(1),os::shared_type);
    	os::smart_ptr<dummyInt> pt2(new dummyInt(2),os::shared_type);
    	os::smart_ptr<dummyInt> pt3(new dummyInt(3),os::shared_type);
    	ds.insert(pt3);
    	ds.insert(pt2);
    	ds.insert(pt1);

    	if(ds.top()!=pt1)
    		throwGeneralTestException("Top value unexpected (1)",locString);
    	ds.pop();
    	if(ds.top()!=pt2)
    		throwGeneralTestException("Top value unexpected (2)",locString);
    	ds.pop();
    	if(ds.top()!=pt3)
    		throwGeneralTestException("Top value unexpected (3)",locString);
    	ds.pop();

    	bool threw=false;
    	try
    	{ds.pop();}
    	catch(...){threw=true;}
    	if(!threw)
    		throwGeneralTestException("Expected exception",locString);

    	for(int i=0;i<100;++i)
    		ds.insert(os::smart_ptr<dummyInt>(new dummyInt(i),os::shared_type));
    	if(ds.size()!=100)
    		throwGeneralTestException("Mass insertion failed",locString);
    	for(int i=99;i>=0;--i)
    		ds.pop();
    	if(ds.size()!=0)
    		throwGeneralTestException("Mass removal failed",locString);
    }

    void customTest(std::string className, objectLinkedStackThreadSafe<dummyInt>& ds){stackObjectTest<objectLinkedStackThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, objectLinkedStack<dummyInt>& ds){stackObjectTest<objectLinkedStack<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerLinkedStackThreadSafe<dummyInt>& ds){stackPointerTest<pointerLinkedStackThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerLinkedStack<dummyInt>& ds){stackPointerTest<pointerLinkedStack<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerLinkedStackThreadSafe<dummyInt>& ds){stackPointerTest<rawPointerLinkedStackThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerLinkedStack<dummyInt>& ds){stackPointerTest<rawPointerLinkedStack<dummyInt> >(className,ds);}

    void customTest(std::string className, objectArrayStackThreadSafe<dummyInt>& ds){stackObjectTest<objectArrayStackThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, objectArrayStack<dummyInt>& ds){stackObjectTest<objectArrayStack<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerArrayStackThreadSafe<dummyInt>& ds){stackPointerTest<pointerArrayStackThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerArrayStack<dummyInt>& ds){stackPointerTest<pointerArrayStack<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerArrayStackThreadSafe<dummyInt>& ds){stackPointerTest<rawPointerArrayStackThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerArrayStack<dummyInt>& ds){stackPointerTest<rawPointerArrayStack<dummyInt> >(className,ds);}

    //Queue object test
    template<class datastruct>
    void queueObjectTest(std::string className,datastruct& ds)
    {
    	std::string locString = "DatastructuresTest.cpp, stackObjectTest<"+className+">()";
    	ds.insert(dummyInt(3));
    	ds.insert(dummyInt(2));
    	ds.insert(dummyInt(1));

    	if(ds.top()!=dummyInt(3))
    		throwGeneralTestException("Top value unexpected (3)",locString);
    	ds.pop();
    	if(ds.top()!=dummyInt(2))
    		throwGeneralTestException("Top value unexpected (2)",locString);
    	ds.pop();
    	if(ds.top()!=dummyInt(1))
    		throwGeneralTestException("Top value unexpected (1)",locString);
    	ds.pop();

    	bool threw=false;
    	try
    	{ds.pop();}
    	catch(...){threw=true;}
    	if(!threw)
    		throwGeneralTestException("Expected exception",locString);

    	for(int i=0;i<100;++i)
    		ds.insert(dummyInt(i));
    	if(ds.size()!=100)
    		throwGeneralTestException("Mass insertion failed",locString);
    	for(int i=0;i<100;++i)
    	{
    		if(ds.top()!=dummyInt(i))
    			throwGeneralTestException("Mass access failed",locString);
    		ds.pop();
    	}
    	if(ds.size()!=0)
    		throwGeneralTestException("Mass removal failed",locString);
    }
    //Queue pointer test
    template<class datastruct>
    void queuePointerTest(std::string className,datastruct& ds)
    {
    	std::string locString = "DatastructuresTest.cpp, stackPointerTest<"+className+">()";
    	os::smart_ptr<dummyInt> pt1(new dummyInt(1),os::shared_type);
    	os::smart_ptr<dummyInt> pt2(new dummyInt(2),os::shared_type);
    	os::smart_ptr<dummyInt> pt3(new dummyInt(3),os::shared_type);
    	ds.insert(pt3);
    	ds.insert(pt2);
    	ds.insert(pt1);

    	if(ds.top()!=pt3)
    		throwGeneralTestException("Top value unexpected (3)",locString);
    	ds.pop();
    	if(ds.top()!=pt2)
    		throwGeneralTestException("Top value unexpected (2)",locString);
    	ds.pop();
    	if(ds.top()!=pt1)
    		throwGeneralTestException("Top value unexpected (1)",locString);
    	ds.pop();

    	bool threw=false;
    	try
    	{ds.pop();}
    	catch(...){threw=true;}
    	if(!threw)
    		throwGeneralTestException("Expected exception",locString);

    	for(int i=0;i<100;++i)
    		ds.insert(os::smart_ptr<dummyInt>(new dummyInt(i),os::shared_type));
    	if(ds.size()!=100)
    		throwGeneralTestException("Mass insertion failed",locString);
    	for(int i=99;i>=0;--i)
    		ds.pop();
    	if(ds.size()!=0)
    		throwGeneralTestException("Mass removal failed",locString);
    }

    void customTest(std::string className, objectLinkedQueueThreadSafe<dummyInt>& ds){queueObjectTest<objectLinkedQueueThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, objectLinkedQueue<dummyInt>& ds){queueObjectTest<objectLinkedQueue<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerLinkedQueueThreadSafe<dummyInt>& ds){queuePointerTest<pointerLinkedQueueThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerLinkedQueue<dummyInt>& ds){queuePointerTest<pointerLinkedQueue<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerLinkedQueueThreadSafe<dummyInt>& ds){queuePointerTest<rawPointerLinkedQueueThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerLinkedQueue<dummyInt>& ds){queuePointerTest<rawPointerLinkedQueue<dummyInt> >(className,ds);}

    void customTest(std::string className, objectBoundedQueueThreadSafe<dummyInt>& ds){queueObjectTest<objectBoundedQueueThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, objectBoundedQueue<dummyInt>& ds){queueObjectTest<objectBoundedQueue<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerBoundedQueueThreadSafe<dummyInt>& ds){queuePointerTest<pointerBoundedQueueThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, pointerBoundedQueue<dummyInt>& ds){queuePointerTest<pointerBoundedQueue<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerBoundedQueueThreadSafe<dummyInt>& ds){queuePointerTest<rawPointerBoundedQueueThreadSafe<dummyInt> >(className,ds);}
    void customTest(std::string className, rawPointerBoundedQueue<dummyInt>& ds){queuePointerTest<rawPointerBoundedQueue<dummyInt> >(className,ds);}


	template<class datastruct>
	void customADSTest(std::string className)
	{
        datastruct ds;
        customTest(className,ds);
	}

/*================================================================
	ADS Tests
  ================================================================*/

	template<class datastruct>
	void singleInsertionNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, singleInsertionNodeTest<"+className+">()";
		datastruct ds;
		if(ds.size()!=0)
			throwGeneralTestException("Expected size to be 0",locString);

		if(!ds.insert(4))
			throwGeneralTestException("Cannot insert element",locString);
		if(!ds.find(4))
			throwGeneralTestException("Cannot find inserted element",locString);

		if(ds.find(5))
			throwGeneralTestException("Found element which was not inserted",locString);
		if(!ds.insert(5))
			throwGeneralTestException("Cannot insert element (2)",locString);
		if(ds.size()!=2)
			throwGeneralTestException("Expected size to be 2",locString);
	}
	template<class datastruct>
	void singleInsertionPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, singleInsertionPointerTest<"+className+">()";
		datastruct ds;
		if(ds.size()!=0)
			throwGeneralTestException("Expected size to be 0",locString);

		os::smart_ptr<dummyInt> ptr(new dummyInt(4),shared_type);
		if(!ds.insert(ptr))
			throwGeneralTestException("Cannot insert element",locString);
		if(!ds.find(ptr))
			throwGeneralTestException("Cannot find inserted element",locString);

		if(ds.find(os::smart_ptr<dummyInt>(new dummyInt(5),shared_type)))
			throwGeneralTestException("Found element which was not inserted",locString);
		if(!ds.insert(os::smart_ptr<dummyInt>(new dummyInt(5),shared_type)))
			throwGeneralTestException("Cannot insert element (2)",locString);
		if(ds.size()!=2)
			throwGeneralTestException("Expected size to be 2",locString);
	}

	template<class datastruct>
	void singleDeletionNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, singleDeletionNodeTest<"+className+">()";
		datastruct ds;
		if(ds.size()!=0)
			throwGeneralTestException("Expected size to be 0",locString);

		ds.insert(4);
		ds.insert(5);
		if(ds.size()!=2)
			throwGeneralTestException("Expected size to be 2",locString);
		if(!ds.remove(4))
			throwGeneralTestException("Failure to remove",locString);
		if(ds.find(4))
			throwGeneralTestException("Found removed element",locString);
		if(ds.size()!=1)
			throwGeneralTestException("Expected size to be 1",locString);
		if(ds.remove(6))
			throwGeneralTestException("Move succeded with uninserted node",locString);

		os::iterator<dummyInt> fst=ds.first();
		if(*fst!=dummyInt(5))
			throwGeneralTestException("Unexpected value of initial node",locString);
	}
	template<class datastruct>
	void singleDeletionPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, singleDeletionPointerTest<"+className+">()";
		datastruct ds;
		if(ds.size()!=0)
			throwGeneralTestException("Expected size to be 0",locString);

		os::smart_ptr<dummyInt> ptr(new dummyInt(4),shared_type);

		ds.insert(ptr);
		ds.insert(smart_ptr<dummyInt>(new dummyInt(5),shared_type));
		if(ds.size()!=2)
			throwGeneralTestException("Expected size to be 2",locString);
		if(!ds.remove(ptr))
			throwGeneralTestException("Failure to remove",locString);
		if(ds.find(ptr))
			throwGeneralTestException("Found removed element",locString);
		if(ds.size()!=1)
			throwGeneralTestException("Expected size to be 1",locString);
		if(ds.remove(smart_ptr<dummyInt>(new dummyInt(6),shared_type)))
			throwGeneralTestException("Move succeded with uninserted node",locString);

		os::iterator<dummyInt> fst=ds.first();
		if(*fst!=dummyInt(5))
			throwGeneralTestException("Unexpected value of initial node",locString);
	}
	template<class datastruct>
	void iteratorDeletionNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, singleDeletionNodeTest<"+className+">()";
		datastruct ds;
		if(ds.size()!=0)
			throwGeneralTestException("Expected size to be 0",locString);

		ds.insert(4);
		ds.insert(5);
		if(ds.size()!=2)
			throwGeneralTestException("Expected size to be 2",locString);
		os::iterator<dummyInt> fst=ds.search(dummyInt(4));
		fst.remove();
		if(ds.find(4))
			throwGeneralTestException("Found removed element",locString);
		if(ds.size()!=1)
			throwGeneralTestException("Expected size to be 1",locString);

		fst=ds.first();
		if(*fst!=dummyInt(5))
			throwGeneralTestException("Unexpected value of initial node",locString);
	}
	template<class datastruct>
	void iteratorDeletionPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, singleDeletionPointerTest<"+className+">()";
		datastruct ds;
		if(ds.size()!=0)
			throwGeneralTestException("Expected size to be 0",locString);

		os::smart_ptr<dummyInt> ptr(new dummyInt(4),shared_type);

		ds.insert(ptr);
		ds.insert(smart_ptr<dummyInt>(new dummyInt(5),shared_type));
		if(ds.size()!=2)
			throwGeneralTestException("Expected size to be 2",locString);
		
		os::iterator<dummyInt> fst=ds.search(ptr);
		fst.remove();
		if(ds.find(ptr))
			throwGeneralTestException("Found removed element",locString);
		if(ds.size()!=1)
			throwGeneralTestException("Expected size to be 1",locString);

		fst=ds.first();
		if(*fst!=dummyInt(5))
			throwGeneralTestException("Unexpected value of initial node",locString);
	}

	template<class datastruct>
	void simpleIteratorNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, simpleIteratorNodeTest<"+className+">()";
		datastruct ds;
		ds.insert(1);
		ds.insert(2);
		ds.insert(3);
		os::iterator<dummyInt> fst=ds.first();
		os::iterator<dummyInt> lst=ds.last();

		if(!fst)
			throwGeneralTestException("No first node defined",locString);
		if(!lst)
			throwGeneralTestException("No last node defined",locString);
		if(fst==lst)
			throwGeneralTestException("First and last illegally match",locString);
		os::iterator<dummyInt> fst1=ds.first();
		if(fst!=fst1)
			throwGeneralTestException("New and old first do not match",locString);
	}
	template<class datastruct>
	void simpleIteratorPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, simpleIteratorPointerTest<"+className+">()";
		datastruct ds;
		ds.insert(smart_ptr<dummyInt>(new dummyInt(1),shared_type));
		ds.insert(smart_ptr<dummyInt>(new dummyInt(2),shared_type));
		ds.insert(smart_ptr<dummyInt>(new dummyInt(3),shared_type));
		os::iterator<dummyInt> fst=ds.first();
		os::iterator<dummyInt> lst=ds.last();

		if(!fst)
			throwGeneralTestException("No first node defined",locString);
		if(!lst)
			throwGeneralTestException("No last node defined",locString);
	}

	template<class datastruct>
	void searchNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, searchNodeTest<"+className+">()";
		datastruct ds;
		ds.insert(1);
		ds.insert(2);
		ds.insert(3);
		os::iterator<dummyInt> fnd=ds.search(dummyInt(2));

		if(!fnd || *fnd!=dummyInt(2))
			throwGeneralTestException("Could not find 2",locString);
		fnd=ds.search(dummyInt(0));
		if(fnd)
			throwGeneralTestException("Unexpectantly found 0",locString);
		fnd=ds.search(dummyInt(1));
		if(!fnd || *fnd!=dummyInt(1))
			throwGeneralTestException("Could not find 1",locString);
	}
	template<class datastruct>
	void searchPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, searchPointerTest<"+className+">()";
		datastruct ds;
		smart_ptr<dummyInt> d1(new dummyInt(1),shared_type);
		smart_ptr<dummyInt> d2(new dummyInt(2),shared_type);
		ds.insert(d1);
		ds.insert(d2);
		ds.insert(smart_ptr<dummyInt>(new dummyInt(3),shared_type));
		os::iterator<dummyInt> fnd=ds.search(d2);

		if(!fnd || *fnd!=dummyInt(2))
			throwGeneralTestException("Could not find 2",locString);
		fnd=ds.search(smart_ptr<dummyInt>(new dummyInt(0),os::shared_type));
		if(fnd)
			throwGeneralTestException("Unexpectantly found 0",locString);
		fnd=ds.search(d1);
		if(!fnd || *fnd!=dummyInt(1))
			throwGeneralTestException("Could not find 1",locString);
	}

	//Copy test
	template<class datastruct>
	void copyStructTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, copyStructTest<"+className+">()";

		datastruct ds1;
		for(int i=0;i<100;++i)
			ds1.insert(rand()%1000);

		datastruct ds2(ds1);

		auto it1=ds1.first();
		auto it2=ds2.first();

		while(it1 || it2)
		{
			if(!it1) 
				throwGeneralTestException("Primary datastructure smaller than copy",locString);
			if(!it2) 
				throwGeneralTestException("Primary datastructure larger than copy",locString);
			if(*it1 != *it2)
				throwGeneralTestException("Primary and copied datastructure do not match",locString);
			++it1;
			++it2;
		}
	}
	template<class datastruct>
	void copyStructPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, copyStructPointerTest<"+className+">()";

		datastruct ds1;
		for(int i=0;i<100;++i)
			ds1.insert(smart_ptr<dummyInt>(new dummyInt(rand()%1000),shared_type));

		datastruct ds2(ds1);

		auto it1=ds1.first();
		auto it2=ds2.first();

		while(it1 || it2)
		{
			if(!it1) 
				throwGeneralTestException("Primary datastructure smaller than copy",locString);
			if(!it2) 
				throwGeneralTestException("Primary datastructure larger than copy",locString);
			if(*it1 != *it2)
				throwGeneralTestException("Primary and copied datastructure do not match",locString);
			++it1;
			++it2;
		}
	}

	//Iteration tests
	template<class datastruct>
	void noIteratorNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, noIteratorNodeTest<"+className+">()";
		datastruct ds;
		ds.insert(4);
		ds.insert(2);
		ds.insert(5);

		os::iterator<dummyInt> it=ds.first();

		bool except=false;
		try{++it;}
		catch(std::exception e)
		{except=true;}
		if(!except)
			throwGeneralTestException("Unexpected iteration success (++it)",locString);

		except=false;
		try{it++;}
		catch(std::exception e)
		{except=true;}
		if(!except)
			throwGeneralTestException("Unexpected iteration success (it++)",locString);

		except=false;
		try{it+=1;}
		catch(std::exception e)
		{except=true;}
		if(!except)
			throwGeneralTestException("Unexpected iteration success (it+=1)",locString);

		except=false;
		try{it=it+1;}
		catch(std::exception e)
		{except=true;}
		if(!except)
			throwGeneralTestException("Unexpected iteration success (it+1)",locString);
	}
	template<class datastruct>
	void noIteratorPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, noIteratorPointerTest<"+className+">()";
		datastruct ds;
		ds.insert(os::smart_ptr<dummyInt>(new dummyInt(4),os::shared_type));
		ds.insert(os::smart_ptr<dummyInt>(new dummyInt(2),os::shared_type));
		ds.insert(os::smart_ptr<dummyInt>(new dummyInt(5),os::shared_type));

		os::iterator<dummyInt> it=ds.first();

		bool except=false;
		try{++it;}
		catch(std::exception e)
		{except=true;}
		if(!except)
			throwGeneralTestException("Unexpected iteration success (++it)",locString);

		except=false;
		try{it++;}
		catch(std::exception e)
		{except=true;}
		if(!except)
			throwGeneralTestException("Unexpected iteration success (it++)",locString);

		except=false;
		try{it+=1;}
		catch(std::exception e)
		{except=true;}
		if(!except)
			throwGeneralTestException("Unexpected iteration success (it+=1)",locString);

		except=false;
		try{it=it+1;}
		catch(std::exception e)
		{except=true;}
		if(!except)
			throwGeneralTestException("Unexpected iteration success (it+1)",locString);
	}
	template<class datastruct>
	void basicIteratorNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, basicIteratorNodeTest<"+className+">()";
		datastruct ds;
		ds.insert(4);
		ds.insert(5);
		ds.insert(3);

		os::constIterator<dummyInt> it=ds.first();
		int cnt=0;
		while(it && cnt<3)
		{
			++it;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("++it iteration failed",locString);

		cnt=0;
		it=ds.first();
		while(it && cnt<3)
		{
			it++;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("it++ iteration failed",locString);

		cnt=0;
		it=ds.first();
		while(it && cnt<3)
		{
			it+=1;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("+= iteration failed",locString);

		cnt=0;
		it=ds.first();
		while(it && cnt<3)
		{
			it=it+1;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("+ iteration failed",locString);

		cnt=0;
		it=ds.last();

		while(it && cnt<3)
		{
			--it;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("--it iteration failed",locString);

		cnt=0;
		it=ds.last();
		while(it && cnt<3)
		{
			it--;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("it-- iteration failed",locString);

		cnt=0;
		it=ds.last();
		while(it && cnt<3)
		{
			it-=1;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("-= iteration failed",locString);

		cnt=0;
		it=ds.last();
		while(it && cnt<3)
		{
			it=it-1;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("- iteration failed",locString);
	}
	template<class datastruct>
	void basicIteratorPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, basicIteratorPointerTest<"+className+">()";
		datastruct ds;
		ds.insert(os::smart_ptr<dummyInt>(new dummyInt(4),os::shared_type));
		ds.insert(os::smart_ptr<dummyInt>(new dummyInt(2),os::shared_type));
		ds.insert(os::smart_ptr<dummyInt>(new dummyInt(5),os::shared_type));

		os::constIterator<dummyInt> it=ds.first();
		int cnt=0;
		while(it && cnt<3)
		{
			++it;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("++it iteration failed",locString);

		cnt=0;
		it=ds.first();
		while(it && cnt<3)
		{
			it++;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("it++ iteration failed",locString);

		cnt=0;
		it=ds.first();
		while(it && cnt<3)
		{
			it+=1;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("+= iteration failed",locString);

		cnt=0;
		it=ds.first();
		while(it && cnt<3)
		{
			it=it+1;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("+ iteration failed",locString);

		cnt=0;
		it=ds.last();
		while(it && cnt<3)
		{
			--it;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("--it iteration failed",locString);

		cnt=0;
		it=ds.last();
		while(it && cnt<3)
		{
			it--;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("it-- iteration failed",locString);

		cnt=0;
		it=ds.last();
		while(it && cnt<3)
		{
			it-=1;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("-= iteration failed",locString);

		cnt=0;
		it=ds.last();
		while(it && cnt<3)
		{
			it=it-1;
			++cnt;
		}
		if(it || cnt<3)
			throwGeneralTestException("- iteration failed",locString);
	}
	template<class datastruct>
	void randomIteratorNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, randomIteratorNodeTest<"+className+">()";
		datastruct ds;
		dummyInt dat[100];
		bool found[100];
		memset(found,0,100*sizeof(bool));
		srand((unsigned)time(NULL));

		for(size_t i=0;i<100;++i)
		{
			dummyInt temp=rand()%1000;
			bool tfnd=false;
			for(size_t cnt=0;cnt<i && !tfnd;++cnt)
			{
				if(dat[cnt]==temp) tfnd=true;
			}
			if(tfnd) --i;
			else dat[i]=temp;
		}

		for(size_t i=0;i<100;++i)
			ds.insert(dat[i]);
		
		for(os::iterator<dummyInt> it=ds.first();it;++it)
		{
			bool fnd=false;
			for(size_t i=0;i<100 && !fnd;++i)
			{
				if(dat[i]==*it)
				{
					fnd=true;
					found[i]=true;
				}
			}
		}
		for(size_t i=0;i<100;i++)
		{
			if(!found[i])
				throwGeneralTestException("Inserted element "+std::to_string(dat[i])+" @ "+std::to_string(i)+" not found",locString);
		}
	}
	template<class datastruct>
	void randomIteratorPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, randomIteratorPointerTest<"+className+">()";
		datastruct ds;
		dummyInt dat[100];
		bool found[100];
		memset(found,0,100*sizeof(bool));
		srand((unsigned)time(NULL));

		for(size_t i=0;i<100;++i)
		{
			dummyInt temp=rand()%1000;
			bool tfnd=false;
			for(size_t cnt=0;cnt<i && !tfnd;++cnt)
			{
				if(dat[cnt]==temp) tfnd=true;
			}
			if(tfnd) --i;
			else dat[i]=temp;
		}

		for(size_t i=0;i<100;++i)
			ds.insert(os::smart_ptr<dummyInt>(new dummyInt(dat[i]),os::shared_type));
		
		for(os::iterator<dummyInt> it=ds.first();it;++it)
		{
			bool fnd=false;
			for(size_t i=0;i<100 && !fnd;++i)
			{
				if(dat[i]==*it)
				{
					fnd=true;
					found[i]=true;
				}
			}
		}
		for(size_t i=0;i<100;i++)
		{
			if(!found[i])
				throwGeneralTestException("Inserted element "+std::to_string(dat[i])+" @ "+std::to_string(i)+" not found",locString);
		}
	}
	
	template<class datastruct>
	void autoIteratorNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, randomIteratorNodeTest<"+className+">()";
		datastruct ds;
		dummyInt dat[100];
		bool found[100];
		memset(found,0,100*sizeof(bool));
		srand((unsigned)time(NULL));

		for(size_t i=0;i<100;++i)
		{
			dummyInt temp=rand()%1000;
			bool tfnd=false;
			for(size_t cnt=0;cnt<i && !tfnd;++cnt)
			{
				if(dat[cnt]==temp) tfnd=true;
			}
			if(tfnd) --i;
			else dat[i]=temp;
		}

		for(size_t i=0;i<100;++i)
			ds.insert(dat[i]);
		
		for(auto it : ds)
		{
			bool fnd=false;
			for(size_t i=0;i<100 && !fnd;++i)
			{
				if(dat[i]==it)
				{
					fnd=true;
					found[i]=true;
				}
			}
		}
		for(size_t i=0;i<100;i++)
		{
			if(!found[i])
				throwGeneralTestException("Inserted element "+std::to_string(dat[i])+" @ "+std::to_string(i)+" not found",locString);
		}
	}
	template<class datastruct>
	void autoIteratorPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, randomIteratorPointerTest<"+className+">()";
		datastruct ds;
		dummyInt dat[100];
		bool found[100];
		memset(found,0,100*sizeof(bool));
		srand((unsigned)time(NULL));

		for(size_t i=0;i<100;++i)
		{
			dummyInt temp=rand()%1000;
			bool tfnd=false;
			for(size_t cnt=0;cnt<i && !tfnd;++cnt)
			{
				if(dat[cnt]==temp) tfnd=true;
			}
			if(tfnd) --i;
			else dat[i]=temp;
		}

		for(size_t i=0;i<100;++i)
			ds.insert(os::smart_ptr<dummyInt>(new dummyInt(dat[i]),os::shared_type));
		
		for(auto it : ds)
		{
			bool fnd=false;
			for(size_t i=0;i<100 && !fnd;++i)
			{
				if(dat[i]==it)
				{
					fnd=true;
					found[i]=true;
				}
			}
		}
		for(size_t i=0;i<100;i++)
		{
			if(!found[i])
				throwGeneralTestException("Inserted element "+std::to_string(dat[i])+" @ "+std::to_string(i)+" not found",locString);
		}
	}
	
	template<class datastruct>
	void randomSortedNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, randomSortedNodeTest<"+className+">()";
		datastruct ds;
		dummyInt dat[100];
		srand((unsigned)time(NULL));

		for(size_t i=0;i<100;++i)
		{
			dummyInt temp=rand()%1000;
			bool tfnd=false;
			for(size_t cnt=0;cnt+1<i && !tfnd;++cnt)
			{
				if(dat[cnt]==temp) tfnd=true;
			}
			if(tfnd) --i;
			else dat[i]=temp;
		}

		for(size_t i=0;i<100;++i)
			ds.insert(dat[i]);

		os::iterator<dummyInt> it1=ds.first();
		os::iterator<dummyInt> it2;
		while(it1)
		{
			if(it2 && it2>it1)
				throwGeneralTestException("Datastructure unsorted",locString);
			it2=it1;
			++it1;
		}

		for(size_t i=0;i<10;++i)
		{
			if(ds.find(dat[i]))
			{
				size_t sz=ds.size();
				if(!ds.remove(dat[i]))
                    throwGeneralTestException("Remove call failed",locString);
                if(ds.find(dat[i]))
                    throwGeneralTestException("Found removed object",locString);
				if(ds.size()==sz)
					throwGeneralTestException("Failed to remove an object",locString);
			}
		}
	}
	template<class datastruct>
	void randomSortedPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, randomSortedPointerTest<"+className+">()";
		datastruct ds;
		os::smart_ptr<dummyInt> dat[100];
		srand((unsigned)time(NULL));

		for(size_t i=0;i<100;++i)
		{
			dummyInt temp=rand()%1000;
			bool tfnd=false;
			for(size_t cnt=0;cnt+1<i && !tfnd;++cnt)
			{
				if(*dat[cnt]==temp) tfnd=true;
			}
			if(tfnd) --i;
			else dat[i]=os::smart_ptr<dummyInt>(new dummyInt(temp),os::shared_type);
		}

		for(size_t i=0;i<100;++i)
			ds.insert(dat[i]);

		os::iterator<dummyInt> it1=ds.first();
		os::iterator<dummyInt> it2;
		while(it1)
		{
			if(it2 && it2>it1)
				throwGeneralTestException("Datastructure unsorted",locString);
			it2=it1;
			++it1;
		}

		for(size_t i=0;i<10;++i)
		{
			if(ds.find(dat[i]))
			{
				size_t sz=ds.size();
                if(!ds.remove(dat[i]))
                    throwGeneralTestException("Remove call failed",locString);
                if(ds.find(dat[i]))
                    throwGeneralTestException("Found removed object",locString);
                if(ds.size()==sz)
                    throwGeneralTestException("Failed to remove an object",locString);
			}
		}
	}
	template<class datastruct>
	void wholeInsertionNodeTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, wholeInsertionNodeTest<"+className+">()";
		datastruct ds1;
		datastruct ds2;

		ds1.insert(1);
		ds1.insert(4);
		ds1.insert(6);

		ds2.insert(3);
		ds2.insert(8);
		ds2.insert(9);

		if(ds1.find(3))
			throwGeneralTestException("Unexpectadly found 3",locString);
		ds1.insertStructure(ds2);
		if(!ds1.find(3))
			throwGeneralTestException("Could not find 3",locString);
	}
	template<class datastruct>
	void wholeInsertionPointerTest(std::string className)
	{
		std::string locString = "DatastructuresTest.cpp, wholeInsertionPointerTest<"+className+">()";
		datastruct ds1;
		datastruct ds2;
		os::smart_ptr<dummyInt> i3(new dummyInt(3),os::shared_type);

		ds1.insert(os::smart_ptr<dummyInt>(new dummyInt(1),os::shared_type));
		ds1.insert(os::smart_ptr<dummyInt>(new dummyInt(4),os::shared_type));
		ds1.insert(os::smart_ptr<dummyInt>(new dummyInt(6),os::shared_type));

		ds2.insert(i3);
		ds2.insert(os::smart_ptr<dummyInt>(new dummyInt(8),os::shared_type));
		ds2.insert(os::smart_ptr<dummyInt>(new dummyInt(9),os::shared_type));

		if(ds1.find(i3))
			throwGeneralTestException("Unexpectadly found 3",locString);
		ds1.insertStructure(ds2);
		if(!ds1.find(i3))
			throwGeneralTestException("Could not find 3",locString);
	}

	//Random access tests
    template<class datastruct>
    void noRandomAccessObjectTest(std::string className)
    {
        std::string locString = "DatastructuresTest.cpp, noRandomAccessObjectTest<"+className+">()";
        datastruct ds;
        ds.insert(1);
        
        bool thrown=false;
        try{ds[0];}
        catch(descriptiveException de){thrown=true;}
        if(!thrown)
            throwGeneralTestException("Expected access to throw exception",locString);
        thrown=false;
        
        ds.insert(2);
        ds.insert(3);

		if(datastruct::ITERABLE)
		{
			os::iterator<dummyInt> it=ds.first();
			if(it+1!=++it)
				throwGeneralTestException("Basic increment failed",locString);

			try{it+=2;}
			catch(descriptiveException de){thrown=true;}
			if(!thrown)
				throwGeneralTestException("Expected double increment to fail",locString);

			it=ds.last();
			if(it-1!=--it)
				throwGeneralTestException("Basic decrement failed",locString);

			try{it-=2;}
			catch(descriptiveException de){thrown=true;}
			if(!thrown)
				throwGeneralTestException("Expected double decrement to fail",locString);
		}
    }
    template<class datastruct>
    void noRandomAccessPointerTest(std::string className)
    {
        std::string locString = "DatastructuresTest.cpp, noRandomAccessPointerTest<"+className+">()";
        datastruct ds;
        ds.insert(os::smart_ptr<dummyInt>(new dummyInt(1),os::shared_type));
        
        bool thrown=false;
        try{ds[0];}
        catch(descriptiveException de){thrown=true;}
        if(!thrown)
            throwGeneralTestException("Expected access to throw exception",locString);
        thrown=false;
        
        ds.insert(os::smart_ptr<dummyInt>(new dummyInt(2),os::shared_type));
        ds.insert(os::smart_ptr<dummyInt>(new dummyInt(3),os::shared_type));

		if(datastruct::ITERABLE)
		{
			os::iterator<dummyInt> it=ds.first();
			if(it+1!=++it)
				throwGeneralTestException("Basic increment failed",locString);

			try{it+=2;}
			catch(descriptiveException de){thrown=true;}
			if(!thrown)
				throwGeneralTestException("Expected double increment to fail",locString);

			it=ds.last();
			if(it-1!=--it)
				throwGeneralTestException("Basic decrement failed",locString);

			try{it-=2;}
			catch(descriptiveException de){thrown=true;}
			if(!thrown)
				throwGeneralTestException("Expected double decrement to fail",locString);
		}
    }
    template<class datastruct>
    void basicRandomAccessObjectTest(std::string className)
    {
        std::string locString = "DatastructuresTest.cpp, basicRandomAccessObjectTest<"+className+">()";
        datastruct ds;
		 srand((unsigned)time(NULL));
        bool thrown=false;
        try{ds[0];}
        catch(descriptiveException de){thrown = true;}
        if(!thrown)
            throwGeneralTestException("Expected out of bounds access to throw exception",locString);
        
        for(int i=0;i<100;++i)
            ds.insert(i);
        dummyInt d;

        for(size_t i=0;i<10;++i)
        {
            size_t r=rand()%98+1;
            d=ds[r];
            if(d!=ds[r])
                throwGeneralTestException("Random access failed",locString);
            if(d==ds[r-1])
                throwGeneralTestException("- 1 random access failed",locString);
            if(d==ds[r+1])
                throwGeneralTestException("+ 1 random access failed",locString);
        }
    }
    template<class datastruct>
    void basicRandomAccessPointerTest(std::string className)
    {
        std::string locString = "DatastructuresTest.cpp, basicRandomAccessPointerTest<"+className+">()";
        datastruct ds;
        srand((unsigned)time(NULL));
        bool thrown=false;
        try{ds[0];}
        catch(descriptiveException de){thrown = true;}
        if(!thrown)
            throwGeneralTestException("Expected out of bounds access to throw exception",locString);
    
        for(int i=0;i<100;++i)
            ds.insert(os::smart_ptr<dummyInt>(new dummyInt(i),os::shared_type));
        os::smart_ptr<dummyInt> d;
    
        for(size_t i=0;i<10;++i)
        {
            size_t r=rand()%98+1;
            d=ds[r];
            if(!d || !ds[r] || *d!=*ds[r])
                throwGeneralTestException("Random access failed",locString);
            if(*d==*ds[r-1])
                throwGeneralTestException("- 1 random access failed",locString);
            if(*d==*ds[r+1])
                throwGeneralTestException("+ 1 random access failed",locString);
        }
    }
	template<class datastruct>
    void iteratorRandomAccessObjectTest(std::string className)
    {
        std::string locString = "DatastructuresTest.cpp, iteratorRandomAccessObjectTest<"+className+">()";
        datastruct ds;
		srand((unsigned)time(NULL));
        bool thrown=false;
        try{ds[0];}
        catch(descriptiveException de){thrown = true;}
        if(!thrown)
            throwGeneralTestException("Expected out of bounds access to throw exception",locString);
        
        for(int i=0;i<100;++i)
            ds.insert(i);
        dummyInt d;
        
        for(size_t i=0;i<10;++i)
        {
            size_t r=rand()%98+1;
            d=ds[r];
            os::iterator<dummyInt> it=ds.first();
			if(*(it+r)!=d)
				throwGeneralTestException("Iterator increasing random-access failed",locString);
			it=ds.last();
			if(*(it-(99-r))!=d)
				throwGeneralTestException("Iterator decreasing random-access failed",locString);
        }
		if(ds.last()+2)
			throwGeneralTestException("Expected out of bounds (high)",locString);
		if(ds.first()-2)
			throwGeneralTestException("Expected out of bounds (low)",locString);
    }
    template<class datastruct>
    void iteratorRandomAccessPointerTest(std::string className)
    {
        std::string locString = "DatastructuresTest.cpp, iteratorRandomAccessPointerTest<"+className+">()";
        datastruct ds;
		srand((unsigned)time(NULL));
        bool thrown=false;
        try{ds[0];}
        catch(descriptiveException){thrown = true;}
        if(!thrown)
            throwGeneralTestException("Expected out of bounds access to throw exception",locString);
        
        for(int i=0;i<100;++i)
			ds.insert(os::smart_ptr<dummyInt>(new dummyInt(i),os::shared_type));
        os::smart_ptr<dummyInt> d;
        
        for(size_t i=0;i<10;++i)
        {
            size_t r=rand()%98+1;
            d=ds[r];
			os::iterator<dummyInt> it=ds.first();
			if(&(it+r)!=d)
				throwGeneralTestException("Iterator increasing random-access failed",locString);
			it=ds.last();
			if(&(it-(99-r))!=d)
				throwGeneralTestException("Iterator decreasing random-access failed",locString);
        }
		if(ds.last()+2)
			throwGeneralTestException("Expected out of bounds (high)",locString);
		if(ds.first()-2)
			throwGeneralTestException("Expected out of bounds (low)",locString);
    }
	
	//Testing structure
	typedef void (*datastructureTestFunction)(std::string cname);

	class datastructureTest: public singleTest
	{
		std::string className;
		datastructureTestFunction func;
	public:
		datastructureTest(std::string tn, std::string cname="NULL", datastructureTestFunction testfunc=NULL):
			singleTest(tn)
		{
			className=cname;
			func=testfunc;
		}
		virtual ~datastructureTest(){}
        
		//Run the specified test function
		void test() 
		{
			if(func!=NULL) func(className);
			else throw os::errorPointer(new nullFunctionException("DatastructuresTest.cpp, datastructureTest::test()"),shared_type);
		}
	};
	
	template <class datastruct>
	class datastructureNodeSuite: public testSuite
	{
	public:
		datastructureNodeSuite(string className, bool sorted=false):
			testSuite(className)
		{
			pushTest(smart_ptr<singleTest>(new datastructureTest("Single Insertion",className,&singleInsertionNodeTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Single Deletion",className,&singleDeletionNodeTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Iterator Deletion",className,&iteratorDeletionNodeTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Iterator Instantiation",className,&simpleIteratorNodeTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Search Node",className,&searchNodeTest<datastruct>),shared_type));
			
			//Iterable tests
			if(datastruct::ITERABLE)
			{
				pushTest(smart_ptr<singleTest>(new datastructureTest("Copy",className,&copyStructTest<datastruct>),shared_type));
				pushTest(smart_ptr<singleTest>(new datastructureTest("Basic Iteration",className,&basicIteratorNodeTest<datastruct>),shared_type));
				pushTest(smart_ptr<singleTest>(new datastructureTest("Random Iteration",className,&randomIteratorNodeTest<datastruct>),shared_type));
				pushTest(smart_ptr<singleTest>(new datastructureTest("Auto Iteration",className,&autoIteratorNodeTest<datastruct>),shared_type));
				pushTest(smart_ptr<singleTest>(new datastructureTest("Whole Insertion",className,&wholeInsertionNodeTest<datastruct>),shared_type));
				if(sorted) pushTest(smart_ptr<singleTest>(new datastructureTest("Sorted",className,&randomSortedNodeTest<datastruct>),shared_type));
			}
			else pushTest(smart_ptr<singleTest>(new datastructureTest("No Iteration",className,&noIteratorNodeTest<datastruct>),shared_type));

            //Random access
            if(datastruct::RANDOM_ACCESS)
            {
                pushTest(smart_ptr<singleTest>(new datastructureTest("Basic Random Access",className,&basicRandomAccessObjectTest<datastruct>),shared_type));
                pushTest(smart_ptr<singleTest>(new datastructureTest("Iterator Random Access",className,&iteratorRandomAccessObjectTest<datastruct>),shared_type));
            }
			else pushTest(smart_ptr<singleTest>(new datastructureTest("No Random Access",className,&noRandomAccessObjectTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Custom Test",className,&customADSTest<datastruct>),shared_type));
		}
		virtual ~datastructureNodeSuite(){}
	};
	template <class datastruct>
	class datastructurePointerSuite: public testSuite
	{
	public:
		datastructurePointerSuite(string className, bool sorted=false):
			testSuite(className)
		{
			pushTest(smart_ptr<singleTest>(new datastructureTest("Single Insertion",className,&singleInsertionPointerTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Single Deletion",className,&singleDeletionPointerTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Iterator Deletion",className,&iteratorDeletionPointerTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Iterator Instantiation",className,&simpleIteratorPointerTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Search Node",className,&searchPointerTest<datastruct>),shared_type));

			//Iterable tests
			if(datastruct::ITERABLE)
			{
				pushTest(smart_ptr<singleTest>(new datastructureTest("Copy",className,&copyStructPointerTest<datastruct>),shared_type));
				pushTest(smart_ptr<singleTest>(new datastructureTest("Basic Iteration",className,&basicIteratorPointerTest<datastruct>),shared_type));
				pushTest(smart_ptr<singleTest>(new datastructureTest("Random Iteration",className,&randomIteratorPointerTest<datastruct>),shared_type));
				pushTest(smart_ptr<singleTest>(new datastructureTest("Auto Iteration",className,&autoIteratorPointerTest<datastruct>),shared_type));
				pushTest(smart_ptr<singleTest>(new datastructureTest("Whole Insertion",className,&wholeInsertionPointerTest<datastruct>),shared_type));
				if(sorted) pushTest(smart_ptr<singleTest>(new datastructureTest("Sorted",className,&randomSortedPointerTest<datastruct>),shared_type));
			}
			else pushTest(smart_ptr<singleTest>(new datastructureTest("No Iteration",className,&noIteratorPointerTest<datastruct>),shared_type));
            
            //Random access
            if(datastruct::RANDOM_ACCESS)
            {
                pushTest(smart_ptr<singleTest>(new datastructureTest("Basic Random Access",className,&basicRandomAccessPointerTest<datastruct>),shared_type));
                pushTest(smart_ptr<singleTest>(new datastructureTest("Iterator Random Access",className,&iteratorRandomAccessPointerTest<datastruct>),shared_type));
            }
			else pushTest(smart_ptr<singleTest>(new datastructureTest("No Random Access",className,&noRandomAccessPointerTest<datastruct>),shared_type));
			pushTest(smart_ptr<singleTest>(new datastructureTest("Custom Test",className,&customADSTest<datastruct>),shared_type));
		}
		virtual ~datastructurePointerSuite(){}
	};

/*================================================================
	MatrixTest
 ================================================================*/

    //Array access test
    void matrixArrayAccessTest()
    {
        std::string locString = "DatastructuresTest.cpp, matrixArrayAccessTest()";
        
        matrix<int>mat1(4,4);
        matrix<int>mat2(4,4);
        matrix<int>mat3(mat1);
        int compArray[16];
        
        //Check size
        if(mat1.width()!=4 || mat2.width()!=4 || mat3.width()!=4) throwGeneralTestException("Matrix width failure",locString);
        if(mat1.height()!=4 || mat2.height()!=4 || mat3.height()!=4) throwGeneralTestException("Matrix height failure",locString);
        
        //Random init
        srand((unsigned)time(NULL));
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
        for(int i = 0;i<16;++i)
        {
            if(compArray[i] != mat1.getArray()[i])
                throwGeneralTestException("Matrix init failed",locString);
        }
        
        //Compare mat1 and mat2 (raw array)
        for(int i = 0;i<16;++i)
        {
            if(mat1.getArray()[i] != mat2.getArray()[i])
            throwGeneralTestException("Matrix direct compare failed",locString);
        }
        
        //Compare mat1 and mat3 (raw array)
        for(int i = 0;i<16;++i)
        {
            if(mat2.getArray()[i] != mat3.getArray()[i])
            throwGeneralTestException("Matrix copy compare failed",locString);
        }
    }
    //Equality test
    void matrixEqualityTest()
    {
        std::string locString = "DatastructuresTest.cpp, matrixEqualityTest()";
        matrix<int>mat1(4,4);
        matrix<int>mat2(4,4);
        matrix<int>mat3(4,4);
        matrix<int>mat4(mat1);
        int compArray[16];
        
        //Random init
        srand((unsigned)time(NULL));
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
        throwGeneralTestException("Equals failed (same init)",locString);
        if(mat1!=mat2)
        throwGeneralTestException("Not equals failed (same init)",locString);
        
        //Compare mat2 and 4
        if(!(mat2==mat4))
        throwGeneralTestException("Equals failed (copy constructor)",locString);
        if(mat2!=mat4)
        throwGeneralTestException("Not equals failed (copy constructor)",locString);
        
        //Compare mat1 and 3
        if(mat1==mat3)
        throwGeneralTestException("Equals failed (different mats)",locString);
        if(!(mat1!=mat3))
        throwGeneralTestException("Not equals failed (different mats)",locString);
    }
    //Addition test
    void matrixAdditionTest()
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
        throwGeneralTestException("Addition failed!",locString);
        out = mat2+mat1;
        if(out!=ans)
        throwGeneralTestException("Addition transitivity failed!",locString);
    }
    //Subtraction test
    static void matrixSubtractionTest()
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
        throwGeneralTestException("Subtraction failed!",locString);
        out = mat1-mat2;
        if(out==ans)
        throwGeneralTestException("Subtraction not respecting order!",locString);
    }
    //Dot product test
    void matrixDotProductTest()
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
        throwGeneralTestException("Dot Product failed!",locString);
        out = mat2*mat1;
        if(out==ans)
        throwGeneralTestException("Dot Product not respecting order!",locString);
    }
    //Advanced construction test
    void matrixAdvancedConstructionTest()
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedConstructionTest()";
        
        //Preform this test 10 times
        srand((unsigned)time(NULL));
        for(int i=0;i<10;++i)
        {
            matrix<int> mast1(10,10);
            matrix<int> cop1;
            matrix<int> bridge1;
            indirectMatrix<int> mast2(10,10);
            indirectMatrix<int> cop2;
            indirectMatrix<int> bridge2;
            int compsrc[100];
            
            for(int i=0;i<100;++i)
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
            for(int i=0;i<100;++i)
            {
                if(mast1.getArray()[i]!=compsrc[i])
                    throwGeneralTestException("Matrix init failed (direct matrix)",locString);
                if(*(mast2.getArray()[i])!=compsrc[i])
                    throwGeneralTestException("Matrix init failed (indirect matrix)",locString);
                
                if(cop1.getArray()[i]!=compsrc[i])
                    throwGeneralTestException("Matrix standard equals failed (direct matrix)",locString);
                if(*(cop2.getArray()[i])!=compsrc[i])
                    throwGeneralTestException("Matrix standard equals failed (indirect matrix)",locString);
                
                if(bridge1.getArray()[i]!=compsrc[i])
                    throwGeneralTestException("Matrix bridge equals failed (direct matrix)",locString);
                if(*(bridge2.getArray()[i])!=compsrc[i])
                    throwGeneralTestException("Matrix bridge equals failed (indirect matrix)",locString);
            }
        }
    }
    //Advanced equality test
    void matrixAdvancedEqualityTest()
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedEqualityTest()";
        
        //Preform this test 10 times
        srand((unsigned)time(NULL));
        for(int i=0;i<10;++i)
        {
            matrix<int> mast1(10,10);
            matrix<int> wrong1(10,10);
            matrix<int> cop1;
            indirectMatrix<int> mast2(10,10);
            indirectMatrix<int> wrong2(10,10);
            indirectMatrix<int> cop2;
            int compsrc[100];
            
            for(int i=0;i<100;++i)
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
            if(!(mast1==cop1)) throwGeneralTestException("S-S equals failed",locString);
            if(!(cop1==mast1)) throwGeneralTestException("Transitive S-S equals failed",locString);
            if(mast1!=cop1) throwGeneralTestException("S-S not equals failed",locString);
            if(cop1!=mast1) throwGeneralTestException("Transitive S-S not equals failed",locString);
            
            //Indirect to indirect
            if(!(mast2==cop2)) throwGeneralTestException("I-I equals failed",locString);
            if(!(cop2==mast2)) throwGeneralTestException("Transitive I-I equals failed",locString);
            if(mast2!=cop2) throwGeneralTestException("I-I not equals failed",locString);
            if(cop2!=mast2) throwGeneralTestException("Transitive I-I not equals failed",locString);
            
            //Standard to indirect
            if(!(mast1==cop2)) throwGeneralTestException("S-I equals failed",locString);
            if(!(cop1==mast2)) throwGeneralTestException("Transitive S-I equals failed",locString);
            if(mast1!=cop2) throwGeneralTestException("S-I not equals failed",locString);
            if(cop1!=mast2) throwGeneralTestException("Transitive S-I not equals failed",locString);
            
            //Indirect to standard
            if(!(mast2==cop1)) throwGeneralTestException("I-S equals failed",locString);
            if(!(cop2==mast1)) throwGeneralTestException("Transitive I-S equals failed",locString);
            if(mast2!=cop1) throwGeneralTestException("I-S not equals failed",locString);
            if(cop2!=mast1) throwGeneralTestException("Transitive I-S not equals failed",locString);
        }
    }
    //Advanced addition test
    void matrixAdvancedAdditionTest()
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedAdditionTest()";
        
        //Preform this test 10 times
        srand((unsigned)time(NULL));
        for(int i=0;i<10;++i)
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
            if(imat1+imat2 != smat1+smat2) throwGeneralTestException("Addition failed: i1+i2 != s1+s2",locString);
            if(imat2+imat1 != smat2+smat1) throwGeneralTestException("Addition failed: i2+i1 != s2+s1",locString);
            if(imat1+smat2 != smat1+smat2) throwGeneralTestException("Addition failed: i1+s2 != s1+s2",locString);
            if(imat2+smat1 != smat2+smat1) throwGeneralTestException("Addition failed: i2+s1 != s2+s1",locString);
            if(smat1+imat2 != smat1+smat2) throwGeneralTestException("Addition failed: s1+i2 != s1+s2",locString);
            if(smat2+imat1 != smat2+smat1) throwGeneralTestException("Addition failed: s2+i1 != s2+s1",locString);
            
            //Transitive tests
            if(imat1+imat2 != smat2+smat1) throwGeneralTestException("Addition failed: i1+i2 != s2+s1",locString);
            if(imat2+imat1 != smat1+smat2) throwGeneralTestException("Addition failed: i2+i1 != s1+s2",locString);
            if(imat1+smat2 != smat2+smat1) throwGeneralTestException("Addition failed: i1+s2 != s2+s1",locString);
            if(imat2+smat1 != smat1+smat2) throwGeneralTestException("Addition failed: i2+s1 != s1+s2",locString);
            if(smat1+imat2 != smat2+smat1) throwGeneralTestException("Addition failed: s1+i2 != s2+s1",locString);
            if(smat2+imat1 != smat1+smat2) throwGeneralTestException("Addition failed: s2+i1 != s1+s2",locString);
        }
    }
    //Advanced subtraction test
    void matrixAdvancedSubtractionTest()
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedSubtractionTest()";
        
        //Preform this test 10 times
        srand((unsigned)time(NULL));
        for(int i=0;i<10;++i)
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
            if(imat1-imat2 != smat1-smat2) throwGeneralTestException("Subtraction failed: i1-i2 != s1-s2",locString);
            if(imat2-imat1 != smat2-smat1) throwGeneralTestException("Subtraction failed: i2-i1 != s2-s1",locString);
            if(imat1-smat2 != smat1-smat2) throwGeneralTestException("Subtraction failed: i1-s2 != s1-s2",locString);
            if(imat2-smat1 != smat2-smat1) throwGeneralTestException("Subtraction failed: i2-s1 != s2-s1",locString);
            if(smat1-imat2 != smat1-smat2) throwGeneralTestException("Subtraction failed: s1-i2 != s1-s2",locString);
            if(smat2-imat1 != smat2-smat1) throwGeneralTestException("Subtraction failed: s2-i1 != s2-s1",locString);
        }
    }
    //Advanced dot product test
    void matrixAdvancedDotProductTest()
    {
        std::string locString = "DatastructuresTest.cpp, matrixAdvancedDotProductTest()";
        
        //Preform this test 10 times
        srand((unsigned)time(NULL));
        for(int i=0;i<10;++i)
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
            if(imat1*imat2 != smat1*smat2) throwGeneralTestException("Dot Product failed: i1*i2 != s1*s2",locString);
            if(imat2*imat1 != smat2*smat1) throwGeneralTestException("Dot Product failed: i2*i1 != s2*s1",locString);
            if(imat1*smat2 != smat1*smat2) throwGeneralTestException("Dot Product failed: i1*s2 != s1*s2",locString);
            if(imat2*smat1 != smat2*smat1) throwGeneralTestException("Dot Product failed: i2*s1 != s2*s1",locString);
            if(smat1*imat2 != smat1*smat2) throwGeneralTestException("Dot Product failed: s1*i2 != s1*s2",locString);
            if(smat2*imat1 != smat2*smat1) throwGeneralTestException("Dot Product failed: s2*i1 != s2*s1",locString);
        }
    }

/*================================================================
	Vector Tests
 ================================================================*/

	//Tests the copy constructor and equality constructor
    void vector2dConstructorTest()
	{
		std::string locString = "DatastructuresTest.cpp, vector2dConstructorTest()";
		vector2d_d v1;
		
		//Test default init values
		if(v1.x!=0 || v1.y!=0)
			throwGeneralTestException("Vector default init failed",locString);

		//Tests the value init
		vector2d_d v2(.5,1.5);
		if(v2.x!=.5 || v2.y!=1.5)
			throwGeneralTestException("Vector init failed",locString);

		//Tests the copy constructor
		vector2d_d v3(v2);
		if(v3.x!=.5 || v3.y!=1.5)
			throwGeneralTestException("Vector copy init failed",locString);
		v1=v3;
		if(v1.x!=.5 || v1.y!=1.5)
			throwGeneralTestException("Vector copy init failed",locString);
	}
    void vector3dConstructorTest()
	{
		std::string locString = "DatastructuresTest.cpp, vector3dConstructorTest()";
		vector3d_d v1;
		
		//Test default init values
		if(v1.x!=0 || v1.y!=0 || v1.z!=0)
			throwGeneralTestException("Vector default init failed",locString);

		//Tests the value init
		vector3d_d v2(.5,1.5,2.5);
		if(v2.x!=.5 || v2.y!=1.5 || v2.z!=2.5)
			throwGeneralTestException("Vector init failed",locString);

		//Tests the copy constructor
		vector3d_d v3(v2);
		if(v3.x!=.5 || v3.y!=1.5 || v3.z!=2.5)
			throwGeneralTestException("Vector copy init failed",locString);
		v1=v3;
		if(v1.x!=.5 || v1.y!=1.5 || v1.z!=2.5)
			throwGeneralTestException("Vector equals init failed",locString);

		//Tests the 2d constructor
		vector2d_d t(1,2);
		vector3d_d v4(t);
		if(v4.x!=1 || v4.y!=2 || v4.z !=0)
			throwGeneralTestException("Vector 2d init failed",locString);
	}
	//Tests equality functions
    void vector2dEqualityTest() 
	{
		std::string locString = "DatastructuresTest.cpp, vector2dEqualityTest()";

		for(int i=0;i<30;++i)
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
				throwGeneralTestException("Compare failed.  Cycle: "+to_string((long long unsigned)i),locString);
			
			//Test all cases
			if(v!=0 && v1==v2) throwGeneralTestException("< failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v==0 && v1!=v2) throwGeneralTestException("<= failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v!=-1 && v1<v2) throwGeneralTestException("< failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v==1 && v1<=v2) throwGeneralTestException("<= failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v!=1 && v1>v2) throwGeneralTestException("> failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v==-1 && v1>=v2) throwGeneralTestException(">= failed.  Cycle: "+to_string((long long unsigned)i),locString);
		}
	}
    void vector3dEqualityTest() 
	{
		std::string locString = "DatastructuresTest.cpp, vector3dEqualityTest()";

		for(int i=0;i<30;++i)
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
				throwGeneralTestException("Compare failed.  Cycle: "+to_string((long long unsigned)i),locString);
			
			//Test all cases
			if(v!=0 && v1==v2) throwGeneralTestException("< failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v==0 && v1!=v2) throwGeneralTestException("<= failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v!=-1 && v1<v2) throwGeneralTestException("< failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v==1 && v1<=v2) throwGeneralTestException("<= failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v!=1 && v1>v2) throwGeneralTestException("> failed.  Cycle: "+to_string((long long unsigned)i),locString);
			if(v==-1 && v1>=v2) throwGeneralTestException(">= failed.  Cycle: "+to_string((long long unsigned)i),locString);
		}
	}
	//Addition
    void vector2dAdditionTest() 
	{
		std::string locString = "DatastructuresTest.cpp, vector2dAdditionTest()";

		//Simple addition
		vector2d_d v1(3,9);
		vector2d_d v2(7,2);
		vector2d_d ans(10,11);

		if(v1.add(v2)!=ans)
			throwGeneralTestException("Simple addition failed",locString);
		if(v1+v2!=ans)
			throwGeneralTestException("Simple + failed",locString);
		if(v2+v1!=ans)
			throwGeneralTestException("+ reverse failed",locString);
		if((v1+=v2)!=ans)
			throwGeneralTestException("Simple += failed",locString);
		if(v1!=ans)
			throwGeneralTestException("+= after failed",locString);

		//Increment and decrement
		vector2d_d raw(0,1);
		++raw;
		if(raw.x!=0 && raw.y!=2)
			throwGeneralTestException("Simple increment failed",locString);
		++raw;
		if(raw.x!=0 && raw.y!=3)
			throwGeneralTestException("Simple increment (2) failed",locString);
		
		raw=vector2d_d(3,4);
		if(5.1<raw.length() || raw.length()<4.9)
			throwGeneralTestException("Length failed",locString);
		++raw;
		if(6.1<raw.length() || raw.length()<5.9)
			throwGeneralTestException("Complex increment failed",locString);
		++raw;
		if(7.1<raw.length() || raw.length()<6.9)
			throwGeneralTestException("Complex increment (2) failed",locString);
	}
    void vector3dAdditionTest() 
	{
		std::string locString = "DatastructuresTest.cpp, vector3dAdditionTest()";

		//Simple addition
		vector3d_d v1(3,9,4);
		vector3d_d v2(7,2,1);
		vector3d_d ans(10,11,5);

		if(v1.add(v2)!=ans)
			throwGeneralTestException("Simple addition failed",locString);
		if(v1+v2!=ans)
			throwGeneralTestException("Simple + failed",locString);
		if(v2+v1!=ans)
			throwGeneralTestException("+ reverse failed",locString);
		if((v1+=v2)!=ans)
			throwGeneralTestException("Simple += failed",locString);
		if(v1!=ans)
			throwGeneralTestException("+= after failed",locString);

		//Increment and decrement
		vector3d_d raw(0,1,0);
		++raw;
		if(raw.x!=0 || raw.y!=2 || raw.z!=0)
			throwGeneralTestException("Simple increment failed",locString);
		++raw;
		if(raw.x!=0 || raw.y!=3 || raw.z!=0)
			throwGeneralTestException("Simple increment (2) failed",locString);
		
		raw=vector3d_d(1,1,1);
		if(raw.length()!=sqrt(3))
			throwGeneralTestException("Length failed",locString);
		++raw;

		if(raw.length() < sqrt(3)+.9 || raw.length() > sqrt(3)+1.1)
			throwGeneralTestException("Complex increment failed",locString);
		++raw;
		if(raw.length() < sqrt(3)+1.9 || raw.length() > sqrt(3)+2.1)
			throwGeneralTestException("Complex increment (2) failed",locString);
	}
	//Subtraction
    void vector2dSubtractionTest() 
	{
		std::string locString = "DatastructuresTest.cpp, vector2dSubtractionTest()";

		//Simple addition
		vector2d_d v1(3,9);
		vector2d_d v2(7,2);
		vector2d_d ans(-4,7);

		if(v1.subtract(v2)!=ans)
			throwGeneralTestException("Simple subtract failed",locString);
		if(v1-v2!=ans)
			throwGeneralTestException("Simple - failed",locString);
		if((v2-v1) != (-ans))
			throwGeneralTestException("- reverse failed",locString);
		if((v1-=v2)!=ans)
			throwGeneralTestException("Simple -= failed",locString);
		if(v1!=ans)
			throwGeneralTestException("-= after failed",locString);

		//Increment and decrement
		vector2d_d raw(0,5);
		--raw;
		if(raw.x!=0 && raw.y!=4)
			throwGeneralTestException("Simple decrement failed",locString);
		--raw;
		if(raw.x!=0 && raw.y!=3)
			throwGeneralTestException("Simple decrement (2) failed",locString);
		
		raw=vector2d_d(3,4);
		if(5.1<raw.length() || raw.length()<4.9)
			throwGeneralTestException("Length failed",locString);
		--raw;
		if(4.1<raw.length() || raw.length()<3.9)
			throwGeneralTestException("Complex decrement failed",locString);
		--raw;
		if(3.1<raw.length() || raw.length()<2.9)
			throwGeneralTestException("Complex decrement (2) failed",locString);
	}
    void vector3dSubtractionTest() 
	{
		std::string locString = "DatastructuresTest.cpp, vector3dSubtractionTest()";

		//Simple addition
		vector3d_d v1(3,9,4);
		vector3d_d v2(7,2,1);
		vector3d_d ans(-4,7,3);

		if(v1.subtract(v2)!=ans)
			throwGeneralTestException("Simple subtraction failed",locString);
		if(v1-v2!=ans)
			throwGeneralTestException("Simple - failed",locString);
		if((v2-v1)!=(-ans))
			throwGeneralTestException("- reverse failed",locString);
		if((v1-=v2)!=ans)
			throwGeneralTestException("Simple -= failed",locString);
		if(v1!=ans)
			throwGeneralTestException("-= after failed",locString);

		//Increment and decrement
		vector3d_d raw(0,5,0);
		--raw;
		if(raw.x!=0 || raw.y!=4 || raw.z!=0)
			throwGeneralTestException("Simple increment failed",locString);
		--raw;
		if(raw.x!=0 || raw.y!=3 || raw.z!=0)
			throwGeneralTestException("Simple increment (2) failed",locString);
		
		raw=vector3d_d(4,4,4);
		if(raw.length()!=sqrt(3*16))
			throwGeneralTestException("Length failed",locString);
		--raw;

		if(raw.length() > sqrt(3*16)-.9 || raw.length() < sqrt(3*16)-1.1)
			throwGeneralTestException("Complex decrement failed",locString);
		--raw;
		if(raw.length() > sqrt(3*16)-1.9 || raw.length() < sqrt(3*16)-2.1)
			throwGeneralTestException("Complex decrement (2) failed",locString);
	}
	//Dot product
    void vector2dDotProductTest() 
	{
		std::string locString = "DatastructuresTest.cpp, vector2dDotProductTest()";
		vector2d_d v1(4,8);
		vector2d_d v2(-3,10);

		if(v1.dotProduct(v2)!=68)
			throwGeneralTestException("Initial dot-product failed!",locString);
		v1(0,1);
		v2(1,0);
		if(v1.dotProduct(v2)!=0)
			throwGeneralTestException("Dot-product zero failed!",locString);
	}
    void vector3dDotProductTest() 
	{
		std::string locString = "DatastructuresTest.cpp, vector3dDotProductTest()";
		vector3d_d v1(4,8,3);
		vector3d_d v2(-3,10,-4);

		if(v1.dotProduct(v2)!=56)
			throwGeneralTestException("Initial dot-product failed!",locString);
		v1(0,1,0);
		v2(0,0,1);
		if(v1.dotProduct(v2)!=0)
			throwGeneralTestException("Dot-product zero failed!",locString);
	}
	//Cross product
    void vector3dCrossProductTest() 
	{
		std::string locString = "DatastructuresTest.cpp, vector3dCrossProductTest()";
		vector3d_d v1(-1,7,4);
		vector3d_d v2(-5,8,4);
		vector3d_d ans(-4,-16,27);

		if(v1.crossProduct(v2)!=ans)
			throwGeneralTestException("Simple cross-product failed",locString);
		if(v1*v2!=ans)
			throwGeneralTestException("Simple * failed",locString);
		if((v2*v1)!=(-ans))
			throwGeneralTestException("* reverse failed",locString);
		if((v1*=v2)!=ans)
			throwGeneralTestException("Simple *= failed",locString);
		if(v1!=ans)
			throwGeneralTestException("*= after failed",locString);

	}

    //Rotation test
    void vector2dRotationTest() 
    {
        std::string locString = "DatastructuresTest.cpp, vector3dCrossProductTest()";
        vector2d_d v1(4,5);
        vector2d_d rotate(1,0);
        
        vector2d_d ans=v1.rotate(rotate);
        vector2d_d comp=v1;
        if(ans!=comp)
            throwGeneralTestException("No rotation failed",locString);
        
        rotate(0,1);
        comp(-5,4);
        ans=v1.rotate(rotate);
        if(ans!=comp)
            throwGeneralTestException("90 degree rotation failed",locString);
        
        rotate(-1,0);
        comp(-4,-5);
        ans=v1.rotate(rotate);
        if(ans!=comp)
            throwGeneralTestException("180 degree rotation failed",locString);

        rotate(0,-1);
        comp(5,-4);
        ans=v1.rotate(rotate);
        if(ans!=comp)
            throwGeneralTestException("270 degree rotation failed",locString);

        v1(4,4);
        rotate(1,1);
        rotate.scaleSelf();
        ans=v1.rotate(rotate);
        if(!(ans.y>5.6 && ans.y<5.7 &&
           ans.x>-.1 && ans.x<.1))
            throwGeneralTestException("45 degree rotation failed",locString);
        
        v1(4,4);
        rotate(1,-1);
        rotate.scaleSelf();
        ans=v1.rotate(rotate);
        if(!(ans.x>5.6 && ans.x<5.7 &&
             ans.y>-.1 && ans.y<.1))
            throwGeneralTestException("45 degree rotation failed",locString);
    }

/*================================================================
	Misc Function Tests
 ================================================================*/

    //Reverse compare
    int reverseCompare(const int& v1,const int& v2)
    {
        if(v1<v2) return 1;
        if(v1>v2) return -1;
        return 0;
    }
    //Int pointer compare
    int pointerCompareSort(smart_ptr<int> ptr1, smart_ptr<int> ptr2)
    {
        if((*ptr1)>(*ptr2)) return 1;
        else if((*ptr1)<(*ptr2)) return -1;
        return 0;
    }

    //Basic quicksort test
    void quicksortArrayTest() throw (os::errorPointer)
    {
        std::string locString = "DatastructuresTest.cpp, quicksortArrayTest()";
        int array[100];
        srand((unsigned)time(NULL));
        for(int i1=0;i1<15;++i1)
        {
            for(int i2=0;i2<100;++i2)
                array[i2]=rand()%100;
            os::quicksort(array, 100);
            for(int i2=0;i2<99;++i2)
            {
                if(array[i2]>array[i2+1])
                {
                    throwGeneralTestException("Quicksort failed at "+std::to_string((long long unsigned)i2)+" "+std::to_string((long long unsigned)array[i2])+" vs "+std::to_string((long long unsigned)array[i2+1]),locString);
                }
            }
        }
    }
    //Reverse quicksort test
    void reverseQuicksortArrayTest() throw (os::errorPointer)
    {
        std::string locString = "DatastructuresTest.cpp, reverseQuicksortArrayTest()";
        int array[100];
        srand((unsigned)time(NULL));
        for(int i1=0;i1<15;++i1)
        {
            for(int i2=0;i2<100;++i2)
                array[i2]=rand()%100;
            os::quicksort(array, 100,&reverseCompare);
            for(int i2=0;i2<99;++i2)
            {
                if(array[i2]<array[i2+1])
                {
                    throwGeneralTestException("Quicksort failed at "+std::to_string((long long unsigned)i2)+" "+std::to_string((long long unsigned)array[i2])+" vs "+std::to_string((long long unsigned)array[i2+1]),locString);
                }
            }
        }
    }
    //Pointer quicksort
    void pointerQuicksortTest() throw (os::errorPointer)
    {
        std::string locString = "DatastructuresTest.cpp, pointerQuicksortTest()";
        os::smart_ptr<os::smart_ptr<int> > _array(new os::smart_ptr<int>[100],os::shared_type_array);
        srand((unsigned)time(NULL));
        for(int i1=0;i1<15;++i1)
        {
            for(int i2=0;i2<100;++i2)
                _array[i2]=os::smart_ptr<int>(new int(rand()%100),os::shared_type);
            os::pointerQuicksort(_array,100);
            for(int i2=0;i2<99;++i2)
            {
                if(*(_array[i2])>*(_array[i2+1]))
                {
                    throwGeneralTestException("Quicksort failed at "+std::to_string((long long unsigned)i2)+" "+std::to_string((long long unsigned)*_array[i2])+" vs "+std::to_string((long long unsigned)*_array[i2+1]),locString);
                }
            }
        }
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

		//Node frame test
		trc = smart_ptr<testSuite>(new testSuite("Node Frame"),shared_type);
			trc->pushTest("Object Node",&objectNodeTest);
			trc->pushTest("Pointer Node",&pointerNodeTest);
			trc->pushTest("Raw-pointer Node",&rawPointerNodeTest);
		pushSuite(trc);

		//Simple Hash tests
		trc = smart_ptr<testSuite>(new testSuite("Simple Hash"),shared_type);
			trc->pushTest("Basic Insertion",&basicHashInsertionTest);
			trc->pushTest("Empty",&emptyHashTest);
			trc->pushTest("Conflict",&conflictHashTest);
			trc->pushTest("Resize",&resizeHashTest);
			trc->pushTest("Hash-Table",&rawAccessTest);
		pushSuite(trc);

		//Lock tests
		trc = smart_ptr<testSuite>(new testSuite("Locks"),shared_type);
			trc->pushTest("Basic Lock",&basicLockTest);
			trc->pushTest("Thread Lock",&threadLockTest);
			trc->pushTest("Thread Counter",&threadCounterTest);
			trc->pushTest("Read-Write",&basicMultiLockTest);
			trc->pushTest("Threaded Read-Write",&threadMultiLockTest);
		pushSuite(trc);

		//Data structure test suite
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectVectorThreadSafe<dummyInt> >("objectVectorThreadSafe"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectVector<dummyInt> >("objectVector"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerVectorThreadSafe<dummyInt> >("pointerVectorThreadSafe"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerVector<dummyInt> >("pointerVector"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerVectorThreadSafe<dummyInt> >("rawPointerVectorThreadSafe"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerVector<dummyInt> >("rawPointerVector"),shared_type));

		//List suite
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectUnsortedListThreadSafe<dummyInt> >("objectUnsortedListThreadSafe"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectUnsortedList<dummyInt> >("objectUnsortedList"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerUnsortedListThreadSafe<dummyInt> >("pointerUnsortedListThreadSafe"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerUnsortedList<dummyInt> >("pointerUnsortedList"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerUnsortedListThreadSafe<dummyInt> >("rawPointerListThreadSafe"),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerUnsortedList<dummyInt> >("rawPointerList"),shared_type));

		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectSortedListThreadSafe<dummyInt> >("objectSortedListThreadSafe",true),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectSortedList<dummyInt> >("objectSortedList",true),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerSortedListThreadSafe<dummyInt> >("pointerSortedListThreadSafe",true),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerSortedList<dummyInt> >("pointerSortedList",true),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerSortedListThreadSafe<dummyInt> >("rawPointerSortedListThreadSafe",true),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerSortedList<dummyInt> >("rawPointerSortedList",true),shared_type));

		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectAVLTreeThreadSafe<dummyInt> >("objectAVLTreeThreadSafe",true),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectAVLTree<dummyInt> >("objectAVLTree",true),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerAVLTree<dummyInt> >("pointerAVLTree",true),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerAVLTreeThreadSafe<dummyInt> >("pointerAVLTreeThreadSafe",true),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerAVLTree<dummyInt> >("rawPointerAVLTree",true),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerAVLTreeThreadSafe<dummyInt> >("rawPointerAVLTreeThreadSafe",true),shared_type));
        
        pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectLinkedStackThreadSafe<dummyInt> >("objectLinkedStackThreadSafe",false),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectLinkedStack<dummyInt> >("objectLinkedStack",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerLinkedStack<dummyInt> >("pointerLinkedStack",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerLinkedStackThreadSafe<dummyInt> >("pointerLinkedStackThreadSafe",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerLinkedStack<dummyInt> >("rawPointerLinkedStack",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerLinkedStackThreadSafe<dummyInt> >("rawPointerLinkedStackThreadSafe",false),shared_type));
        
        pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectLinkedQueueThreadSafe<dummyInt> >("objectLinkedQueueThreadSafe",false),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectLinkedQueue<dummyInt> >("objectLinkedQueue",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerLinkedQueue<dummyInt> >("pointerLinkedQueue",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerLinkedQueueThreadSafe<dummyInt> >("pointerLinkedQueueThreadSafe",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerLinkedQueue<dummyInt> >("rawPointerLinkedQueue",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerLinkedQueueThreadSafe<dummyInt> >("rawPointerLinkedQueueThreadSafe",false),shared_type));
        
        pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectArrayStackThreadSafe<dummyInt> >("objectArrayStackThreadSafe",false),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectArrayStack<dummyInt> >("objectArrayStack",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerArrayStack<dummyInt> >("pointerArrayStack",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerArrayStackThreadSafe<dummyInt> >("pointerArrayStackThreadSafe",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerArrayStack<dummyInt> >("rawPointerArrayStack",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerArrayStackThreadSafe<dummyInt> >("rawPointerArrayStackThreadSafe",false),shared_type));
        
        pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectBoundedQueueThreadSafe<dummyInt> >("objectBoundedQueueThreadSafe",false),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectBoundedQueue<dummyInt> >("objectBoundedQueue",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerBoundedQueue<dummyInt> >("pointerBoundedQueue",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerBoundedQueueThreadSafe<dummyInt> >("pointerBoundedQueueThreadSafe",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerBoundedQueue<dummyInt> >("rawPointerBoundedQueue",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerBoundedQueueThreadSafe<dummyInt> >("rawPointerBoundedQueueThreadSafe",false),shared_type));
        
        pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectHashThreadSafe<dummyInt> >("objectHashThreadSafe",false),shared_type));
		pushSuite(smart_ptr<testSuite>(new datastructureNodeSuite<objectHash<dummyInt> >("objectHash",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerHashThreadSafe<dummyInt> >("pointerHashThreadSafe",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<pointerHash<dummyInt> >("pointerHash",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerHashThreadSafe<dummyInt> >("rawPointerHashThreadSafe",false),shared_type));
        pushSuite(smart_ptr<testSuite>(new datastructurePointerSuite<rawPointerHash<dummyInt> >("rawPointerHash",false),shared_type));
        

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
            trc->pushTest("Rotate Test",&vector2dRotationTest);
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
        
        //Misc Function
        trc = smart_ptr<testSuite>(new testSuite("Misc Functions"),shared_type);
            trc->pushTest("Raw Quicksort",&quicksortArrayTest);
            trc->pushTest("Reverse Quicksort",&quicksortArrayTest);
            trc->pushTest("Pointer Quicksort",&pointerQuicksortTest);
        pushSuite(trc);
	}

#endif

///@endcond