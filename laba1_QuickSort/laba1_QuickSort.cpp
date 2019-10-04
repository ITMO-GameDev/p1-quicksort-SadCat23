
#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int size_inter = 16;
template<typename T, typename Compare>
void sorter(T *first, T *last, const Compare &comp);
template<typename T, typename R, typename Compare>void intersation_sort(T *mas, const R count, const Compare &comp){
	int key = 0;
	T temp = 0;
	for (int i = 0; i < count - 1; i++)
	{
		key = i + 1;
		temp = mas[key];
		for (int j = i + 1; j > 0; j--)
		{
			if (comp(temp, mas[j - 1]))
			{
				mas[j] = mas[j - 1];
				key = j - 1;
			}
		}
		mas[key] = temp;
	}
}

template<typename T, typename Compare>
void quick_sort(T *first, T *last, const Compare &comp)
{
	T* l;
	T* f;
	T a[3];
	T pivot;
	T buf;

	while (first != last)
	{
		const  T* midle = first + ((last - first) / 2);
		f = first;
		l = last;
		a[0] = *first;
		a[1] = *last;
		a[2] = *midle;
		//вызов сортировки вставками для определения медианны
		intersation_sort(a, 3, comp);
		//медианна средний элемент массива 
		pivot = a[1];
		do
		{

			while (comp(*f, pivot))
			{
				f++;
				if (f == l) { break; }
			}
			while (comp(pivot, *l))
			{
				l--;
				if (f == l) { break; }
			}
			if (f < l) //swap
			{

				buf = *f;
				*f = *l;
				*l = buf;
				f++;
				l--;
			}
		} while (f < l);

		if (f == l)
		{

			if (comp(*f, pivot)) { l++; }
			else { f--; }

		}
		if (f > l)
		{
			T *buf = f;
			f = l;
			l = buf;
		}

		//сравнение размера двух получившихся частей
		if ((f - first) < (last - l))
		{
			//вызов рекурсии для меньшей части
			if (first < l)
			{
				sorter(first, l - 1, comp);
			}
			//если большая часть меньше size_inter(16)-вызываем сортировку вставками 
			//и выходим из вызова функции
			if ((last - l) <= size_inter)
			{

				intersation_sort(l, last - l + 1, comp);
				break;
			}
			//иначе итеративно сортируем коректируя указтели для следующего прохода цикла 
			else
			{
				first = l;
			}
		}
		//сравнение размера двух получившихся частей
		else
		{
			//вызов рекурсии для меньшей части
			if (f < last)
			{
				sorter(f + 1, last, comp);

			}
			//если большая часть меньше size_inter(16)-вызываем сортировку вставками 
			//и выходим из вызова функции
			if (f - first <= size_inter)
			{

				intersation_sort(first, f - first + 1, comp);
				break;
			}
			//иначе итеративно сортируем коректируя указтели для следующего прохода цикла 
			else
			{
				last = f;
			}
		}

	}

}



template<typename T, typename Compare>
void sorter(T *first, T *last, const Compare &comp){
	int size = (last - first) + 1;
	//если размер меньше 16-сортировка вставками 
	if (size <= size_inter)
	{
		intersation_sort(first, size, comp);
	}
	//иначе бытсрая сортировка
	else
	{
		quick_sort(first, last, comp);
	}
}

int main()
{
	getchar();
}

