#include "Stdafx.h"
using namespace std;

template<typename T> class LL;

template<typename T> class node;


template<typename T>
class node
{public:
	node(T data)	{ m_data = new T(data); }

#ifdef DISPLAY_METHOD
	void Display()	{ m_data->DISPLAY_METHOD; }
#endif

	~node(){ delete m_data; }

private:
	node<T>* m_next;
	node<T>* m_prev;
	T* m_data;

friend class LL<T>;
};


template<typename T>
class LL: public OrderedList<T>
{public:

	LL(){	head = 0;	tail = 0;	N_items = 0;
			LNS ="Error: There is no list yet.";
			ENL ="Error: An entry with that ID has not been listed.";
			EAL ="Error: An entry with that ID is already in the list.";
		}

	int Count()const { return N_items; }

	void bbA(const T &item)
	{	++N_items;
		node<T>* temp = new node<T>(item);	//Allocate and create a new cNode.
		if (tail == 0)			//If first list item.
		{	tail = temp;		// /Set the head and tail
			head = temp;	}	// \to the first position.
		tail->m_next = temp;	// /Move the new node-
		temp->m_prev = tail;	// \pointer to the end.
		tail = temp;			//Declare this to be the tail
		temp->m_next = head;	//Reattach tail to head
		head->m_prev = tail;	//Reattach head to tail
	}

	void Add(const T &item)
	{	++N_items;
		node<T>* temp = new node<T>(item);	//Allocate and create a new cNode.
		if (tail == 0)			//If first list item.
		{	tail = temp;		// /Set the head and tail
			head = temp;	}	// \to the first position.		
		head->m_prev = temp;	// /Move the new node-
		temp->m_next = head;	// \pointer to the start.
		head = temp;			//Declare this to be the head
		temp->m_prev = tail;	//Reattach head to tail
		tail->m_next = head;	//Reattach tail to head
	}
	

	void Insert(const T &item, int index)
	{	node<T>* othr = Find1(index);
		Insert(item, othr);
	}

	inline void Insert(const T &item, node<T>* &othr)
	{	if (!N_items) throw LNS;		//Check because it doesn't take that long.
		if (!othr	) throw ENL;		//For when (Insert(item,Find(tag)) && Find(tag)==NULL).
		++N_items;
		node<T>* temp=new node<T>(item);//Allocate and create a new cNode.
		temp->m_prev = othr->m_prev;	//Set the new node's m_prev to the node behind.
		othr->m_prev->m_next = temp;	//Set the node behind's   m_next to the new node.
		othr->m_prev = temp;			//Set the node in-front's m_prev to the new node.
		temp->m_next = othr;			//Set the new node's m_next to the node in-front.
		if(othr == head) head = temp;
	}

	void Insert_after(const T &item, int index)
	{	node<T>* othr = Find1(index);
		Insert_after(item, othr);
	}

	inline void Insert_after(const T &item, node<T>* &othr)
	{	if (!N_items) throw LNS;		//Check because it doesn't take that long.
		if (!othr	) throw ENL;		//For when (Insert(item,Find(tag)) && Find(tag)==NULL).
		++N_items;
		node<T>* temp=new node<T>(item);//Allocate and create a new cNode.
		temp->m_next = othr->m_next;	//Set the new node's m_next to the node in-front.
		othr->m_next->m_prev = temp;	//Set the node in-front's m_prev to the new node.
		othr->m_next = temp;			//Set the node behind's   m_next to the new node.
		temp->m_prev = othr;			//Set the new node's m_prev to the node behind.
		if(othr == tail) tail = temp;
	}


#ifdef CELL_ID
	/*\/ Safe Add first checks, to ensure there will be no repeats.\/*/
	
	void s_Add(T &item, string tag, bool before = false)
	{	if (!Find(tag) && before == false)	bbA(item);
		else if (!Find(tag))				Add(item);
	else throw EAL;
	}
	
