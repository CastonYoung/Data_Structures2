//#include "Stdafx.h"
template <class T> class Organized : public OrderedList<T>
{public:
				Organized();
	virtual int Count()  const { return actuallist.Count(); }				// returns the number of items in the list
	virtual void Add	(const T& item);	// add new item into proper location in list
	virtual void Remove (const T& item);	// remove item if it exists from list
	
	class OLI: public OrderedListIterator
	{public:
					 OLI();
		virtual bool HasNext() const; // returns true if there is a next item
		virtual T&		Next()		; // returns next item and advances iterator toward end
		virtual T	  Remove()		; // removes item at current position, contracting the list
	};
	virtual OrderedListIterator * Begin();	// returns new iterator at beginning of list
	virtual OrderedListIterator * Find(const T & target);
	//\\ returns new iterator at the item in the list, or NULL if not found.
private:

};