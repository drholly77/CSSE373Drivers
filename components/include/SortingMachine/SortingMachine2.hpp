#pragma once
//
// exchange Sort Realization of SortingMachineTemplate using Queue
// author: Dr. Holly
//

#include "SortingMachine/SortingMachineKernel.hpp"
#include "Queue\Queue1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
class SortingMachine2 : public StdOps<SortingMachine2<T, areOrdered>>, SortingMachineKernel<T>
{
public: // standard Operations
	SortingMachine2 ();
	SortingMachine2(const SortingMachine2& s) = delete;
	~SortingMachine2 ();
	void clear (void);
	void transferFrom(SortingMachine2& source);
	SortingMachine2& operator = (SortingMachine2& rhs);

	// SortingMachine2 Specific Operations
	void add (T& x);
	void changeToExtractionMode (void);
	void removeFirst (T& x);
	Integer size (void);
	Boolean isInInsertionMode (void);

	friend wostream & operator<< <T, areOrdered>(wostream &os, SortingMachine2& s);
	//! updates os
	//! restores s

private: // representation
	typedef Queue1 <T> QueueOfT;

	Boolean insertionMode;
	QueueOfT itemKeeper;

private: // local Operations
	void split (QueueOfT& q, QueueOfT& h1, QueueOfT& h2);
	void join (QueueOfT& q, QueueOfT& h1, QueueOfT& h2);
	void mergeSort (QueueOfT& q);
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//----------------------------------------------------------------
// local Operations
//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine2<T, areOrdered>::split (QueueOfT& q, QueueOfT& h1, QueueOfT& h2)
{
	for (int i = 0, z = (q.length() / 2); i < z; i++) {
		T x;

		q.dequeue(x);
		h1.enqueue(x);
	} // end for
	h2.transferFrom(q);
} // split

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine2<T, areOrdered>::join (QueueOfT& q, QueueOfT& h1, QueueOfT& h2)
{
	q.clear();
	while (h1.length() > 0 && h2.length() > 0) {
		T x;

		if (areOrdered(h1.front(), h2.front())) {
			h1.dequeue(x);
		} else {
			h2.dequeue(x);
		} // end if
		q.enqueue(x);
	} // end while

	if (h2.length() > 0) {
		h1.transferFrom(h2);
	} // end if

	for (int i = 0, z = h1.length(); i < z; i++) {
		T x;

		h1.dequeue(x);
		q.enqueue(x);
	} // end for
} // join

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine2<T, areOrdered>::mergeSort (QueueOfT& q)
{
	if (q.length() > 1) {
		QueueOfT h1, h2;

		split(q, h1, h2);
		mergeSort(h1);
		mergeSort(h2);
		join(q, h1, h2);
	} // end if
}

//----------------------------------------------------------------
// exported Operations
//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
SortingMachine2<T, areOrdered>::SortingMachine2 ()
{
	insertionMode = true;
}	// SortingMachine2

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
SortingMachine2<T, areOrdered>::~SortingMachine2 ()
{
}	// ~SortingMachine2

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine2<T, areOrdered>::transferFrom(SortingMachine2& source)
{
	insertionMode.transferFrom(source.insertionMode);
	itemKeeper.transferFrom(source.itemKeeper);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
SortingMachine2<T, areOrdered>&
SortingMachine2<T, areOrdered>::operator = (SortingMachine2& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	return (*this);
} // operator =

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine2<T, areOrdered>::clear (void)
{
	itemKeeper.clear();
	insertionMode = true;
}	// clear

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine2<T, areOrdered>::add (T& x)
{
	itemKeeper.enqueue(x);
}	// add

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine2<T, areOrdered>::changeToExtractionMode (void)
{
	mergeSort(itemKeeper);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine2<T, areOrdered>::removeFirst (T& x)
{
	itemKeeper.dequeue(x);
}	// removeFirst

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Integer SortingMachine2<T, areOrdered>::size (void)
{
   return (itemKeeper.length());
}	// size

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Boolean SortingMachine2<T, areOrdered>::isInInsertionMode (void)
{
   return (insertionMode);
}	// isInInsertionMode

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
wostream & operator<<(wostream &os, SortingMachine2<T, areOrdered>& sm)
{
	Boolean inInsertionPhase;
	SortingMachine2<T, areOrdered> temp;

	inInsertionPhase = sm.isInInsertionMode();
	if (inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if
	os << L"({";
	for (int i = 0, z = sm.size(), lastItem = z - 1; i < z; i++) {
		T x;

		sm.removeFirst(x);
		os << x;
		temp.add(x);
		if (i < lastItem) {
			os << L",";
		} // end if
	}	// end for
	os << L"},";
	os << inInsertionPhase << L")";

	sm.transferFrom(temp);
	if (!inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if

#ifndef NDEBUG
	os << endl;
	os << sm.itemKeeper;
#endif
	return (os);
} // operator<<