	void s_Add(T &item, string tag, int other, bool before = false)
	{		 if ( Find(tag) )	throw EAL;
		else if (!Find(other)	throw ENL;//For when (s_Add(item,tag,Find(tag)) && Find(tag)==NULL).
		else if (before) Insert_after(item, other);
		else Insert(item, other);
	}

	node<T>* Find(string &tag)//--------------------Returns a specific node
	{	if (head == 0) return 0;			//Otherwise program will crash.
		int checks(0);
		node<T>* nptr = head;				//create a pointer to continually check against
		
		do{	if(nptr->m_data->CELL_ID == tag) return nptr;		//if found
			nptr = nptr->m_next;	}while(nptr != head);	//if not found

		return 0;							//if never found
	}


	T* operator[](string &tag)		{ if (Find(tag)) return  (Find(tag))->m_data ; return false; }
	const &T Get (string &tag)const { if (Find(tag)) return *(Find(tag) ->m_data); return false; }
						//I'm assuming modern compilers won't actually make Find run twice. 
#endif

	node<T>* Find1(unsigned index)const//--------------------Returns a specific node
	{	if (head == 0) return 0;			//Otherwise program will crash.
		int check(0);
		node<T>* nptr = head;				//create a pointer to continually check against

		do{	if (check++ == index) return nptr;		//if found
			nptr = nptr-> m_next;
		  } while (nptr != head);				//if not found

		return 0;							//if never found
	}
	node<T>* Find2(const T& item)const//--------------------Returns a specific node
	{	if (head == 0) return 0;			//Otherwise program will crash.
		int check(0);
		node<T>* nptr = head;				//create a pointer to continually check against

		do{	if (*(nptr->m_data) == item) return nptr;		//if found
			nptr = nptr-> m_next;
		  } while (nptr != head);				//if not found

		return 0;							//if never found
	}

	T* operator[](int index)	 { return  (Find1(index))->m_data ; }
	const T& Get (int index)const{ return *(Find1(index) ->m_data); }
	

	void Remove(unsigned indX){Extract(indX);}
	void Remove(const T& item){Extract(item);}
	void Remove(node<T>* nptr){Extract(nptr);}

	T& Extract(unsigned index)
	{	node<T>* nptr = Find1(index);
		if (!nptr ) throw ENL;
		return Extract(nptr);
	}
	T& Extract(const T& item)
	{	node<T>* nptr = Find2(item);
		if (!nptr ) throw ENL;
		return Extract(nptr);
	}
	T& Extract(node<T>* &nptr)
	{	if ( nptr == head ) head = nptr->m_next;	//If at head update
   else if ( nptr == tail ) tail = nptr->m_prev;	//If at tail update
		nptr->m_next->m_prev = nptr->m_prev;		//Move m_next
		nptr->m_prev->m_next = nptr->m_next;		//Move m_prev
		--N_items;									//update N_items
		return *(nptr->m_data);						//Return the node data
	}

#ifdef DISPLAY_METHOD
	void Display_all()//Calls Cell.Display once for each city. Shares many elements with search routine.
	{if (N_items > 0){
		node<T>* nptr = head;			 //Create a temporary node 
		do{	nptr->m_data->DISPLAY_METHOD;//Call display
			nptr = nptr->m_next;		 //Go to the next node.
		} while( nptr != head );		 //While not at end.
	}}
#endif


	void Purge()
	{	int i = 0;
		node<T>* nptr = head;
		do {Extract(i++);
			nptr = nptr->m_next;
			nprt->m_prev->~node();
		} while (N_items > 0);
		head = 0;
		tail = 0;
	}

	class OLI: public OrderedListIterator
	{public:
		OLI(LL<T> * La_Lista, node<T>* a): Linked(La_Lista), noedy(a){}
		
		OLI(const OLI &oli): Linked(oli.Linked), noedy(oli.noedy){}

		virtual bool HasNext	() const { if (noedy != Linked-> tail ) return true;  return false; }
		virtual bool HasPrevious() const { if (noedy != Linked-> head ) return true;  return false; }
			// Returns true if there is a next or previous item respectively.

		virtual T & Next()		// Returns CURRENT item and advances iterator toward end.
		{	noedy  = noedy->m_next;
			return *(noedy->m_prev->m_data);
		}
		virtual T & Previous()	// Returns previous item and advances iterator toward beginning.
		{	noedy  = noedy->m_prev;
			return *(noedy->m_data);
		}
		virtual void Insert(const T & item)	{ Linked->Insert(item, noedy); }
			// Inserts item at current position, making room as needed.

		virtual T Remove()					{ return Linked->Extract(noedy); }
			// Removes item at current position, contracting the list.

	private:LL<T>* Linked;
			node<T>*noedy;
	};
	
	OrderedListIterator* Begin(				)	{ return new OLI( this, head ); }
		//\\ returns new iterator at beginning of list.

	OrderedListIterator* End (				)	{ return new OLI( this, tail ); }
		//\\ returns new iterator past end of list.

	OrderedListIterator* Find(const T & target)	{ return new OLI( this, Find2(target) ); }
		//\\ returns new iterator at the item in the list, or NULL if not found.

private: 
	int N_items;
	node<T>* head; node<T>* tail;
	string LNS, ENL, EAL;
};