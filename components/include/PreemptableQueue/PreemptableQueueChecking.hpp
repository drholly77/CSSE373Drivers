#pragma once
/*
	Checking Version of PreemptableQueue
	Author: Dr. Holly
*/

template <class T, class UncheckedPreemptableQueue>
class PreemptableQueueChecking1: public UncheckedPreemptableQueue
{
private:
	typedef UncheckedPreemptableQueue PreemptableQueueOfT;
public:

//-------------------------------------------------------------------

void dequeue (T& x)
{
	// assert that length > 0
	if (PreemptableQueueOfT::length() <= 0) {
		OutputDebugString (L"Operation: dequeue\n");
		OutputDebugString (L"Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	PreemptableQueueOfT::dequeue (x);
}	// dequeue

//-------------------------------------------------------------------

T& front(void)
{
	// assert that length > 0
	if (PreemptableQueueOfT::length () <= 0) {
		OutputDebugString (L"Operation: front\n");
		OutputDebugString (L"Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	return PreemptableQueueOfT::front();
}	// front

//-------------------------------------------------------------------

void replaceFront(T& x)
{
	// assert that length > 0
	if (PreemptableQueueOfT::length () <= 0) {
		OutputDebugString (L"Operation: replaceFront\n");
		OutputDebugString (L"Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	PreemptableQueueOfT::replaceFront(x);
}	// replaceFront
};

