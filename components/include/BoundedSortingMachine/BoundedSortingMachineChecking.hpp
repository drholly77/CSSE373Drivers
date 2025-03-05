#pragma once

/*
	Checking Version of BoundedSortingMachine
	Author: Dr. Holly
*/

template <
	class T,
	class UncheckedBoundedSortingMachine
>
class BoundedSortingMachineChecking1:
	public UncheckedBoundedSortingMachine
{
	typedef UncheckedBoundedSortingMachine BoundedSortingMachineOfT;
public:

//-------------------------------------------------------------------

void add (T& x)
{
	// assert that sorting machine is in InsertionPhase
	if (!BoundedSortingMachineOfT::isInInsertionMode()) {
		OutputDebugString(L"Operation: add\n");
		OutputDebugString(L"Assertion failed: isInInsertionMode()\n");
		DebugBreak();
	}	// end if 

	// assert that sorting machine size is not at capacity
	if (BoundedSortingMachineOfT::remainingCapacity() == 0) {
		OutputDebugString(L"Operation: add\n");
		OutputDebugString(L"Assertion failed: |self.contents| < self.maxSize\n");
		DebugBreak();
	}	// end if 

	BoundedSortingMachineOfT::add(x);
}	// add

//-------------------------------------------------------------------

void changeToExtractionMode (void)
{
	// assert that sorting machine is in InsertionPhase
	if (!BoundedSortingMachineOfT::isInInsertionMode()) {
		OutputDebugString(L"Operation: changeToExtractionMode\n");
		OutputDebugString(L"Assertion failed: isInInsertionMode()\n");
		DebugBreak();
	}	// end if 

	BoundedSortingMachineOfT::changeToExtractionMode();
}	// changeToExtractionMode


//-------------------------------------------------------------------

void removeFirst (T& x)
{
	// assert that sorting machine is not in InsertionPhase
	if (BoundedSortingMachineOfT::isInInsertionMode()) {
		OutputDebugString(L"Operation: removeFirst\n");
		OutputDebugString(L"Assertion failed: !BoundedSortingMachineOfT::isInInsertionMode()\n");
		DebugBreak();
	}	// end if 

	// assert that size of sorting machine > 0
	if (BoundedSortingMachineOfT::size() <= 0) {
		OutputDebugString(L"Operation: removeFirst\n");
		OutputDebugString(L"Assertion failed: size() > 0\n");
		DebugBreak();
	}	// end if 

	BoundedSortingMachineOfT::removeFirst(x);
}	// removeFirst
};



