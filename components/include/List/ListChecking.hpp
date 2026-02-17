#pragma once

/*
	Checking Version of List
	Author: Dr. Holly
*/

template <class T, class UnchedkedList>
class ListChecking1: public UnchedkedList
{
private:
	typedef UnchedkedList ListOfT;
public:

//-------------------------------------------------------------------
	
void advance (void)
{
	// assert that right size > 0
	if (ListOfT::rightLength () <= 0) {
		OutputDebugString (L"Operation: Advance\n");
		OutputDebugString (L"Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	ListOfT::advance ();
}	// advance

//-------------------------------------------------------------------

void removeRightFront (T& x)
{
	// assert that right size > 0
	if (ListOfT::rightLength () <= 0) {
		OutputDebugString (L"Operation: removeRightFront\n");
		OutputDebugString (L"Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	ListOfT::removeRightFront (x);
}	// removeRightFront

//-------------------------------------------------------------------

T& rightFront (void)
{
	// assert that right size > 0
	if (ListOfT::rightLength () <= 0) {
		OutputDebugString (L"Operation: rightFront\n");
		OutputDebugString (L"Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	return (ListOfT::rightFront());
}	// rightFront

void replaceRightFront (T& x)
{
	// assert that right size > 0
	if (ListOfT::rightLength () <= 0) {
		OutputDebugString (L"Operation: replaceRightFront\n");
		OutputDebugString (L"Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	ListOfT::replaceRightFront (x);
}
};



