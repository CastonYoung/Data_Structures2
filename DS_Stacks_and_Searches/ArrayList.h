// ArrayList.h
// Caston Young, 4/16/2016
// ArrayList implementation of the List data structure

#pragma once
#include "Stdafx.h"


template <class T> class ArrayList : public List<T>
{private:
	int start_i;	// the index of the first item.
	int count;			// # of items in the list
	int size;			// capacity of the list
	T* the_array;

public:
	ArrayList(int start_index = 0)
	{	start_i = start_index;
		count = 0;
		size = 10;
		the_array = new T[size];
	}

	virtual int Count() const	{ return count; }	// returns the number of items in the list

	virtual void SetStartIndex	(int start_index)	{ start_i = start_index; }

	virtual void DoubleSize()
	{	// double the capacity
		int newSize = size * 2;
		T * newArray = new T[newSize];
		if (newArray == NULL)throw AF;
		for (int i = 0; i < size; i++)	newArray[i] = the_array[i];//Copy values
		delete [] the_array;	// free up old memory	
		the_array = newArray;	// save the new
		size = newSize;
	}

	virtual void Append(const T & item)      // add to end of list
	{	if (count >= size) DoubleSize();
		the_array[count++] = item;
	}

	virtual void Insert(const T & item, int index)	// index from 0 to Count
	{	index = index - start_i;
		if (index+1 > count) Append(item);
		else
		{	if (count++ == size) DoubleSize();
			for(int i = count; i > index; i--) the_array[i] = the_array[i-1];
			the_array[index] = item;
		}
	}

	virtual T & Remove(int index)			// remove item at index
	{	index = index - start_i;
		if (index < 0) throw LNS;
		if (index+1 > count) throw OoB;
		T* value = new T(the_array[index]);
		while(++index < count)	the_array[index-1] = the_array[index];
		--count;// </\I believe this to be the most optimum /\_
		return *value;
	}

											// return item at index
	virtual const T& operator[]	(int index) const { return Get(index); }
	virtual const T& Get		(int index) const
	{	index = index - start_i;
		if(index >= 0 && index < size)	return the_array[index];
		else throw OoB;
	}


	class ArraIterator : public ListIterator
	{public:
		ArraIterator(ArrayList<T>* l, int i = 0): list(l), index(i)
			{ if (0 > i || i > l->Count()) throw OoB; }
		// Constructs a new ArraIterator using whatever integer is passed in.

		virtual bool HasNext(				) const	{ return (index <= list->Count()); }
		// Returns true if there is a CURRENT item.

		virtual T &  Next	(				)		{ return list->the_array[index++]; }
		// Returns CURRENT item and advances iterator toward end.

		virtual bool HasPrevious(			) const	{ return (index >= 0); }
		// Returns true if there is a previous item.

		virtual T & Previous(				)		{ return list->the_array[--index]; }
		// Returns previous item and advances iterator toward beginning.

		virtual void Insert (const T & item )		{ list->Insert(item, index); }
		// Inserts item at current position, making room as needed.

		virtual T &  Remove (				)		{ return list->Remove(index); }
		// Removes item at current position, contracting the list.

	private: 
		ArrayList<T>* list;
		int index;
	};

	virtual ListIterator * Begin()	{ return new ArraIterator(this, start_i); }
	// returns new iterator at beginning of list
	
	virtual ListIterator * End()	{ return new ArraIterator(this, count - start_i - 1); }
	// returns new iterator past end of list
};
