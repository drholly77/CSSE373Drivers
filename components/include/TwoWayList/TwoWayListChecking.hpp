#pragma once

/*
	Checking Version of TwoWayList
	Author: Dr. Holly
*/

template <
	class T,
	class UncheckedTwoWayList
>
class TwoWayListChecking1:
	public UncheckedTwoWayList
{
	typedef UncheckedTwoWayList TwoWayListOfT;
public:

//-------------------------------------------------------------------

void advance (void)
{
	// assert that right size > 0
	if (TwoWayListOfT::rightLength() <= 0) {
		OutputDebugString (L"Operation: advance\n");
		OutputDebugString (L"Assertion failed: |s.right| > 0\n");
		DebugBreak();
	}	// end if 

	TwoWayListOfT::advance();
}	// advance

//-------------------------------------------------------------------

void retreat (void)
{
	// assert that left size > 0
	if (TwoWayListOfT::leftLength() <= 0) {
		OutputDebugString (L"Operation: retreat\n");
		OutputDebugString (L"Assertion failed: |s.left| > 0\n");
		DebugBreak();
	}	// end if 

	TwoWayListOfT::retreat();
}	// retreat

//-------------------------------------------------------------------

void removeRightFront (T& x)
{
	// assert that right size > 0
	if (TwoWayListOfT::rightLength() <= 0) {
		OutputDebugString (L"Operation: removeRightFront\n");
		OutputDebugString (L"Assertion failed: |s.right| > 0\n");
		DebugBreak();
	}	// end if 

	TwoWayListOfT::removeRightFront(x);
}	// removeRightFront

//-------------------------------------------------------------------

T& rightFront (void)
{
	// assert that right size > 0
	if (TwoWayListOfT::rightLength() <= 0) {
		OutputDebugString (L"Operation: rightFront\n");
		OutputDebugString (L"Assertion failed: |s.right| > 0\n");
		DebugBreak();
	}	// end if 

	return TwoWayListOfT::rightFront();
}	// rightFront

//-------------------------------------------------------------------

void replaceRightFront (T& x)
{
	// assert that right size > 0
	if (TwoWayListOfT::rightLength() <= 0) {
		OutputDebugString (L"Operation: replaceRightFront\n");
		OutputDebugString (L"Assertion failed: |s.right| > 0\n");
		DebugBreak();
	}	// end if 

	TwoWayListOfT::replaceRightFront(x);
}	// replaceRightFront
};

