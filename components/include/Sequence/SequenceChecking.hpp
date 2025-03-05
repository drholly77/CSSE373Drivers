#pragma once

//
// Checking Version for Sequence
// author: Dr. Holly
//


template <
	class T,
	class UncheckedSequence
>
class SequenceChecking1:
	public UncheckedSequence
{
	typedef UncheckedSequence SequenceOfT;
public:

//-----------------------------------------------------------------------

void add (Integer pos, T& x)
{
	// assert that 0 <= pos <= s.length
	if (pos < 0) {
		OutputDebugString (L"Operation: add\n");
		OutputDebugString (L"Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (pos > SequenceOfT::length ()) {
		OutputDebugString (L"Operation: add\n");
		OutputDebugString (L"Assertion failed: pos <= |s|\n");
		DebugBreak ();
	}	// end if 

	SequenceOfT::add (pos, x);
}	// add

//-----------------------------------------------------------------------

void remove (Integer pos, T& x)
{
	// assert that 0 <= pos < s.length
	if (pos < 0) {
		OutputDebugString (L"Operation: remove\n");
		OutputDebugString (L"Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (SequenceOfT::length () <= pos) {
		OutputDebugString (L"Operation: remove\n");
		OutputDebugString (L"Assertion failed: pos < |s|\n");
		DebugBreak ();
	}	// end if 

	SequenceOfT::remove (pos, x);
}	// remove

//-----------------------------------------------------------------------

void replaceEntry (Integer pos, T& x)
{
	// assert that 0 <= pos < s.length
	if (pos < 0) {
		OutputDebugString (L"Operation: replaceEntry\n");
		OutputDebugString (L"Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (SequenceOfT::length () <= pos) {
		OutputDebugString (L"Operation: replaceEntry\n");
		OutputDebugString (L"Assertion failed: pos < |s|\n");
		DebugBreak ();
	}	// end if 

	SequenceOfT::replaceEntry (pos, x);
}	// swapItem

//-----------------------------------------------------------------------

void split (Integer pos, SequenceChecking1& otherS)
{
	// assert that 0 <= pos <= s.length
	if (pos < 0) {
		OutputDebugString (L"Operation: split\n");
		OutputDebugString (L"Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (pos > SequenceOfT::length ()) {
		OutputDebugString (L"Operation: split\n");
		OutputDebugString (L"Assertion failed: pos <= |s|\n");
		DebugBreak ();
	}	// end if 

	SequenceOfT::split (pos, otherS);
}	// split

//-----------------------------------------------------------------------

T& entry (Integer pos)
{
	// assert that 0 <= pos < s.length
	if (pos < 0) {
		OutputDebugString (L"Operation: entry\n");
		OutputDebugString (L"Assertion failed: 0 <= pos\n");
		DebugBreak ();
	}	// end if 
	if (SequenceOfT::length () <= pos) {
		OutputDebugString (L"Operation: entry\n");
		OutputDebugString (L"Assertion failed: pos < |s|\n");
		DebugBreak ();
	}	// end if 

	return SequenceOfT::entry (pos);
}	// entry
};

