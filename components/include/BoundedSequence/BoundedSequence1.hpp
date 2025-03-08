#pragma once

//
// realization of BoundedSequence Template layered on StaticArray
// author: Dr. Holly
//
#include "BoundedSequence/BoundedSequenceKernel.hpp"
#include "StaticArray/StaticArray1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------
template <class T, int maxLength>
class BoundedSequence1 : 
	public StdOps<BoundedSequence1<T, maxLength>>, 
	public BoundedSequenceKernel<BoundedSequence1<T, maxLength>, T, maxLength>
{
public: // Standard Operations
	BoundedSequence1();
	BoundedSequence1(const BoundedSequence1& s) = delete;
	~BoundedSequence1();
	void clear(void);
	void transferFrom(BoundedSequence1& source);
	BoundedSequence1& operator = (BoundedSequence1& rhs);

// BoundedSequence1 Specific Operations
	void add(Integer pos, T& x);
	void remove(Integer pos, T& x);
	void replaceEntry(Integer pos, T& x);
	T& entry(Integer pos);
	void append(BoundedSequence1& sToAppend);
	void split(Integer pos, BoundedSequence1& receivingS);
	Integer length(void);
	Integer remainingCapacity(void);

	friend wostream & operator<< <T>(wostream &os, BoundedSequence1& s);
	//! updates os
	//! restores s

private: // representation

	enum { lowerBound = 0, upperBound = (maxLength - 1) };
	typedef StaticArray1 <T, lowerBound, upperBound> ArrayOfT;

	ArrayOfT contents;
	Integer currentLength;

	// correspondence self = IteratedConcatenation(z: 0 <= z < currentLength, <contents(z)>)

	// convention 0 <= currentLength < maxLength

private: // local Operations
	void displayRep(wostream &os);
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// local Operations
//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedSequence1<T, maxLength>::displayRep(wostream &os)
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
BoundedSequence1<T, maxLength>::BoundedSequence1()
{
}	// BoundedSequence1

//-----------------------------------------------------------------------

template <class T, int maxLength>
BoundedSequence1<T, maxLength>::~BoundedSequence1()
{
}	// ~BoundedSequence1

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedSequence1<T, maxLength>::transferFrom(BoundedSequence1& source)
{
	contents.transferFrom(source.contents);
	currentLength.transferFrom(source.currentLength);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, int maxLength>
BoundedSequence1<T, maxLength>& BoundedSequence1<T, maxLength>::operator = (BoundedSequence1& rhs)
{
	contents = rhs.contents;
	currentLength = rhs.currentLength;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedSequence1<T, maxLength>::clear(void)
{
	contents.clear();
	currentLength.clear();
}	// clear

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedSequence1<T, maxLength>::add(Integer pos, T& x)
{
	for (int k = currentLength; k > pos; k--) {
		contents[k].transferFrom(contents[k - 1]);
	} // end for
	contents[pos].transferFrom(x);
	currentLength++;
}	// add

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedSequence1<T, maxLength>::remove(Integer pos, T& x)
{
	x.transferFrom(contents[pos]);
	for (int k = pos, z = currentLength - 1; k < z; k++) {
		contents[k].transferFrom(contents[k + 1]);
	} // end for
	currentLength--;
}	// remove

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedSequence1<T, maxLength>::replaceEntry(Integer pos, T& x)
{
	T temp;

	temp.transferFrom(contents[pos]);
	contents[pos].transferFrom(x);
	x.transferFrom(temp);
}	// replaceEntry

//-----------------------------------------------------------------------

template <class T, int maxLength>
T& BoundedSequence1<T, maxLength>::entry(Integer pos)
{
	return (contents[pos]);
}	// entry

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedSequence1<T, maxLength>::append(BoundedSequence1& sToAppend)
{
	for (int j = currentLength, k = 0; k < sToAppend.currentLength; j++, k++) {
		contents[j].transferFrom(sToAppend.contents[k]);
	} // end for
	currentLength += sToAppend.currentLength;
	sToAppend.currentLength.clear();
}	// append

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedSequence1<T, maxLength>::split(Integer pos, BoundedSequence1& receivingS)
{
	receivingS.contents.clear();

	for (int j = pos, k = 0; j < currentLength; j++, k++) {
		receivingS.contents[k].transferFrom(contents[j]);
	} // end for
	receivingS.currentLength = currentLength - pos;
	currentLength = pos;
}	// split

//-----------------------------------------------------------------------

template <class T, int maxLength>
Integer BoundedSequence1<T, maxLength>::length(void)
{
	return currentLength;
}	// length

//-----------------------------------------------------------------------

template <class T, int maxLength>
inline Integer BoundedSequence1<T, maxLength>::remainingCapacity(void)
{
	return 	(maxLength - currentLength);
}	// remainingCapacity

//-----------------------------------------------------------------------

template <class T, int maxLength>
wostream & operator<<(wostream &os, BoundedSequence1<T, maxLength>& s)
{
#ifdef NDEBUG
	os << L"<";
	for (int p = 0, z = s.length(), lastItem = z - 1; p < z; p++) {
		T x;

		os << s.entry(p);
		if (p < lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L">";
#else
	s.displayRep(os);
#endif
	return (os);
} // operator<<