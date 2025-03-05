#pragma once
/*
	Checking Version for QueueOfText
	Author: Dr. Holly
*/

template <class QueueOfT>
class QueueOfTextChecking1: public QueueOfT
{
public:

//-------------------------------------------------------------------

void dequeue (Text& x)
{
	// assert that length > 0
	if (QueueOfT::length() <= 0) {
		OutputDebugString (L"Operation: dequeue\n");
		OutputDebugString (L"Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	QueueOfT::dequeue (x);
}	// dequeue

//-------------------------------------------------------------------

Text& front(void)
{
	// assert that length > 0
	if (QueueOfT::length () <= 0) {
		OutputDebugString (L"Operation: front\n");
		OutputDebugString (L"Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	return QueueOfT::front();
}	// front

//-------------------------------------------------------------------

void replaceFront(Text& x)
{
	// assert that length > 0
	if (QueueOfT::length () <= 0) {
		OutputDebugString (L"Operation: replaceFront\n");
		OutputDebugString (L"Assertion failed: |q| > 0\n");
		DebugBreak ();
	}	// end if 

	QueueOfT::replaceFront(x);
}	// replaceFront
};

