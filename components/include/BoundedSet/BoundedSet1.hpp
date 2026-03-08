#pragma once
#include "BoundedSet/BoundedSetKernel.hpp"
#include "StaticArray/StaticArray1.hpp"
/*
	Realization of Set layered on Chain Position
*/

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
class BoundedSet1 : public StdOps<BoundedSet1<T, maxSize, areEqual>>, public BoundedSetKernel<T, maxSize>
{
public: // Standard Operations
	BoundedSet1();
	BoundedSet1(const BoundedSet1& s) = delete;
	~BoundedSet1();
	void clear(void);
	void transferFrom(BoundedSet1& source);
	BoundedSet1& operator = (BoundedSet1& rhs);

	// BoundedSet1 Specific Operations
	void add(T& x);
	void remove(T& xFromClient, T& xFromSet);
	void removeAny(T& x);
	Boolean contains(T& x);
	Integer size(void);
	Integer remainingCapacity(void);

	friend wostream& operator<< <T, maxSize, areEqual>(wostream& os, BoundedSet1& s);
	//! updates os
	//! restores s

private: // Representation

	enum { lowerBound = 0, upperBound = (maxSize - 1) };
	typedef StaticArray1 <T, lowerBound, upperBound> ArrayOfT;

	ArrayOfT contents;
	Integer currentSize;
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------


// convention: chain == smartPosition

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
BoundedSet1<T, maxSize, areEqual>::BoundedSet1()
{
	currentSize = 0;
}	// BoundedSet1

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
BoundedSet1<T, maxSize, areEqual>::~BoundedSet1()
{
}	// ~BoundedSet1

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
void BoundedSet1<T, maxSize, areEqual>::clear(void)
{
	contents.clear();
	currentSize = 0;
}	// clear

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
void BoundedSet1<T, maxSize, areEqual>::transferFrom(BoundedSet1& source)
{
	contents.transferFrom(source.contents);
	currentSize.transferFrom(source.currentSize);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
BoundedSet1<T, maxSize, areEqual>& BoundedSet1<T, maxSize, areEqual>::operator = (BoundedSet1& rhs)
{
	contents = rhs.contents;
	currentSize = rhs.currentSize;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
void BoundedSet1<T, maxSize, areEqual>::add(T& x)
{
	contents[currentSize].transferFrom(x);
	currentSize++;
}	// add

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
void BoundedSet1<T, maxSize, areEqual>::remove(T& xFromClient, T& xFromSet)
{
	int k = 0;
	while (!areEqual(xFromClient, contents[k])) {
		k++;
	}	// end while
	xFromSet.transferFrom(contents[k]);
	while (k < (currentSize - 1)) {
		contents[k].transferFrom(contents[k + 1]);
		k++;
	}	// end while
	currentSize--;
}	// remove

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
void BoundedSet1<T, maxSize, areEqual>::removeAny(T& x)
{
	currentSize--;
	x.transferFrom(contents[currentSize]);
}	// removeAny

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
Boolean BoundedSet1<T, maxSize, areEqual>::contains(T& x)
{
	int k = 0;
	while (k < currentSize && !areEqual(x, contents[k])) {
		k++;
	}	// end while
	return (k < currentSize);
}	// contains

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
Integer BoundedSet1<T, maxSize, areEqual>::size(void)
{
	return currentSize;
}	// size

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean(*areEqual)(T&, T&)>
Integer BoundedSet1<T, maxSize, areEqual>::remainingCapacity(void)
{
	return (maxSize - currentSize);
}	// remainingCapacity

//-----------------------------------------------------------------------

template <class T, int maxSize, Boolean (*areEqual)(T&, T&)>
wostream& operator<<(wostream& os, BoundedSet1<T, maxSize, areEqual>& s)
{
	BoundedSet1<T, maxSize, areEqual> temp;

	os << L"{";
	for (int k = 0, z = s.size(), lastItem = z - 1; k < z; k++) {
		T x;

		s.removeAny(x);
		os << x;
		temp.add(x);
		if (k < lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L"}";

	s.transferFrom(temp);
	return os;
} // operator<<