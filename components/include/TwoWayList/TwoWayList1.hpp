#pragma once
/*
	Realization of TwoWayListTemplate using CyclePosition
	Author: Dr. Holly
*/
#include "TwoWayList/TwoWayListKernel.hpp"
#include "CyclePosition/CyclePosition.hpp"

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T>
class TwoWayList1 : public StdOps<TwoWayList1<T>>, public TwoWayListKernel<TwoWayList1<T>, T>
{
public: // Standard Operations
	TwoWayList1 ();
	TwoWayList1(const TwoWayList1& s) = delete;
	~TwoWayList1 ();
	void clear (void);
	void transferFrom (TwoWayList1& source);
	TwoWayList1& operator = (TwoWayList1& rhs);

	// TwoWayList1 Specific Operations
	void moveToStart(void);
	void moveToFinish(void);
	void advance(void);
	void retreat(void);
	void addRightFront(T& x);
	void removeRightFront(T& x);
	T& rightFront(void);
	void replaceRightFront(T& x);
	void swapRights(TwoWayList1& otherS);
	Integer leftLength(void);
	Integer rightLength(void);

	friend wostream& operator<< <T>(wostream& os, TwoWayList1<T>& s);
		//! updates os
		//! restores s

private: // Representation
	typedef CyclePosition1 <T> CyclePositionOfT;

	CyclePositionOfT preFront;
	CyclePositionOfT lastLeft;
	Integer lengthOfLeft;
	Integer lengthOfRight;

private: // Local Operations
	void clearRep(void);
};
//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::clearRep(void)
{
	preFront.clear();
	lastLeft.clear();
	lengthOfLeft.clear();
	lengthOfRight.clear();
} // clearRep

  //-----------------------------------------------------------------------
  // exported Operations
  //-----------------------------------------------------------------------

template <class T>
TwoWayList1<T>::TwoWayList1()
{
	lastLeft = preFront;
}	// TwoWayList1

//-----------------------------------------------------------------------

template <class T>
TwoWayList1<T>::~TwoWayList1()
{
}	// ~TwoWayList1

  //-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::clear(void)
{
	self.clearRep();
	lastLeft = preFront;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::transferFrom(TwoWayList1& source)
{
	preFront.transferFrom(source.preFront);
	lastLeft.transferFrom(source.lastLeft);
	lengthOfLeft.transferFrom(source.lengthOfLeft);
	lengthOfRight.transferFrom(source.lengthOfRight);

	lastLeft = preFront;
}

//-----------------------------------------------------------------------

template <class T>
TwoWayList1<T>& TwoWayList1<T>::operator = (TwoWayList1& rhs)
{
	CyclePositionOfT existingPos, current;
	T x;
	Integer size;

	self.clearRep();
	lastLeft = preFront;
	current = lastLeft;

	existingPos = rhs.preFront;
	existingPos.applyTarget();
	size = rhs.lengthOfLeft + rhs.lengthOfRight;
	while (size > 0) {
		CyclePositionOfT newPos;
		x = existingPos.label();
		newPos.replaceLabel(x);
		current.transposeAfter(newPos);
		current.applyTarget();
		if (existingPos == rhs.lastLeft) {
			lastLeft = current;
		} // end if
		existingPos.applyTarget();
		size--;
	} // end while
	lengthOfLeft = rhs.lengthOfLeft;
	lengthOfRight = rhs.lengthOfRight;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::moveToStart(void)
{
	lastLeft = preFront;
	lengthOfRight += lengthOfLeft;
	lengthOfLeft = 0;
}	// moveToStart

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::moveToFinish(void)
{
	lastLeft = preFront;
	lastLeft.applyInverseTarget();
	lengthOfLeft += lengthOfRight;
	lengthOfRight = 0;
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::advance(void)
{
	lastLeft.applyTarget();
	lengthOfLeft++;
	lengthOfRight--;
}	// advance

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::retreat(void)
{
	lastLeft.applyInverseTarget();
	lengthOfLeft--;
	lengthOfRight++;
}	// retreat

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::addRightFront(T& x)
{
	CyclePositionOfT newPos;

	newPos.replaceLabel(x);
	lastLeft.transposeAfter(newPos);
	lengthOfRight++;
}	// addRightFront

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::removeRightFront(T& x)
{
	CyclePositionOfT temp;

	temp = lastLeft;
	temp.applyTarget();
	temp.replaceLabel(x);
	lastLeft.transposeAfter(temp);
	lengthOfRight--;
}	// removeRightFront

//-----------------------------------------------------------------------

template <class T>
T& TwoWayList1<T>::rightFront(void)
{
	CyclePositionOfT temp;

	temp = lastLeft;
	temp.applyTarget();
	return temp.label();
}  // rightFront

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::replaceRightFront(T& item)
{
	CyclePositionOfT temp;

	temp = lastLeft;
	temp.applyTarget();
	temp.replaceLabel(item);
} // replaceRightFront

//-----------------------------------------------------------------------

template <class T>
void TwoWayList1<T>::swapRights(TwoWayList1& s)
{
	lastLeft.transposeAfter(s.lastLeft);
	preFront.transposeBefore(s.preFront);

	int temp = lengthOfRight;
	lengthOfRight = s.lengthOfRight;
	s.lengthOfRight = temp;
}	// swapRights

//-----------------------------------------------------------------------

template <class T>
Integer TwoWayList1<T>::leftLength(void)
{
	return lengthOfLeft;
}	// leftLength

//-----------------------------------------------------------------------

template <class T>
Integer TwoWayList1<T>::rightLength(void)
{
	return lengthOfRight;
}	// rightLength

//-----------------------------------------------------------------------

template <class T>
wostream & operator<<(wostream &os, TwoWayList1<T>& s)
{
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
	return os;
}
