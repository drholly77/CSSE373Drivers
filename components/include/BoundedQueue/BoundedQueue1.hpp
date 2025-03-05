#pragma once
#include "BoundedQueue/BoundedQueueKernel.hpp"
#include "StaticArray\StaticArray1.hpp"

/*
	Realization of BoundedQueue using StaticArray
	Author: Dr. Holly
*/


//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, int maxLength>
class BoundedQueue1 : public StdOps<BoundedQueue1<T, maxLength>>, public BoundedQueueKernel<T, maxLength>
{
public: // standard Operations
	BoundedQueue1();
	BoundedQueue1(const BoundedQueue1& s) = delete;
	~BoundedQueue1();
	void clear(void);
	void transferFrom(BoundedQueue1& source);
	BoundedQueue1& operator =(BoundedQueue1& rhs);

	// BoundedQueue1 Specific Operations
	void enqueue(T& x);
	void dequeue(T& x);
	void replaceFront(T& x);
	T& front(void);
	Integer length(void);
	Integer remainingCapacity (void);

	friend wostream& operator << <T, maxLength>(wostream &os, BoundedQueue1<T, maxLength>& q);
	//! updates os
	//! restores q

private: // internal representation
	
	enum { lowerBound = 0, upperBound = (maxLength - 1) };
	typedef StaticArray1 <T, lowerBound, upperBound> ArrayOfT;

	ArrayOfT contents;
	Integer currentLength;

	// correspondence s = IteratedConcatenation(z:Integer 0 <= z < currentLength, <contents(z)>)

	// convention 0 <= currentLength < maxLength

private: // local operations
	void displayRep(wostream &os);
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedQueue1<T, maxLength>::displayRep(wostream &os)
//! ensures: contents = #contents  and  
//!          currentLength = #currentLength  and  
//!          maxLength = #maxLength  and
//!          the values for each data member (contents, currentLength, maxLength) are displayed
{
	os << endl;
	os << "     contents: " << contents << endl;
	os << "currentLength: " << currentLength << endl;
	os << "    maxLength: " << maxLength << endl;
} // displayRep

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T, int maxLength>
BoundedQueue1<T, maxLength>::BoundedQueue1 ()
{
}	// BoundedQueue1

//-----------------------------------------------------------------------

template <class T, int maxLength>
BoundedQueue1<T, maxLength>::~BoundedQueue1 ()
{
}	// ~BoundedQueue1

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedQueue1<T, maxLength>::transferFrom (BoundedQueue1& source)
{
	contents.transferFrom(source.contents);
	currentLength.transferFrom(source.currentLength);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, int maxLength>
BoundedQueue1<T, maxLength>& BoundedQueue1<T, maxLength>::operator = (BoundedQueue1& rhs)
{
	contents = rhs.contents;
	currentLength = rhs.currentLength;
	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedQueue1<T, maxLength>::clear (void)
{
	contents.clear();
	currentLength.clear();
}	// clear

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedQueue1<T, maxLength>::enqueue (T& x)
{
	contents[currentLength].transferFrom(x);
	currentLength++;
}	// enqueue

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedQueue1<T, maxLength>::dequeue(T& x)
{
	static Integer locationZero = 0;

	x.transferFrom(contents[locationZero]);
	for (int k = 0, z = (currentLength - 1); k < z; k++) {
		contents[k].transferFrom(contents[k + 1]);
	} // end for
	currentLength--;
}	// dequeue

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedQueue1<T, maxLength>::replaceFront (T& x)
{
	static Integer locationZero = 0;
	T temp;

	temp.transferFrom(contents[locationZero]);
	contents[locationZero].transferFrom(x);
	x.transferFrom(temp);
}	// replaceFront

//-----------------------------------------------------------------------

template <class T, int maxLength>
T& BoundedQueue1<T, maxLength>::front (void)
{
	static Integer locationZero = 0;

	return contents[locationZero];
}  // front

//-----------------------------------------------------------------------

template <class T, int maxLength>
Integer BoundedQueue1<T, maxLength>::length (void)
{
	return (currentLength);
}	// length

//-----------------------------------------------------------------------

template <class T, int maxLength>
Integer BoundedQueue1<T, maxLength>::remainingCapacity(void)
{
	return (maxLength - currentLength);
}	// remainingCapacity

//-----------------------------------------------------------------------

template <class T, int maxLength>
wostream& operator<< (wostream &os, BoundedQueue1<T, maxLength>& q)
{
#ifdef NDEBUG
	os << L"<";
	for (int i = 0, z = q.length(), lastItem = z - 1; i < z; i++) {
		T x;

		q.dequeue(x);
		os << x;
		q.enqueue(x);
		if (i < lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L">";
#else
	q.displayRep(os);
#endif
	return (os);
} // operator<<



