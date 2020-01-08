#include "pch.h"
#include <set>
#include "CppUnitTest.h"
#include "..\p-3-search\Dictionary.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;



namespace UnitTest1
{



	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(getSize_Test)
		{

			Dictionary<string, int> chr;
			chr.put("exp", 50);
			chr.put("ammo", 50);
			Assert::AreEqual(2, chr.getSize());

		}
		TEST_METHOD(remove_Test)
		{
			Dictionary <string, int> chr;
			chr.put("exp", 50);
			chr.put("ammo", 50);
			chr.remove("exp");
			Assert::AreEqual(1, chr.getSize());
			Assert::IsFalse(chr.contains("exp"));
		}

		TEST_METHOD(contains_Test)
		{
			Dictionary <string, int> chr;
			chr.put("exp", 50);
			chr.put("ammo", 50);
			Assert::AreEqual(false, chr.contains("health"));
			chr.put("health", 60);
			Assert::AreEqual(true, chr.contains("health"));
			chr.remove("health");
		}
		TEST_METHOD(get_index_operator_Test)
		{
			Dictionary <string, int> chr;
			chr.put("exp", 50);
			chr.put("ammo", 80);
			Assert::AreEqual(50, chr["exp"]);

		}

		TEST_METHOD(get_index_operator_UnexcitedElement_Test)
		{
			Dictionary <string, int> chr;
			Assert::AreEqual(0, chr["exp"]);
		}
		TEST_METHOD(set_index_operator_Test)
		{
			Dictionary <string, int> chr;
			chr.put("exp", 50);
			chr.put("ammo", 80);
			chr["exp"] = 44;
			Assert::AreEqual(44, chr["exp"]);
		}

		TEST_METHOD(iterator_getKey_Test)
		{
			Dictionary <string, int> chr;
			chr.put("ammo", 50);
			auto it = chr.iterator();
			string key = "ammo";
			Assert::AreEqual(key, it.key());
		}

		TEST_METHOD(iterator_setValue_Test)
		{
			Dictionary <string, int> chr;
			chr.put("ammo", 80);
			auto it = chr.iterator();
			it.set(56);
			Assert::AreEqual(56, it.get());
		}

		TEST_METHOD(iterator_NextOperator_Test)
		{

			Dictionary<int, int> chr;
			std::set<int> defaultSet;
			std::set<int> curentSet;

			for (int i = 0; i < 15; i++)
			{
				chr.put(i, i);
				defaultSet.insert(i);
			}


			auto it = chr.iterator();


			curentSet.insert(it.get());

			int i = 0;
			while (it.hasNext())
			{
				it.next();
				curentSet.insert(it.get());
			}

			Assert::IsTrue(defaultSet == curentSet);
		}

		TEST_METHOD(iterator_PrevOperator_Test)
		{

			Dictionary<int, int> chr;
			std::set<int> defaultSet;
			std::set<int> curentSet;

			for (int i = 0; i < 15; i++)
			{
				chr.put(i, i);
				defaultSet.insert(i);
			}


			auto it = chr.iterator();
			while (it.hasNext())
			{
				it.next();
			}

			curentSet.insert(it.get());

			int i = 0;
			while (it.hasPrev())
			{
				it.prev();
				curentSet.insert(it.get());
			}

			Assert::IsTrue(defaultSet == curentSet);

		}

	};
}
