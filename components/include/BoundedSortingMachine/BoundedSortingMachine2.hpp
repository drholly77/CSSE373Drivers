#pragma once
//
// Insertion Sort Realization of SortingMachine using Array
// author: Dr. Holly
//

#include "Wrapper.h"
#include "BoundedSortingMachine/BoundedSortingMachineKernel.hpp"
#include "CeramicArray\CeramicArray1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------


template <class T, Boolean(*areOrdered)(T&, T&)>
class BoundedSortingMachine2 : public StdOps<BoundedSortingMachine2<T, areOrdered>>, public BoundedSortingMachineKernel<T>
{
public: // standard Operations
	BoundedSortingMachine2 ();
	BoundedSortingMachine2(const BoundedSortingMachine2& s) = delete;
	~BoundedSortingMachine2 ();
	void clear (void);
	void transferFrom(BoundedSortingMachine2& source);
	BoundedSortingMachine2& operator = (BoundedSortingMachine2& rhs);

	// BoundedSortingMachine2 Specific Operations
	void setMaxSize(Integer maxSize);
	Integer maxSize(void);
	void add (T& x);
	void changeToExtractionMode (void);
	void removeFirst (T& x);
	Integer size (void);
	Boolean isInInsertionMode (void);
	Integer remainingCapacity(void);

	friend wostream& operator<< <T, areOrdered>(wostream &os, BoundedSortingMachine2& s);
	//! updates os
	//! restores s

private: // representation
	typedef CeramicArray1 <T> ArrayOfT;

	Boolean insertionMode;
	ArrayOfT itemKeeper;
	Integer nextAddLocation;
	Integer maxContentsSize;

private: // local Operations
	void insertionSort(ArrayOfT& s, Integer size);
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------



//----------------------------------------------------------------
// local Operations
//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine2<T, areOrdered>::insertionSort (ArrayOfT& a, Integer size)
{
	for (int j = 1; j < size; j++) {
		Integer k = j - 1;
		T key;
		key.transferFrom(a[j]);
		while ((k >= 0) && (areOrdered(a[k], key))) {
			a[k + 1].transferFrom(a[k]);
			k--;
		} // end while
		a[k + 1].transferFrom(key);
	} // end for
}	// insertionSort

//----------------------------------------------------------------
// exported Operations
//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
BoundedSortingMachine2<T, areOrdered>::BoundedSortingMachine2 ()
{
	insertionMode = true;
}	// BoundedSortingMachine2

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
BoundedSortingMachine2<T, areOrdered>::~BoundedSortingMachine2 ()
{
}	// ~BoundedSortingMachine2

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine2<T, areOrdered>::transferFrom(BoundedSortingMachine2& source)
{
	insertionMode.transferFrom(source.insertionMode);
	itemKeeper.transferFrom(source.itemKeeper);
	nextAddLocation.transferFrom(source.nextAddLocation);
	maxContentsSize.transferFrom(source.maxContentsSize);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
BoundedSortingMachine2<T, areOrdered>& 
BoundedSortingMachine2<T, areOrdered>::operator = (BoundedSortingMachine2& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	nextAddLocation = rhs.nextAddLocation;
	maxContentsSize = rhs.maxContentsSize;
	return (*this);
} // operator =

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine2<T, areOrdered>::clear (void)
{
	itemKeeper.clear();
	insertionMode = true;
	nextAddLocation.clear();
	maxContentsSize.clear();
}	// clear

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine2<T, areOrdered>::setMaxSize(Integer maxSize)
{
	maxContentsSize = maxSize;
	itemKeeper.setBounds(0, (maxSize - 1));
}	// setMaxSize

	//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Integer BoundedSortingMachine2<T, areOrdered>::maxSize(void)
{
	return maxContentsSize;
}	// maxSize

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine2<T, areOrdered>::add (T& x)
{
	itemKeeper[nextAddLocation].transferFrom(x);
	nextAddLocation++;
}	// add

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine2<T, areOrdered>::changeToExtractionMode (void)
{
	insertionSort(itemKeeper, nextAddLocation);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine2<T, areOrdered>::removeFirst (T& x)
{
	nextAddLocation--;
	x.transferFrom(itemKeeper[nextAddLocation]);
}	// removeFirst

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Integer BoundedSortingMachine2<T, areOrdered>::size (void)
{
	return nextAddLocation; 
}	// size

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Boolean BoundedSortingMachine2<T, areOrdered>::isInInsertionMode (void)
{
   return insertionMode;
}	// isInInsertionMode

	//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Integer BoundedSortingMachine2<T, areOrdered>::remainingCapacity(void)
{
	return maxContentsSize - nextAddLocation;
}	// remainingCapacity

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
wostream & operator<<(wostream &os, BoundedSortingMachine2<T, areOrdered>& sm)
{
	Boolean inInsertionPhase;
	BoundedSortingMachine2<T, areOrdered> temp;

	inInsertionPhase = sm.isInInsertionMode();
	temp.setMaxSize(sm.maxSize());
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
	return (os);
} // operator<<