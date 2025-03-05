#pragma once
#include "SortingMachine/SortingMachineKernel.hpp"
//
// Exchange Sort Realization of SortingMachine using List
// author: Dr. Holly
//

#include "List/List1.hpp"

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
class SortingMachine1 : public StdOps<SortingMachine1<T, areOrdered>>, SortingMachineKernel<T>
{
public: // Standard Operations
	SortingMachine1 ();
	SortingMachine1(const SortingMachine1& s) = delete;
	~SortingMachine1 ();
	void clear (void);
	void transferFrom (SortingMachine1& source);
	SortingMachine1& operator = (SortingMachine1& rhs);

	// SortingMachine1 Specific Operations
	void add (T& x);
	void changeToExtractionMode (void);
	void removeFirst (T& x);
	Integer size (void);
	Boolean isInInsertionMode (void);

	friend wostream& operator<< <T, areOrdered>(wostream& os, SortingMachine1& s);
		//! updates os
		//! restores s

private: // Representation
	typedef List1 <T> ListOfT;

	Boolean insertionMode;
	ListOfT itemKeeper;

private: // Local Operations
	void exchangeSort (ListOfT& s);
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

// convention
// itemKeeper.left = <>
//

//----------------------------------------------------------------
// Local Operations
//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine1<T, areOrdered>::exchangeSort (ListOfT& s)
{
	for (int k = 0, z = s.rightLength(); k < z; k++) {
		T x;
		s.removeRightFront(x);
		for (int k = 0; k < (z - 1); k++) {
			T y;
			s.removeRightFront(y);
			if (areOrdered(x, y)) {
				s.addRightFront(x);
				x.transferFrom(y);
			}
			else {
				s.addRightFront(y);
			} // end if
			s.advance();
		}	// end for
		s.addRightFront(x);
		s.moveToStart();
	} // end for
}	// exchangeSort

//----------------------------------------------------------------
// Exported Operations
//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
SortingMachine1<T, areOrdered>::SortingMachine1 ()
{
	insertionMode = true;
}	// SortingMachine1

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
SortingMachine1<T, areOrdered>::~SortingMachine1 ()
{
}	// ~SortingMachine1

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine1<T, areOrdered>::clear(void)
{
	itemKeeper.clear();
	insertionMode = true;
}	// clear

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine1<T, areOrdered>::transferFrom(SortingMachine1& source)
{
	insertionMode.transferFrom(source.insertionMode);
	source.insertionMode = true;
	itemKeeper.transferFrom(source.itemKeeper);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
SortingMachine1<T, areOrdered>& 
SortingMachine1<T, areOrdered>::operator = (SortingMachine1& rhs)
{
	insertionMode = rhs.insertionMode;
	itemKeeper = rhs.itemKeeper;
	return *this;
} // operator =

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine1<T, areOrdered>::add (T& x)
{
	itemKeeper.addRightFront(x);
}	// add

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine1<T, areOrdered>::changeToExtractionMode (void)
{
	exchangeSort(itemKeeper);
	insertionMode = false;
}	// changeToExtractionMode

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
void SortingMachine1<T, areOrdered>::removeFirst (T& x)
{
	itemKeeper.removeRightFront(x);
}	// removeFirst

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Integer SortingMachine1<T, areOrdered>::size (void)
{
   return itemKeeper.rightLength();
}	// size

//----------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
Boolean SortingMachine1<T, areOrdered>::isInInsertionMode (void)
{
   return insertionMode;
}	// isInInsertionMode

//-----------------------------------------------------------------------

template <class T, Boolean(*areOrdered)(T&, T&)>
wostream& operator<<(wostream& os, SortingMachine1<T, areOrdered>& sm)
{
#ifdef NDEBUG
	Boolean inInsertionPhase;
	SortingMachine1<T, areOrdered> temp;

	inInsertionPhase = sm.isInInsertionMode();
	if (inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if
	os << L"({";
	for (int k = 0, z = sm.size(), lastItem = z - 1; k < z; k++) {
		T x;

		sm.removeFirst(x);
		os << x;
		temp.add(x);
		if (k < lastItem) {
			os << L",";
		} // end if
	}	// end for
	os << L"},";
	os << inInsertionPhase << L")";

	sm.transferFrom(temp);
	if (!inInsertionPhase) {
		sm.changeToExtractionMode();
	}   // end if
#else
	os << sm.itemKeeper;
#endif
	return os;
} // operator<<