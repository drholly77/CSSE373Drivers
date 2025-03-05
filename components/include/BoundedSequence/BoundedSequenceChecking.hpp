#pragma once

//
// checking Version for BoundedSequence
// author: Dr. Holly
//


template <
	class T,
	int maxLength,
	class UncheckedBoundedSequence
>
class BoundedSequenceChecking1 :
	public UncheckedBoundedSequence
{
	typedef UncheckedBoundedSequence BoundedSequenceOfT;
public:

	//-----------------------------------------------------------------------

	void add(
		Integer pos,
		T& x
		)
	{
		// assert that |self| + 1 <= maxLength
		if (BoundedSequenceOfT::length() + 1 > maxLength) {
			OutputDebugString(L"Operation: add\n");
			OutputDebugString(L"Assertion failed: |self| + 1 <= maxLength\n");
			DebugBreak();
		}	// end if 
		// assert that 0 <= pos <= s.length
		if (pos < 0) {
			OutputDebugString(L"Operation: add\n");
			OutputDebugString(L"Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (pos > BoundedSequenceOfT::length()) {
			OutputDebugString(L"Operation: add\n");
			OutputDebugString(L"Assertion failed: pos <= |s|\n");
			DebugBreak();
		}	// end if 

		BoundedSequenceOfT::add(pos, x);
	}	// add

	//-----------------------------------------------------------------------

	void remove(
		Integer pos,
		T& x
		)
	{
		// assert that 0 <= pos < s.length
		if (pos < 0) {
			OutputDebugString(L"Operation: remove\n");
			OutputDebugString(L"Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (BoundedSequenceOfT::length() <= pos) {
			OutputDebugString(L"Operation: remove\n");
			OutputDebugString(L"Assertion failed: pos < |s|\n");
			DebugBreak();
		}	// end if 

		BoundedSequenceOfT::remove(pos, x);
	}	// remove

	//-----------------------------------------------------------------------

	void replaceEntry(
		Integer pos,
		T& x
		)
	{
		// assert that 0 <= pos < s.length
		if (pos < 0) {
			OutputDebugString(L"Operation: replaceEntry\n");
			OutputDebugString(L"Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (BoundedSequenceOfT::length() <= pos) {
			OutputDebugString(L"Operation: replaceEntry\n");
			OutputDebugString(L"Assertion failed: pos < |s|\n");
			DebugBreak();
		}	// end if 

		BoundedSequenceOfT::replaceEntry(pos, x);
	}	// swapItem

	//-----------------------------------------------------------------------

	void split(
		Integer pos,
		BoundedSequenceChecking1& otherS
		)
	{
		// assert that 0 <= pos <= s.length
		if (pos < 0) {
			OutputDebugString(L"Operation: split\n");
			OutputDebugString(L"Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (pos > BoundedSequenceOfT::length()) {
			OutputDebugString(L"Operation: split\n");
			OutputDebugString(L"Assertion failed: pos <= |s|\n");
			DebugBreak();
		}	// end if 

		BoundedSequenceOfT::split(pos, otherS);
	}	// split

	//-----------------------------------------------------------------------

	T& entry(Integer pos)
	{
		// assert that 0 <= pos < s.length
		if (pos < 0) {
			OutputDebugString(L"Operation: entry\n");
			OutputDebugString(L"Assertion failed: 0 <= pos\n");
			DebugBreak();
		}	// end if 
		if (BoundedSequenceOfT::length() <= pos) {
			OutputDebugString(L"Operation: entry\n");
			OutputDebugString(L"Assertion failed: pos < |s|\n");
			DebugBreak();
		}	// end if 

		return (BoundedSequenceOfT::entry(pos));
	}	// entry

		//-----------------------------------------------------------------------

	void append(BoundedSequenceChecking1& sToAppend)
	{
		// assert that |self| + |sToAppend| <= maxLength
		if ((BoundedSequenceOfT::length() + sToAppend.length()) > maxLength) {
			OutputDebugString(L"Operation: append\n");
			OutputDebugString(L"Assertion failed: |self| + |sToAppend| <= maxLength\n");
			DebugBreak();
		}	// end if 
		BoundedSequenceOfT::append(sToAppend);
	}	// append

};

