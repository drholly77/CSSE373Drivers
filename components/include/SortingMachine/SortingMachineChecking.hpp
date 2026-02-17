#pragma once

/*
	Checking Version of SortingMachine
	Author: Dr. Holly
*/

template <class T, class UncheckedSortingMachine>
class SortingMachineChecking1: public UncheckedSortingMachine
{
private:
	typedef UncheckedSortingMachine SortingMachineOfT;
public:

//-------------------------------------------------------------------

void add (T& x)
{
	// assert that sorting machine is in InsertionPhase
	if (!SortingMachineOfT::isInInsertionMode()) {
		OutputDebugString (L"Operation: add\n");
		OutputDebugString (L"Assertion failed: isInInsertionMode()\n");
		DebugBreak();
	}	// end if 

	SortingMachineOfT::add(x);
}	// add

//-------------------------------------------------------------------

void changeToExtractionMode (void)
{
	// assert that sorting machine is in InsertionPhase
	if (!SortingMachineOfT::isInInsertionMode()) {
		OutputDebugString (L"Operation: changeToExtractionMode\n");
		OutputDebugString (L"Assertion failed: isInInsertionMode()\n");
		DebugBreak();
	}	// end if 

	SortingMachineOfT::changeToExtractionMode();
}	// changeToExtractionMode


//-------------------------------------------------------------------

void removeFirst (T& x)
{
	// assert that sorting machine is not in InsertionPhase
	if (SortingMachineOfT::isInInsertionMode()) {
		OutputDebugString (L"Operation: removeFirst\n");
		OutputDebugString (L"Assertion failed: !SortingMachineOfT::isInInsertionMode()\n");
		DebugBreak();
	}	// end if 

	// assert that size of sorting machine > 0
	if (SortingMachineOfT::size() <= 0) {
		OutputDebugString (L"Operation: removeFirst\n");
		OutputDebugString (L"Assertion failed: size() > 0\n");
		DebugBreak();
	}	// end if 

	SortingMachineOfT::removeFirst(x);
}	// removeFirst
};



