#pragma once

/*
	Checking Version of BoundedList
	Author: Dr. Holly
*/


template <
	class T,
	int maxLength,
	class UncheckedBoundedList
>
class BoundedListChecking1 :
	public UncheckedBoundedList
{
	typedef UncheckedBoundedList BoundedListOfT;
public:

//-------------------------------------------------------------------
	
void advance (void)
{
	// assert that right size > 0
	if (BoundedListOfT::rightLength () <= 0) {
		OutputDebugString(L"Operation: Advance\n");
		OutputDebugString(L"Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	BoundedListOfT::advance ();
}	// advance

//-------------------------------------------------------------------

void addRightFront(T& x)
{
	// assert that |self.left| + |self.right| + 1 <= maxLength
	if ((BoundedListOfT::leftLength() + BoundedListOfT::rightLength() + 1) > maxLength) {
		OutputDebugString(L"Operation: addRightFront\n");
		OutputDebugString(L"Assertion failed: |self.left| + |self.right| + 1 <= maxLength\n");
		DebugBreak();
	}	// end if 

	BoundedListOfT::addRightFront(x);
}	// addRightFront

//-------------------------------------------------------------------

void removeRightFront (T& x)
{
	// assert that right size > 0
	if (BoundedListOfT::rightLength () <= 0) {
		OutputDebugString(L"Operation: removeRightFront\n");
		OutputDebugString(L"Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	BoundedListOfT::removeRightFront (x);
}	// removeRightFront

//-------------------------------------------------------------------

T& rightFront (void)
{
	// assert that right size > 0
	if (BoundedListOfT::rightLength () <= 0) {
		OutputDebugString(L"Operation: rightFront\n");
		OutputDebugString(L"Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	return (BoundedListOfT::rightFront());
}	// rightFront

void replaceRightFront (T& x)
{
	// assert that right size > 0
	if (BoundedListOfT::rightLength () <= 0) {
		OutputDebugString(L"Operation: replaceRightFront\n");
		OutputDebugString(L"Assertion failed: |s.right| > 0\n");
		DebugBreak ();
	}	// end if 

	BoundedListOfT::replaceRightFront (x);
}

void swapRights(BoundedListOfT& otherS)
{
	// assert that |self.left| + |otherS.right| <= maxLength  and
    //             |otherS.left| + |self.right| <= maxLength
	if ((BoundedListOfT::leftLength() + otherS.rightLength()) > maxLength) {
		OutputDebugString(L"Operation: swapRights\n");
		OutputDebugString(L"Assertion failed: |self.left| + |otherS.right| <= maxLength\n");
		DebugBreak();
	}	// end if 
	if ((otherS.leftLength() + BoundedListOfT::rightLength()) > maxLength) {
		OutputDebugString(L"Operation: swapRights\n");
		OutputDebugString(L"Assertion failed: |otherS.left| + |self.right| <= maxLength\n");
		DebugBreak();
	}	// end if 

	BoundedListOfT::swapRights(otherS);
}

};



