#pragma once

//
// Checking version of BoundedSet 
// author: Dr. Holly
//

template <class T, class UncheckedBoundedSet>
class BoundedSetChecking1:	public UncheckedBoundedSet
{
private:
	typedef UncheckedBoundedSet BoundedSetOfT;
public:

//-------------------------------------------------------------------

void add (T& x)
{
	// assert that s is not full 
	if ((BoundedSetOfT::remainingCapacity() == 0)) {
		OutputDebugString(L"Operation: add\n");
		OutputDebugString(L"Assertion failed: |self| < maxSize\n");
		DebugBreak();
	}	// end if 
	// assert that s does not contain x
	if (BoundedSetOfT::contains(x)) {
		OutputDebugString (L"Operation: add\n");
		OutputDebugString (L"Assertion failed: self does not contain x\n");
		DebugBreak ();
	}	// end if 

	BoundedSetOfT::add (x);
}	// add

//-------------------------------------------------------------------

void remove (T& xFromClient, T& xFromSet)
{
	// assert that s contains xFromClient
	if (!BoundedSetOfT::contains(xFromClient)) {
		OutputDebugString (L"Operation: remove\n");
		OutputDebugString (L"Assertion failed: self contains xFromClient\n");
		DebugBreak ();
	}	// end if 

	BoundedSetOfT::remove (xFromClient, xFromSet);
}	// remove

//-------------------------------------------------------------------

void removeAny (T& x)
{
	// assert |self| > 0
	if (BoundedSetOfT::size () <= 0) {
		OutputDebugString (L"Operation: removeAny\n");
		OutputDebugString (L"Assertion failed: |self| > 0\n");
		DebugBreak ();
	}	// end if 

	BoundedSetOfT::removeAny (x);
}	// removeAny
};
