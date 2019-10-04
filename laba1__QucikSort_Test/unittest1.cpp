#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdlib>
#include <ctime>
#include "..\laba1_QuickSort\laba1_QuickSort.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{

	int compare(const void * x1, const void * x2)   // функция сравнения элементов массива
	{
		return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
	}
	int compareReverse(const void * x1, const void * x2)   // функция сравнения элементов массива
	{
		return -(*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
	}
	int compareDouble(const void * x1, const void * x2)   // функция сравнения элементов массива
	{
		return (*(double*)x1 - *(double*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
	}


	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(IntRandomArrayIncrease_100items)
		{
			int *a = new int[100];
			int *b = new int[100];
			srand(time(0));
			for (int i = 0; i < 100; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 100, b);
			qsort(a, 100, sizeof(int), compare);
			sorter(b, b + 99, [](int a, int b) { return a < b; });

			for (int i = 0; i < 100; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
		}

		TEST_METHOD(IntRandomArrayIncrease_1000items)
		{
			int *a = new int[1000];
			int *b = new int[1000];
			srand(time(0));
			for (int i = 0; i < 1000; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 1000, b);
			qsort(a, 1000, sizeof(int), compare);
			sorter(b, b + 999, [](int a, int b) { return a < b; });

			for (int i = 0; i < 1000; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
		}
		TEST_METHOD(IntRandomArrayIncrease_10000items)
		{
			int *a = new int[10000];
			int *b = new int[10000];
			srand(time(0));
			for (int i = 0; i < 10000; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 10000, b);
			qsort(a, 10000, sizeof(int), compare);
			sorter(b, b + 9999, [](int a, int b) { return a < b; });
			for (int i = 0; i < 10000; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
			// TODO: Разместите здесь код своего теста
		}
		TEST_METHOD(IntRandomArrayIncrease_100000items)
		{
			int *a = new int[100000];
			int *b = new int[100000];
			srand(time(0));
			for (int i = 0; i < 100000; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 100000, b);
			qsort(a, 100000, sizeof(int), compare);
			sorter(b, b + 99999, [](int a, int b) { return a < b; });
			for (int i = 0; i < 100000; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
			// TODO: Разместите здесь код своего теста
		}



		TEST_METHOD(IntRandomArrayDecrease_1000items)
		{
			int *a = new int[1000];
			int *b = new int[1000];
			srand(time(0));
			for (int i = 0; i < 1000; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 1000, b);
			qsort(a, 1000, sizeof(int), compareReverse);
			sorter(b, b + 999, [](int a, int b) { return a > b; });
			for (int i = 0; i < 1000; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
			// TODO: Разместите здесь код своего теста
		}

		TEST_METHOD(doubleRandomArrayIncrease_1000items)
		{
			double *a = new double[1000];
			double *b = new double[1000];
			srand(time(0));
			for (int i = 0; i < 1000; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 1000, b);
			qsort(a, 1000, sizeof(double), compareDouble);
			sorter(b, b + 999, [](double a, double b) { return a < b; });
			for (int i = 0; i < 1000; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
		}

		TEST_METHOD(IntOneItems)
		{
			int *a = new int[1];
			int *b = new int[1];
			srand(time(0));
			for (int i = 0; i < 1; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 1, b);
			qsort(a, 1, sizeof(int), compare);
			sorter(b, b + 0, [](int a, int b) { return a > b; });
			for (int i = 0; i < 1; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
			// TODO: Разместите здесь код своего теста
		}

		TEST_METHOD(IntSortRandomArray_1000items)
		{
			int *a = new int[1000];
			int *b = new int[1000];
			srand(time(0));
			for (int i = 0; i < 1000; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 1000, b);
			qsort(a, 1000, sizeof(int), compare);
			qsort(b, 1000, sizeof(int), compare);
			sorter(b, b + 999, [](int a, int b) { return a < b; });
			for (int i = 0; i < 1000; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
			// TODO: Разместите здесь код своего теста
		}


		TEST_METHOD(IntSortRandomArray_100000items)
		{
			int *a = new int[100000];
			int *b = new int[100000];
			srand(time(0));
			for (int i = 0; i < 100000; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 100000, b);
			qsort(a, 100000, sizeof(int), compare);
			qsort(b, 100000, sizeof(int), compare);
			sorter(b, b + 99999, [](int a, int b) { return a < b; });
			for (int i = 0; i < 100000; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
			// TODO: Разместите здесь код своего теста
		}

		TEST_METHOD(IntSortRandomArrayReverse_1000items)
		{
			int *a = new int[1000];
			int *b = new int[1000];
			srand(time(0));
			for (int i = 0; i < 1000; i++)
			{
				a[i] = rand() % 1000;
			}
			copy(a, a + 1000, b);
			qsort(a, 1000, sizeof(int), compareReverse);
			qsort(b, 1000, sizeof(int), compare);
			sorter(b, b + 999, [](int a, int b) { return a > b; });
			for (int i = 0; i < 1000; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
			// TODO: Разместите здесь код своего теста
		}

		TEST_METHOD(IntNoInitArray)
		{
			int *a = new int[100];
			int *b = new int[100];
			srand(time(0));
			copy(a, a + 100, b);
			qsort(b, 100, sizeof(int), compareReverse);
			sorter(b, b + 99, [](int a, int b) { return a > b; });
			for (int i = 0; i < 100; i++)
			{
				Assert::AreEqual(b[i], a[i]);
			}
			// TODO: Разместите здесь код своего теста
		}




	};
}