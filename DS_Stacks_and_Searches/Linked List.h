#include "Stdafx.h"
using namespace std;
#ifndef ORF
#define ORF else if
#endif
#ifdef _INC_STRING
	const std::string BLIST_NPP = "Error: Unhandle-able null pointer passed.";
	const std::string BLIST_ENL = "Error: An entry with that ID has not been listed.";
	const std::string BLIST_EAL = "Error: An entry with that ID is already in the list.";
	const std::string BLIST_OOB = "Error: Out of Bounds.";
	const std::string BLIST_LNS = "Error: The list has not been started yet.";
	const std::string BLIST_ERR = "Unknown bList error.";
#elif
	const int BLIST_NPP = 5;
	const int BLIST_ENL = 4;
	const int BLIST_EAL = 3;
	const int BLIST_OOB = 2
	const int BLIST_LNS = 1;
	const int BLIST_ERR = 0;
#endif

template<typename T> class LL;

template<typename T> class node;

template<typename T>
class node
{public:
	node(T &data)
	{	m_left = NULL;
		m_right= NULL;
		m_data = &data;
	}
	
	node(T* data)
	{	m_left = NULL;
		m_right= NULL;
		m_data = data;
	}

#ifdef DISPLAY_METHOD
	void Display()	{ m_data->DISPLAY_METHOD; }
#endif

	~node(){ delete m_data; }

private:
	node<T>* m_left;
	node<T>* m_right;
	T* m_data;

friend class LL<T>;
};


template<typename T>
class LL: public OrderedList<T>
{public:

	LL(bool no_repeats_ = true): no_repeats(no_repeats_)
		{ root = 0;	start = 0;	stop = 0;	N_items=0; }

	int Count()const { return N_items; }

	void Add(T* item)
	{	node<T>* p_top;
		if( N_items )
		{	p_top = Search(item);
			if ( *item < *(p_top->m_data) ) p_top->m_left = new node<T>(item);
			ORF( *item > *(p_top->m_data) ) p_top->m_right= new node<T>(item);
			ORF( no_repeats ) --N_items;	//negate the ++N_items later;
		  else/* *item ==*(p_top->m_data) */p_top->m_left = new node<T>(item);	
			if ( *item < *(start->m_data) ) start = p_top->m_left ;
			ORF( *item > *(stop ->m_data) ) stop  = p_top->m_right;
		}else 
		{	root = new node<T>(item);
			start= root;
			stop = root;
		}++N_items;
	}

	void Add(const T &item)	{ T* pointer = new T(item);	Add(pointer); }
	

#ifdef CELL_ID	

	node<T>* Find(string &tag)//--------------------Returns a specific node
	{	if (start == 0) return 0;			//Otherwise program will crash.
		int checks(0);
		node<T>* nptr = start;				//create a pointer to continually check against
		
		do{	if(nptr->m_data->CELL_ID == tag) return nptr;		//if found
			nptr = nptr->m_next;	}while(nptr != start);	//if not found

		return 0;							//if never found
	}


	T& operator[](string &tag)const { if (Find(tag)) return *(Find(tag) ->m_data); return false; }
						//I'm assuming modern compilers won't actually make Find run twice. 
#endif


	T& operator[](T &goal)	{ return *(Search(goal)->m_data); }
	/*T& operator[](int index)
	{	if (index++ > N_items) throw OOB;
		for(indesy = Begin(); index; --index) indesy.Next();
		return indesy.
	}*/

	node<T>* Search(const T &goal, node<T>* p_top = CAST(node<T>*, NNUL) )
	{	//CAST(const T, goal);
		if(  p_top == CAST(node<T>*, NNUL)) p_top = root;
		if( !p_top ) return NULL;
	
		Previous.Push(p_top);
		
		if ( goal > *(p_top->m_data) && p_top->m_right ) return Search(goal, p_top->m_right);
		ORF( goal < *(p_top->m_data) && p_top->m_left  ) return Search(goal, p_top->m_left );
		else return p_top;
	}node<T>* Search(const T* goal){ return Search(*goal, root); }



	void i_Remove(unsigned indX){Extract(indX);}
	void   Remove(const T& item){Extract(item);}
	void   Remove(node<T>* nptr){Extract(nptr);}

	T& i_Extract(unsigned indX)
	{	if (0 > indX||indX > N_items) throw BLIST_ENL;
		OrderedListIterator* nptr = Begin();
		for(int i(0); i < indX; ++i) nptr->Next();
		return Extract(nptr->noedy);
	}

