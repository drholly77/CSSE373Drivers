#pragma once
/*
	Realization of BoundedList using StaticArray
	Author: Dr. Holly
*/
#include "BoundedList/BoundedListKernel.hpp"
#include "StaticArray/StaticArray1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, int maxLength>
class BoundedList1 : public StdOps<BoundedList1<T, maxLength>>, public BoundedListKernel<BoundedList1<T, maxLength>, T, maxLength>
{
public: // standard Operations
	BoundedList1 ();
	BoundedList1(const BoundedList1& s) = delete;
	~BoundedList1 ();
	void clear (void);
	void transferFrom(BoundedList1& source);
	BoundedList1& operator = (BoundedList1& rhs);

	// BoundedList1 Specific Operations
	void moveToStart (void);
	void moveToFinish (void);
	void advance (void);
	void addRightFront (T& x);
	void removeRightFront (T& x);
	T& rightFront (void);
	void replaceRightFront (T& x);
	void swapRights (BoundedList1& otherS);
	Integer leftLength (void);
	Integer rightLength (void);
	Integer remainingCapacity (void);

	friend wostream& operator << <T, maxLength>(wostream &os, BoundedList1<T, maxLength>& s);
	//! updates os
	//! restores q

private: // representation
	enum { lowerBound = 0, upperBound = (maxLength - 1)};
	typedef StaticArray1 <T, lowerBound, upperBound> ArrayOfT;

	ArrayOfT contents;
	Integer fenceLocation;
	Integer currentLength;

	// correspondence s.left = IteratedConcatenation(z: 0 <= z < fenceLocation, <contents(z)>)
	//                s.right = IteratedConcatenation(z: fenceLocation <= z < currentLength, <contents(z)>)

