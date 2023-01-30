#pragma once
template<class T> class PriorityQueue
{
public:

	PriorityQueue();
	PriorityQueue(PriorityQueue* queueToCopy);
	~PriorityQueue();

	void Push(T item);
	T Pop();
	void Print();
	bool IsEmpty();
	int GetSize();

	T operator[](int);

private:
	int trueLength; // What is the true size of the array 
	int dataLength;	// How much useful data is inside the array 
	void BubbleSort(T* items, int size);
	void Swap(T* i, T* j);

	T* items;
};

#include <iostream>

template<class T> PriorityQueue<T>::PriorityQueue()
{
	trueLength = 2;
	dataLength = 0;

	items = new T[trueLength];
}

template <class T> PriorityQueue<T>::PriorityQueue(PriorityQueue* queueToCopy)
{
	trueLength = queueToCopy->trueLength;
	dataLength = queueToCopy->dataLength;

	items = new T[trueLength];

	// Copy over item values 
	for (int i = 0; i < dataLength; i++)
	{
		items[i] = queueToCopy->items[i];
	}

}

template <class T> PriorityQueue<T>::~PriorityQueue()
{
	//delete[] items; // Causes crashing? 
	items = nullptr;
}

template <class T> void PriorityQueue<T>::Push(T item)
{
	cout << item << endl;
	// Check if can fit into inner array 
	if (dataLength + 1 < trueLength)
	{
		// Adds to end of data length 
		items[dataLength] = item;
		dataLength += 1;
	}
	else
	{
		// Copy array to new one 
		trueLength *= 2;
		T* next = new T[trueLength];

		// Copying items 
		for (int i = 0; i < dataLength; i++)
		{
			next[i] = items[i];
		}

		// Adds the newest item 
		next[dataLength] = item;

		//delete[] items; // Cleans up previous array 

		// replaces inner array with bigger array 
		items = next;
		dataLength++;
	}

	BubbleSort(items, dataLength);
}

using namespace std;
template <class T> T PriorityQueue<T>::Pop()
{
	if (dataLength >= 1)
	{
		// Return the first in the array and set new 
		// array that no longer has first placed item 
		T hold = items[0];

		T* next = new T[trueLength];
		
		//cout << items[0] << endl;

		// Copies items by starting without past first in queue
		for (int i = 1; i < dataLength; i++)
		{
			next[i - 1] = items[i];
		}
		dataLength -= 1;

		//delete[] items;
		items = next;

		return hold;
	}

	// Default value 
	return NULL;

}

template <class T> void PriorityQueue<T>::Print()
{
	for (int i = 0; i < dataLength; i++)
	{
		std::cout << items[i] << std::endl;
	}
}

template <class T> bool PriorityQueue<T>::IsEmpty()
{
	return dataLength == 0;
}

template <class T> int PriorityQueue<T>::GetSize()
{
	return dataLength;
}


/// <summary>
/// Sorts the contents of the array 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="arr"></param>
/// <param name="size"></param>
template <class T> void PriorityQueue<T>::BubbleSort(T* arr, int size)
{

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			//std::cout << arr[j] << std::endl;
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

template <class T> void PriorityQueue<T>::Swap(T* i, T* j)
{
	T temp = *i;
	*i = *j;
	*j = temp;
}


template <class T> T PriorityQueue<T>::operator[] (int index)
{
	if (index < dataLength && index >= 0)
	{
		return items[index];
	}
	else
	{
		// Does not exist
		return NULL;
	}
}