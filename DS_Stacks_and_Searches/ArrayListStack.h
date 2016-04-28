template <class T> class Stack
{public:
	virtual		int		Count()const		= 0;// returns the number of items in the list
	virtual		void	Push(const T & item)= 0;// push item onto the stack
	virtual		  T		Pop ()				= 0;// pop top item from the stack
	virtual const T &	Peek() const		= 0;// return item from top of stack, but leave it there
};

template <class T> class OrderedList
{public:
	virtual int Count()  const = 0;				// returns the number of items in the list
	virtual void Add	(const T& item) = 0;	// add new item into proper location in list
	virtual void Remove (const T& item) = 0;	// remove item if it exists from list
	
	class OrderedListIterator
	{public:
		virtual bool HasNext() const = 0; // returns true if there is a next item
		virtual T&		Next()		 = 0; // returns next item and advances iterator toward end
		virtual T	  Remove()		 = 0; // removes item at current position, contracting the list
	};
	virtual OrderedListIterator * Begin() = 0;	// returns new iterator at beginning of list
	virtual OrderedListIterator * Find(const T & target) = 0;
	//\\ returns new iterator at the item in the list, or NULL if not found.
};