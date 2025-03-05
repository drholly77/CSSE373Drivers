#pragma once
#include "StaticArray/StaticArrayKernel.hpp"

//
// StaticArray template
// author: Dr. Holly
//

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
class StaticArray1 : public StdOps<StaticArray1<T, lowerBound, upperBound>>,
	public StaticArrayKernel<T, lowerBound, upperBound>
{
public: // Standard Operations
	StaticArray1 ();
	StaticArray1(const StaticArray1& s) = delete;
	~StaticArray1 ();
	void clear (void);
	void transferFrom (StaticArray1& source);
	StaticArray1& operator = (StaticArray1& rhs);

	// StaticArray1 Specific Operations
	void getBounds (Integer& lower, Integer& upper);
	T& operator [] (Integer index);

	friend wostream& operator<< <T, lowerBound, upperBound>(wostream& os, StaticArray1<T, lowerBound, upperBound>& a);
		//! updates os
		//! restores a

private: // Representation
	T* items;   // array of T's to be allocated

private: // Local Operations
	T* createNewRep(int lb, int ub);
	void reclaimRep(T* rep);
};
//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
T* StaticArray1<T, lowerBound, upperBound>::createNewRep(int lb, int ub)
{
	return new T[ub - lb + 1];
} // createNewRep

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
void StaticArray1<T, lowerBound, upperBound>::reclaimRep(T* rep)
{
	delete [] rep;
} // reclaimRep

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
StaticArray1<T, lowerBound, upperBound>::StaticArray1 ()
{
	items = createNewRep(lowerBound, upperBound);
}  // StaticArray1 ()

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
StaticArray1<T, lowerBound, upperBound>::~StaticArray1 ()
{
	reclaimRep(items);
}  // ~StaticArray1 ()

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
void StaticArray1<T, lowerBound, upperBound>::clear(void)
{
	reclaimRep(items);
	items = createNewRep(lowerBound, upperBound);
}  // clear

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
void StaticArray1<T, lowerBound, upperBound>::transferFrom(StaticArray1& source)
{
	reclaimRep(items);
	items = source.items;
	source.items = createNewRep(lowerBound, upperBound);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
StaticArray1<T, lowerBound, upperBound>& StaticArray1<T, lowerBound, upperBound>::operator = (StaticArray1& rhs)
{
	Integer index, size;

	size = upperBound - lowerBound + 1;
	for (index = 0; index < size; index++) {
		items[index] = rhs.items[index];
	} // end for
	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
void StaticArray1<T, lowerBound, upperBound>::getBounds (Integer& lower, Integer& upper)
{
	lower = lowerBound;
	upper = upperBound;
}  // getBounds

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
T& StaticArray1<T, lowerBound, upperBound>::operator [] (Integer index)
{
	return items[index - lowerBound];
}  // operator []

//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
wostream& operator<<(wostream& os, StaticArray1<T, lowerBound, upperBound>& a)
{
	Integer lb, ub;

	a.getBounds (lb, ub);
	os << L"[";
	for (int k = lb; k <= ub; k++) {
		os << a[k];
		if (k < ub) {
			os << L",";
		} // endif
	}	// end for
	os << L"]";

	return os;
} // operator<<
