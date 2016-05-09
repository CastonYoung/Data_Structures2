#include "Stdafx.h"


inline void Flush(){ cin.ignore(cin.rdbuf()->in_avail()); }
void Clear_Screen();/*M. T. Geer. Nov 27, 2011*/
		

//void Display(LL<TYPE> &The_List)
	//{ for (int i(0); i < The_List.Count(); i++) cout<< The_List[i] << endl; }

bool Test(LL<TYPE> &The_List)
{	LL<TYPE>* La_list = &The_List;
	LL<TYPE>::OLI indesies(La_list/*, The_List.Begin()*/);
	//for (i(0); i < The_List.Count(); i++) if(The_List[i] != (int)'n'-i) return false;
	return true ;
}

int main()
{try{
	bool pass(true), ErrMes(false);
	int test(0);
	StackRA<int> Array_Stack;
	/*Begin Test*/
		Array_Stack.Push(5);
		cout<< Array_Stack.Pop();
		Array_Stack.Push(3);
		Array_Stack.Push(2);
		Array_Stack.Push(1);
		while(3 >= ++test && test == Array_Stack.Peek())	Array_Stack.Pop();
		try{ cout<< Array_Stack.Pop();	return 1; }
			catch(string except){ if (except != BLIST_LNS) throw except; }
	/*End Test*/


	LL<TYPE> The_List(false);
	/*Begin Test*/
		char ey('a'), bee('b'), see('c'), dee('d'), ee('e'), ef('f'), jee('g'), eych('h'), aye('i'), jay('j'),
			kay('k'), el('l'), em('m'), en('n'), uwh('o'), pee('p'), que('q'), ar('r'), es('s'), tee('t'),
			yoo('u'), vee('v'), dubelyoo('w'), ex('x'), whie('y'), and('&'), zee('z');
		//char em('m');
		//Step 1 Test pre-start errors.
		
		//Display(The_List);


		//Step 2 Make a list.
		The_List.Add( 'g' );	The_List.Add( 'h' );	The_List.Add( 'f' );
		The_List.Add( 'i' );	The_List.Add( 'e' );	The_List.Add( 'd' );
		The_List.Add( 'j' );	The_List.Add( 'k' );	The_List.Add( 'c' );
		The_List.Add( 'b' );	The_List.Add( 'a' );	The_List.Add( 'l' );
		The_List.Add( 'm' );	The_List.Add( 'n' );	The_List.Add( 'm' );


		//Step 3 Test functions.
		if(The_List.Extract(em) != 'm')
			{ cout<< "Remove Fail\n";	pass =false; }


		
		//	try { The_List.Remove(19); }
		//		catch(string exe){ if(exe == ENL) ErrMes = true; }
		//	if (!ErrMes){	cout<< "Remove Error Message fail.\n";	pass =false;	}


			//Step 5 Final Test
			//Display(The_List);
			if (Test(The_List) && pass) cout<< "Test PASSED.";
			else cout<< "Test failed.";
		/*End Test*/

}catch(string except){ cout<< except;}
DEBUGPAUSE;
return 0;
}