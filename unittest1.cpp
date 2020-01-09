#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\dynamicArray\dynamicArray.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace arrayTest
{		
	TEST_CLASS(UnitTestIntArray)
	{
	public:
		void InitIntArray(Array<int> *MyArray)
		{
			for (int i = 0; i < 10; i++)
			{
				MyArray->insert(i);
			}
		}	
		TEST_METHOD(GetItem)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			Assert::AreEqual(5, MyArray[5]);
		}
		TEST_METHOD(SetItem)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			MyArray[4] = 11;
			Assert::AreEqual(11, MyArray[4]);
		}
		TEST_METHOD(remove)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			MyArray.remove(5);
			Assert::AreEqual(6, MyArray[5]);
		}
		TEST_METHOD(Size)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			Assert::AreEqual(10,MyArray.getsize());
		}
		TEST_METHOD(Insert)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			MyArray.insert(10);
			Assert::AreEqual(10, MyArray[10]);
		}

		TEST_METHOD(InsertIndex)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			MyArray.insert(10,2);
			Assert::AreEqual(10, MyArray[2]);
		}

		TEST_METHOD(getIterator)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			auto it = MyArray.iterator();
			it.next();
			Assert::AreEqual(MyArray[1], it.get());
		}
		TEST_METHOD(setIterator)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			auto it = MyArray.iterator();
			it.next();
			it.set(9);
			Assert::AreEqual(9, MyArray[1]);
			Assert::AreEqual(9, it.get());
		}
		TEST_METHOD(removeIterator)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			auto it = MyArray.iterator();
			it.next();
			it.remove();
			Assert::AreEqual(2, it.get());
			Assert::AreEqual(2, MyArray[1]);
		}
		TEST_METHOD(insertIt)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			auto it = MyArray.iterator();
			it.next();
			it.insertIt(12);
			Assert::AreEqual(12,it.get());
			Assert::AreEqual(12, MyArray[1]);
		}
		TEST_METHOD(toIndexIt)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			auto it = MyArray.iterator();
			it.toIndex(5);
			Assert::AreEqual(MyArray[5], it.get());
		}
		TEST_METHOD(hasPrevIt)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			auto it = MyArray.iterator();
			it.toIndex(5);
			Assert::IsTrue(it.hasPrev());
			it.toIndex(0);
			Assert::IsFalse(it.hasPrev());
		}

		TEST_METHOD(hasNextIt)
		{
			Array<int> MyArray;
			InitIntArray(&MyArray);
			auto it = MyArray.iterator();
			it.toIndex(9);
			Assert::IsFalse(it.hasNext());
			it.toIndex(0);
			Assert::IsTrue(it.hasNext());	
		}

	};
}