	T& Extract(const T& item)	{ return Extract(Search(item)); }
	T& Extract(node<T>* nptr)	
	{	if (!nptr ) throw BLIST_NPP;
		T extracted = *(nptr->m_data);
		node<T>* successor;
		node<T>* s_parent = Previous.Peek();//PEEK not POP, ergo the <s_>
		if	( nptr == start ){ start= s_parent; s_parent->m_left = NULL; delete nptr;}	//If at start update
		ORF ( nptr == stop  ){ stop = s_parent; s_parent->m_right= NULL; delete nptr;}	//If at stop  update

		ORF ( nptr->m_right )
		{	
			successor = nptr->m_right;
			while (successor->m_left){ Previous.Push(successor);	successor = successor->m_left; }
			nptr->m_data = &Extract(successor);
			++N_items;
		}
		ORF ( nptr->m_left )
		{	s_parent = nptr;
			nptr = nptr->m_left;
			delete s_parent;
		}

		ORF ( nptr == s_parent->m_right) { s_parent->m_right= NULL; delete nptr; }
	   else/*(nptr == s_parent->m_left)*/{ s_parent->m_left = NULL; delete nptr; }

		--N_items;									//update N_items
		return extracted;						//Return the node data
	}

#ifdef DISPLAY_METHOD
	void Display_all()//Calls Cell.Display once for each city. Shares many elements with search routine.
	{if (N_items > 0){
		node<T>* nptr = start;			 //Create a temporary node 
		do{	nptr->m_data->DISPLAY_METHOD;//Call display
			nptr = nptr->m_next;		 //Go to the next node.
		} while( nptr != start );		 //While not at end.
	}}
#endif


	/*void Purge()
	{	int i = 0;
		node<T>* nptr = start;
		do {Extract(i++);
			nptr = nptr->m_next;
			nprt->m_prev->~node();
		} while (N_items > 0);
		start = 0;
		stop = 0;
	}*/

	class OLI: public OrderedListIterator
	{public:
		OLI(LL<T>* c):									Linked(c){ noedy = c.start; }
		OLI(LL<T>* c, node<T>* a, StackRA<node<T>*> B): Linked(c), noedy(a), m_Previous(B)
			{if(!a){ m_Previous.~StackRA(); throw BLIST_NPP; }}


		OLI(const OLI &oli): Linked(oli.Linked), noedy(oli.noedy), m_Previous(oli.m_Previous){}

		virtual bool HasNext	() const { if (noedy != Linked->stop) return true;  return false; }
		virtual bool HasPrevious() const { if ( m_Previous.Count( ) ) return true;  return false; }
			// Returns true if there is a next or Previous item respectively.

		virtual T & Next()		// Returns CURRENT item and advances iterator toward end.
		{	T* The_Data = noedy->m_data;//Save the return value.
			
			if (!HasNext()) noedy = Linked->start;
			ORF(noedy->m_right)
			{	m_Previous.Push(noedy);
				noedy = noedy->m_right;

				while (noedy->m_left)
				{	m_Previous.Push(noedy);
					noedy = noedy->m_left;		}
			}
			else
			{	node<T>* parent = m_Previous.Pop();

				while(noedy == parent->m_right);
				{	noedy = parent;
					parent = m_Previous.Pop();	}

				m_Previous.Push(parent);
				noedy = parent->m_right;

				while(noedy->m_left)
				{	m_Previous.Push(noedy);
					noedy = noedy->m_left;		}
			}
			
			return *The_Data;			//return, the next element does not matter
		}

#ifdef NOT
		virtual T & Previous()	// Returns Previous item and advances iterator toward beginning.
		{	if(!HasPrevious()) noedy = Linked->stop;
			else 
		}
#endif
		virtual T Remove()					{ return Linked->Extract(noedy); }
			// Removes item at current position, contracting the list.

	private:  LL<T>* Linked;
			node<T>* noedy;
	StackRA<node<T>*> m_Previous;
	};
	
	OrderedListIterator* Begin(				)	{ return new OLI( this, start, Previous ); }
		//\\ returns new iterator at beginning of list.

	OrderedListIterator* End (				)	{ return new OLI( this, stop , Previous ); }
		//\\ returns new iterator past end of list.		//Past?

	OrderedListIterator* Find(const T & target)	{ return new OLI( this, Search(target), Previous ); }
		//\\ returns new iterator at the item in the list, or NULL if not found.

private: 
	friend class OLI;
	OLI indesy;
	bool no_repeats;
	int N_items;
	StackRA<node<T>*> Previous;
	node<T>* root,* start,* stop;
};