	// convention 0 <= fenceLocation < maxLength and
	//            0 <= currentLength < maxLength and
	//            fenceLocation <= currentLength

private: // local operations
	void displayRep(wostream &os);
	Integer computeRightLength(void);
	void swap(T& lhs, T& rhs);
	void swapRightsHelper(BoundedList1& sSmaller, BoundedList1& sLarger);
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::displayRep(wostream &os)
//! ensures: contents = #contents  and  
//!          currentLength = #currentLength  and  
//!          maxLength = #maxLength  and
//!          the values for each data member (contents, currentLength, maxLength) are displayed
{
	os << endl;
	os << "     contents: " << contents << endl;
	os << "fenceLocation: " << fenceLocation << endl;
	os << "currentLength: " << currentLength << endl;
	os << "    maxLength: " << maxLength << endl;
} // displayRep

//-----------------------------------------------------------------------

template <class T, int maxLength>
Integer BoundedList1<T, maxLength>::computeRightLength(void)
{
	return currentLength - fenceLocation;
} // computeRightLength

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::swap(T& lhs, T& rhs)
{
	T temp;

	temp.transferFrom(lhs);
	lhs.transferFrom(rhs);
	rhs.transferFrom(temp);
} // swap

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::swapRightsHelper(BoundedList1& sSmaller, BoundedList1& sLarger)
//! requires |sSmaller.right| <= |sLarger.right|
{
	Integer kSm, kLg;

	for (kSm = sSmaller.fenceLocation, kLg = sLarger.fenceLocation; kSm < sSmaller.currentLength; kSm++, kLg++) {
		swap(sSmaller.contents[kSm], sLarger.contents[kLg]);
	} // end for
	while (kLg < sLarger.currentLength) {
		sSmaller.contents[kSm].transferFrom(sLarger.contents[kLg]);
		kSm++;
		kLg++;
	} // end while
} // swapRightsHelper

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T, int maxLength>
BoundedList1<T, maxLength>::BoundedList1 ()
{
}	// BoundedList1

//-----------------------------------------------------------------------

template <class T, int maxLength>
BoundedList1<T, maxLength>::~BoundedList1 ()
{
}	// ~BoundedList1

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::transferFrom(BoundedList1& source)
{
	contents.transferFrom(source.contents);
	fenceLocation.transferFrom(source.fenceLocation);
	currentLength.transferFrom(source.currentLength);
} // transferFrom

//-----------------------------------------------------------------------

template <class T, int maxLength>
BoundedList1<T, maxLength>& BoundedList1<T, maxLength>::operator = (BoundedList1& rhs)
{
	contents = rhs.contents;
	fenceLocation = rhs.fenceLocation;
	currentLength = rhs.currentLength;
	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::clear (void)
{
	contents.clear();
	fenceLocation.clear();
	currentLength.clear();
}	// clear

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::moveToStart (void)
{
	fenceLocation = 0;
}	// moveToStart

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::moveToFinish (void)
{
	fenceLocation = currentLength;
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::advance (void)
{
	fenceLocation++;
}	// advance

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::addRightFront (T& x)
{
	for (int k = currentLength; k > fenceLocation; k--) {
		contents[k].transferFrom(contents[k - 1]);
	} // end for
	contents[fenceLocation].transferFrom(x);
	currentLength++;
}	// addRightFront

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::removeRightFront (T& x)
{
	x.transferFrom(contents[fenceLocation]);
	for (int k = fenceLocation, z = currentLength - 1; k < z; k++) {
		contents[k].transferFrom(contents[k + 1]);
	} // end for
	currentLength--;
}	// removeRightFront

//-----------------------------------------------------------------------

template <class T, int maxLength>
T& BoundedList1<T, maxLength>::rightFront(void)
{
	return (contents[fenceLocation]);
}  // rightFront


//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::replaceRightFront (T& x)
{
	swap(x, contents[fenceLocation]);
} // replaceRightFront

//-----------------------------------------------------------------------

template <class T, int maxLength>
void BoundedList1<T, maxLength>::swapRights (BoundedList1& otherS)
{
	Integer lhsRightLength = computeRightLength();
	Integer rhsRightlength = otherS.computeRightLength();

	if (computeRightLength() <= otherS.computeRightLength()) {
		swapRightsHelper(self, otherS);
	} else {
		swapRightsHelper(otherS, self);
	} // end if

	currentLength = fenceLocation + rhsRightlength;
	otherS.currentLength = otherS.fenceLocation + lhsRightLength;

}	// swapRights

//-----------------------------------------------------------------------

template <class T, int maxLength>
Integer BoundedList1<T, maxLength>::leftLength (void)
{
	return (fenceLocation);
}	// leftLength

//-----------------------------------------------------------------------

template <class T, int maxLength>
Integer BoundedList1<T, maxLength>::rightLength (void)
{
	return computeRightLength();
}	// rightLength

//-----------------------------------------------------------------------

template <class T, int maxLength>
Integer BoundedList1<T, maxLength>::remainingCapacity(void)
{
	return maxLength - currentLength;
}	// remainingCapacity

//-----------------------------------------------------------------------

template <class T, int maxLength>
wostream & operator<<(wostream &os, BoundedList1<T, maxLength>& s)
{
#ifdef NDEBUG
	os << L"(<";
	int lengthOfLeft = s.leftLength();

	s.moveToStart();
	for (int i = 0, lastItem = lengthOfLeft - 1; i < lengthOfLeft; i++) {
		os << s.rightFront();
		s.advance();
		if (i < lastItem) {
			os << ",";
		} // end if
	}
	os << L">,<";

	int lengthOfRight = s.rightLength();
	for (int i = 0, lastItem = lengthOfRight - 1; i < lengthOfRight; i++) {
		os << s.rightFront();
		s.advance();
		if (i < lastItem) {
			os << L",";
		} // end if
	}
	os << L">)";

	// reset fence to original location
	s.moveToStart();
	for (int i = 0; i < lengthOfLeft; i++) {
		s.advance();
	}
#else
	s.displayRep(os);
#endif
	return (os);
}