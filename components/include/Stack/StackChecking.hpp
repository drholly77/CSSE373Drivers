#pragma once

/*
	Checking Version of Stack
	Author: Dr. Holly
*/

template <class T, class UncheckedStack>
class StackChecking1 : public UncheckedStack
{
private:
	typedef UncheckedStack StackOfT;
public:

void pop (T& x)
{
	// assert that length is > 0
	if (StackOfT::length () <= 0) {
		OutputDebugString (L"Operation: pop\n");
		OutputDebugString (L"Assertion failed: |s| > 0\n");
		DebugBreak ();
	}	// end if 

	StackOfT::pop (x);
}	// pop

//-------------------------------------------------------------------

void replaceTop (T& x)
{
	// assert that length is > 0
	if (StackOfT::length () <= 0) {
		OutputDebugString (L"Operation: replaceTop\n");
		OutputDebugString (L"Assertion failed: |s| > 0\n");
		DebugBreak ();
	}	// end if 

	StackOfT::replaceTop (x);
}	// replaceTop

//-------------------------------------------------------------------

T& top (void)
{
	// assert that length > 0
	if (StackOfT::length () <= 0) {
		OutputDebugString (L"Operation: top\n");
		OutputDebugString (L"Assertion failed: |s| > 0\n");
		DebugBreak ();
	}	// end if 

	return (StackOfT::top());
}	// top
};

