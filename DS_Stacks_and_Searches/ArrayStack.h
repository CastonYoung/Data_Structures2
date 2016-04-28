#include "Stdafx.h"

template <class T> class StackRA: public Stack<T>
{public:
						StackRA()		{ i=0; }						// Start at the end.
	virtual	int			Count()const	{ return TheRA.Count(); }		// Get # of items.
	virtual	void Push( const T & item )	{ TheRA.Append(item); ++i; }	// Push item onto the stack.
	virtual		  T		Pop ()			{ return TheRA.Remove(--i);	}	// Take an item from the top.
	virtual const T &	Peek() const	{ return TheRA[i-1]; }			// Return an item from top, but leave it there.

private:
	ArrayList<T> TheRA;
	unsigned i;
};