// dynamicArray.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <utility>


using namespace std;

template <typename T>
class Array
{

protected:
	int capacity;
public:
	T* arr = nullptr;
	int size = 0;
	// конструкторы
	Array();
	Array(int capacity);
	~Array();
	
	class Iterator
	{
		 Array *array;
	public:
		T* cur;

		Iterator( Array<T> *a)
		{
			array = a;
			cur = a->arr;
		}
		const T& get() const		{			return *cur;		}		void set(const T& value)		{			*cur = value;		}		void remove()		{			int index = cur - array->arr;			array->remove(index);			toIndex(index);		}		void insertIt(const T& value)		{			int index = cur - array->arr;			array->insert(value,index);		}		void next()		{			cur++;		}		void prev()		{			cur--;		}		void toIndex(int index)		{			cur = &array->arr[index];		}		bool hasNext() const
		{
			if (cur==array->arr+array->size-1)
			{
				return false;
			}
			return true;
		}

		bool hasPrev() const
		{
			if (cur == array->arr)
			{
				return false;
			}
			return true;
		}
	};
	const T& operator [] (int i) const;
	T& operator [] (int i);
	void insert(const T& value);
	void insert(const T& value, int index);
	void remove(int index);
	void RightShift(int index);
	void LeftShift(int index);
	int getsize() const;
	
	Iterator iterator()
	{
		Iterator it(this);
		return it;
	}
	

};


//конструкторы
template <typename T>
Array<T>::Array()
{
	arr = new T[8];
	capacity = 8;
}
template <typename T>
Array<T>::Array(int capacity)
{
	arr = new T[capacity];
	this->capacity = capacity;
}

template <typename T>
Array<T>::~Array()
{
	if (size > 0)
	{
		delete[] arr;
	}

}


//сдвиги
template <typename T>
void Array<T>::RightShift(int index)
{
	for (int i = size-1; i >= index; i--)
	{
		arr[i+1] = arr[i];
	}
}

template <typename T>
void Array<T>::LeftShift(int index)
{
	for (int i = index; i < size-1; i++)
	{
		arr[i] = arr[i+1];
	}
}

//идексирование
template <typename T>
const T& Array<T>::operator[](int index) const
{
	if (index >= 0 && index < size)
	{
		return arr[index];
	}
}

template <typename T>
 T& Array<T>::operator[](int index)
{
	 if (index >= 0 && index < size)
	 {
		 return arr[index];
	 }
}


 //ужаление
template <typename T>
void Array<T>::remove(int index)
{
	if (index>=0&&index<size)
	{
		LeftShift(index);
		T* buf = new T[capacity];
		size--;	
		copy(arr, arr + size, buf);
		delete[] arr;
		arr = buf;	
	}

}


//втавка
template <typename T>
void Array<T>::insert(const T& value)
{
	if (size >= capacity)
	{
		cout << " resize";
		capacity = capacity * 2;
		T* buf = new T[capacity];
		copy(arr, arr + size, buf);
		delete[] arr;
		arr = buf;
	}
	arr[size] = value;
	size++;
}

template <typename T>
void Array<T>::insert(const T& value, int index)
{
	if (size >= capacity)
	{
		cout << " resize\n";
		capacity = capacity * 2;
		T* buf = new T[capacity];
		copy(arr, arr + size, buf);
		delete[] arr;
		arr = buf;
	}
	if (index != size)
	{
		RightShift(index);
	}
	arr[index] = value;
	size++;
}



//размер
template <typename T>
int Array<T>::getsize() const
{
	return size;	
}

class Student
{
public:
	const char* FIO=new char[10];
	int id;
};



int main()
{
	Array<int> MyArray;
	for (int i = 0; i < 6; i++)
	{
		MyArray.insert(i);
	}
	auto it = MyArray.iterator();
	it.next();
	it.remove();
	
	for (int i = 0; i < MyArray.getsize(); i++)
	{
		cout << MyArray[i];
	}
	
	cout << endl << it.get();
	getchar();
}

