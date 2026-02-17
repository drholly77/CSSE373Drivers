#pragma once
/*
	Checking Version of BoundedQueue
	Author: Dr. Holly
*/

template <class T, int maxLength, class UncheckedBoundedQueue>
class BoundedQueueChecking1: public UncheckedBoundedQueue
{
private:
	typedef UncheckedBoundedQueue BoundedQueueOfT;
public:

	//-------------------------------------------------------------------

	void enqueue (T& x)
	{
		// assert that length < maxLength
		if (BoundedQueueOfT::length() + 1 > maxLength) {
			OutputDebugString(L"Operation: enqueue\n");
			OutputDebugString(L"Assertion failed: |q| + 1 <= maxLength\n");
			DebugBreak();
		}	// end if 

		BoundedQueueOfT::enqueue(x);
	}	// enqueue

//-------------------------------------------------------------------

void dequeue (T& x)
{
	// assert that length > 0
	if (BoundedQueueOfT::length() <= 0) {
		OutputDebugString(L"Operation: dequeue\n");
		OutputDebugString(L"Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	BoundedQueueOfT::dequeue (x);
}	// dequeue

//-------------------------------------------------------------------

T& front(void)
{
	// assert that length > 0
	if (BoundedQueueOfT::length () <= 0) {
		OutputDebugString(L"Operation: front\n");
		OutputDebugString(L"Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	return BoundedQueueOfT::front();
}	// front

//-------------------------------------------------------------------

void replaceFront(T& x)
{
	// assert that length > 0
	if (BoundedQueueOfT::length () <= 0) {
		OutputDebugString(L"Operation: replaceFront\n");
		OutputDebugString(L"Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	BoundedQueueOfT::replaceFront(x);
}	// replaceFront
};

