#pragma once
#include "Wrapper.h"
#include "BoundedSortingMachine/BoundedSortingMachineKernel.hpp"
#include "CeramicArray/CeramicArray1.hpp"
//
// Exchange Sort Realization of BoundedSortingMachine using Ceramic Array
// author: Dr. Holly
//


//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
class BoundedSortingMachine1 : public StdOps<BoundedSortingMachine1<T, areOrdered>>, public BoundedSortingMachineKernel<T>
{
public: // standard Operations
	BoundedSortingMachine1 ();
	BoundedSortingMachine1(const BoundedSortingMachine1& s) = delete;
	~BoundedSortingMachine1 ();
	void clear (void);
	void transferFrom(BoundedSortingMachine1& source);
	BoundedSortingMachine1& operator = (BoundedSortingMachine1& rhs);

	// BoundedSortingMachine1 Specific Operations
	void setMaxSize(Integer maxSize);
	Integer maxSize(void);
	void add (T& x);
	void changeToExtractionMode (void);
	void removeFirst (T& x);
	Integer size (void);
	Boolean isInInsertionMode (void);
	Integer remainingCapacity(void);

	friend wostream & operator<< <T, areOrdered>(wostream &os, BoundedSortingMachine1& s);
	    //! updates os
	    //! restores s

private: // representation
	typedef CeramicArray1 <T> ArrayOfT;

	Boolean insertionMode;
	ArrayOfT itemKeeper;
	Integer nextAddLocation;
	Integer maxContentsSize;

private: // local Operations
	void exchangeSort (ArrayOfT& a, Integer size);
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------



//----------------------------------------------------------------
// local Operations
//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine1<T, areOrdered>::exchangeSort (ArrayOfT& a, Integer size)
{
	for (int j = 0; j < size; j++) {
		for (int k = 0, z = (size - 1); k < z; k++) {
			if (areOrdered(a[k], a[k+1])) {
				T temp;
				temp.transferFrom(a[k]);
				a[k].transferFrom(a[k+1]);
				a[k + 1].transferFrom(temp);
			} // end if
		}	// end for
	} // end for
}	// exchangeSort

//----------------------------------------------------------------
// exported Operations
//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
BoundedSortingMachine1<T, areOrdered>::BoundedSortingMachine1 ()
{
	insertionMode = true;
}	// BoundedSortingMachine1

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
BoundedSortingMachine1<T, areOrdered>::~BoundedSortingMachine1 ()
{
}	// ~BoundedSortingMachine1

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine1<T, areOrdered>::transferFrom(BoundedSortingMachine1& source)
{
	insertionMode.transferFrom(source.insertionMode);
	itemKeeper.transferFrom(source.itemKeeper);
	nextAddLocation.transferFrom(source.nextAddLocation);
	maxContentsSize.transferFrom(source.maxContentsSize);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
BoundedSortingMachine1<T, areOrdered>& 
BoundedSortingMachine1<T, areOrdered>::operator = (BoundedSortingMachine1& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	nextAddLocation = rhs.nextAddLocation;
	maxContentsSize = rhs.maxContentsSize;
	return (*this);
} // operator =

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine1<T, areOrdered>::clear (void)
{
	itemKeeper.clear();
	insertionMode = true;
	nextAddLocation.clear();
	maxContentsSize.clear();
}	// clear

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine1<T, areOrdered>::setMaxSize(Integer maxSize)
{
	maxContentsSize = maxSize;
	itemKeeper.setBounds(0, (maxSize - 1));
}	// setMaxSize

	//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Integer BoundedSortingMachine1<T, areOrdered>::maxSize(void)
{
	return maxContentsSize;
}	// maxSize

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine1<T, areOrdered>::add (T& x)
{
	itemKeeper[nextAddLocation].transferFrom(x);
	nextAddLocation++;
}	// add

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine1<T, areOrdered>::changeToExtractionMode (void)
{
	exchangeSort(itemKeeper, nextAddLocation);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void BoundedSortingMachine1<T, areOrdered>::removeFirst (T& x)
{
	nextAddLocation--;
	x.transferFrom(itemKeeper[nextAddLocation]);
}	// removeFirst

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Integer BoundedSortingMachine1<T, areOrdered>::size (void)
{
	return nextAddLocation; 
}	// size

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Boolean BoundedSortingMachine1<T, areOrdered>::isInInsertionMode (void)
{
   return insertionMode;
}	// isInInsertionMode

	//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Integer BoundedSortingMachine1<T, areOrdered>::remainingCapacity(void)
{
	return maxContentsSize - nextAddLocation;
}	// remainingCapacity

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
wostream & operator<<(wostream &os, BoundedSortingMachine1<T, areOrdered>& sm)
{
	Boolean inInsertionPhase;
	BoundedSortingMachine1<T, areOrdered> temp;

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