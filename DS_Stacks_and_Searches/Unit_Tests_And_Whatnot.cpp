#include "Stdafx.h"


inline void Flush(){ cin.ignore(cin.rdbuf()->in_avail()); }
void Clear_Screen();/*M. T. Geer. Nov 27, 2011*/

void Add(LL<TYPE> &The_List, TYPE data, bool alt)
{	if (alt)The_List.Add ( data );
	else	The_List.bbA ( data );	}
		
void Add_after(LL<TYPE> &The_List, int side, TYPE data, bool alt)
{	if (alt) The_List.Insert_after( data, side );	 //side = number of the pr(e)(o)ceding node.
	else	 The_List.Insert	  ( data, side );	}//data = what to add.

void Display(LL<TYPE> &The_List)
	{ for (int i(0); i < The_List.Count(); i++) cout<< The_List.Get(i) << endl; }

bool Test(LL<TYPE> &The_List)
	{ for (int i(0); i < The_List.Count(); i++) if(The_List.Get(i) != 14-i) return false;
	/*											else					*/	return true ; }

int main()
{try{
	bool pass(true), ErrMes(false);
	int test(0);
	char(2);
	StackRA<int> Array_Stack;
	/*Begin Test*/
		Array_Stack.Push(5);
		cout<< Array_Stack.Pop();
		Array_Stack.Push(3);
		Array_Stack.Push(2);
		Array_Stack.Push(1);
		while(3 >= ++test && test == Array_Stack.Peek())	Array_Stack.Pop();
		try{ cout<< Array_Stack.Pop();	return 1; }
			catch(string except){ if (except != LNS) throw except; }
	/*End Test*/


	LL<TYPE> The_List;
	/*Begin Test*/

			cout<<endl<< "Running Linked List Unit test" << endl;

			//Step 1 Test pre-start errors.
			try { Add_after(The_List, 1, 5, 0); } catch(string exe)
				{ if(exe == LNS) ErrMes = true; }
			if (!ErrMes){	cout<< "Add next to Error message fail.\n";	pass = false;	}
			ErrMes = false;
		
			Display(The_List);


			//Step 2 Make a list.
			Add(The_List, 7, false);	Add(The_List, 8,  true);
			Add(The_List, 6, false);	Add(The_List, 9,  true);
			Add(The_List, 5, false);	Add(The_List, 4, false);
			Add(The_List, 10, true);	Add(The_List, 11, true);
			Add(The_List, 3, false);	Add(The_List, 2, false);
			Add(The_List, 1, false);	Add(The_List, 12, true);
			Add(The_List, 13, true);	Add(The_List, 13, true);


			//Step 3 Test functions.
			Add_after(The_List, 0, 14, false);
			Add_after(The_List, 14, 0, true );
			if(The_List.Extract(2) != 13)
				{ cout<< "Remove Fail\n";	pass =false; }


			//Step 4 Test Error messages.
			try { Add_after(The_List, 20, 5, 0); } catch(string exe)
				{ if (exe == ENL) ErrMes = true; }
			if (!ErrMes){	cout<< "Append Error Message fail.\n";	pass =false;	}
			ErrMes =false;
		
			try {The_List.Remove(19);			} catch(string exe)
				{ if(exe == ENL) ErrMes = true; }
			if (!ErrMes){	cout<< "Remove Error Message fail.\n";	pass =false;	}


			//Step 5 Final Test
			Display(The_List);
			if (Test(The_List) && pass) cout<< "Test PASSED.";
			else cout<< "Test failed.";
		/*End Test*/

}catch(string except){; cout<< except;}
DEBUGPAUSE;
return 0;
}