// List.h
// Pete Myers, 3/28/2016
// Abstract interface for the List data structure

#pragma once

template <class T> class List
{
public:
	virtual int Count() const = 0;		// returns the number of items in the list
	virtual void Insert(const T & item, int index) = 0;    // index from 0 to Count
	virtual void Append(const T & item) = 0;      // add to end of list
	virtual T & Remove(int index) = 0;            // remove item at index
	virtual const T & Get(int index) const = 0;   // return item at index

	class ListIterator
	{
	public:
		virtual bool HasNext() const = 0;    // returns true if there is a next item
		virtual T & Next() = 0;              // returns next item and advances iterator toward end
		virtual bool HasPrevious() const = 0;// returns true if there is a previous item
		virtual T & Previous() = 0;          // returns previous item and advances iterator toward beginning
		virtual void Insert(const T & item) = 0;  // inserts item at current position, making room as needed
		virtual T & Remove() = 0;        // removes item at current position, contracting the list
	};

	virtual ListIterator * Begin() = 0;  // returns new iterator at beginning of list
	virtual ListIterator * End() = 0;    // returns new iterator past end of list
};
