#pragma once
#include "Wrapper.h"
#include "List/ListKernel.hpp"
#include "ChainPosition/ChainPosition.hpp"

/*
	Realization of List using ChainPosition
*/

template <class T>
class List1 : public StdOps<List1<T>>, public ListKernel<List1<T>, T>
{
public: // Standard Operations
	List1 ();
	List1(const List1& s) = delete;
	~List1 ();
	void clear (void);
	void transferFrom (List1& source);
	List1& operator = (List1& rhs);

	// List1 Specific Operations
	void moveToStart (void);
	void moveToFinish (void);
	void advance (void);
	void addRightFront (T& x);
	void removeRightFront (T& x);
	T& rightFront(void);
	void replaceRightFront (T& x);
	void swapRights (List1& otherS);
	Integer leftLength (void);
	Integer rightLength (void);

	friend wostream& operator<< <T>(wostream& os, List1<T>& s);
		//! updates os
		//! restores s

private: // Representation
	typedef ChainPosition1 <T> ChainPositionOfT;

	ChainPositionOfT preFront;
	ChainPositionOfT lastLeft;
	ChainPositionOfT lastNode;
	Integer lengthOfLeft;
	Integer lengthOfRight;

private: // Local Operations
	void createNewRep(void);
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

template <class T>
void List1<T>::createNewRep(void)
{
	T temp;

	preFront.labelNew (temp);
	lastLeft = preFront;
	lastNode = preFront;
	lengthOfLeft.clear ();
	lengthOfRight.clear ();
}

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

template <class T>
List1<T>::List1 ()
{
	self.createNewRep();
}	// List1

//-----------------------------------------------------------------------

template <class T>
List1<T>::~List1 ()
{
}	// ~List1

//-----------------------------------------------------------------------

template <class T>
void List1<T>::clear(void)
{
	self.createNewRep();
}	// clear

//-----------------------------------------------------------------------

template <class T>
void List1<T>::transferFrom(List1& source)
{
	preFront.transferFrom(source.preFront);
	lastLeft.transferFrom(source.lastLeft);
	lastNode.transferFrom(source.lastNode);
	lengthOfLeft.transferFrom(source.lengthOfLeft);
	lengthOfRight.transferFrom(source.lengthOfRight);
	source.createNewRep();
}

//-----------------------------------------------------------------------

template <class T>
List1<T>& List1<T>::operator = (List1& rhs)
{
	ChainPositionOfT newPos, oldPos;
	T x;

	preFront.labelNew (x);
	lastLeft = preFront;
	lastNode = preFront;

	oldPos = rhs.preFront;
	oldPos.applyTarget ();
	while (!oldPos.isZero ()) {
		x = oldPos.label();
		newPos.labelNew (x);
		if (oldPos == rhs.lastLeft) {
			// in the rhs list we have found lastLeft location
			// set the lastLeft in the receiving list
			lastLeft = newPos;
		} // end if
		lastNode.swapWithTarget (newPos);
		lastNode.applyTarget ();
		oldPos.applyTarget ();
	} // end while
	lengthOfLeft = rhs.lengthOfLeft;
	lengthOfRight = rhs.lengthOfRight;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void List1<T>::moveToStart (void)
{
	lastLeft = preFront;
	lengthOfRight += lengthOfLeft;
	lengthOfLeft = 0;
}	// moveToStart

//-----------------------------------------------------------------------

template <class T>
void List1<T>::moveToFinish (void)
{
	lastLeft = lastNode;
	lengthOfLeft += lengthOfRight;
	lengthOfRight = 0;
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T>
void List1<T>::advance (void)
{
	lastLeft.applyTarget ();
	lengthOfLeft++;
	lengthOfRight--;
}	// advance

//-----------------------------------------------------------------------

template <class T>
void List1<T>::addRightFront (T& x)
{
	ChainPositionOfT newPos;
	ChainPositionOfT temp;

	newPos.labelNew (x);
	temp = newPos;
	lastLeft.swapWithTarget (temp);
	newPos.swapWithTarget (temp);
	lengthOfRight++;
	if (lengthOfRight == 1) {
		lastNode = newPos;
	} // end if
}	// addRightFront

//-----------------------------------------------------------------------

template <class T>
void List1<T>::removeRightFront (T& x)
{
	ChainPositionOfT temp;

	temp = lastLeft;
	temp.applyTarget ();
	temp.replaceLabel (x);
	temp.applyTarget ();
	lastLeft.swapWithTarget (temp);
	lengthOfRight--;
	if (lengthOfRight == 0) {
		lastNode = lastLeft;
	} // end if
}	// removeRightFront

//-----------------------------------------------------------------------

template <class T>
T& List1<T>::rightFront(void)
{
	ChainPositionOfT temp;

	temp = lastLeft;
	temp.applyTarget ();
	return temp.label();
}  // rightFront


//-----------------------------------------------------------------------

template <class T>
void List1<T>::replaceRightFront (T& x)
{
	ChainPositionOfT temp;

	temp = lastLeft;
	temp.applyTarget ();
	temp.replaceLabel (x);
} // replaceRightFront

//-----------------------------------------------------------------------

template <class T>
void List1<T>::swapRights (List1& s)
{
	ChainPositionOfT temp;

	lastLeft.swapWithTarget (temp);
	(s.lastLeft).swapWithTarget (temp);
	lastLeft.swapWithTarget (temp);

	// swap lastNodes
	temp.transferFrom(lastNode);
	lastNode.transferFrom(s.lastNode);
	s.lastNode.transferFrom(temp);

	int length = lengthOfRight;
	lengthOfRight = s.lengthOfRight;
	s.lengthOfRight = length;

	if (lengthOfRight == 0) {
		lastNode = lastLeft;
	} // end if
	if (s.lengthOfRight == 0) {
		s.lastNode = s.lastLeft;
	} // end if
}	// swapRights

//-----------------------------------------------------------------------

template <class T>
Integer List1<T>::leftLength (void)
{
	return lengthOfLeft;
}	// leftLength

//-----------------------------------------------------------------------

template <class T>
inline Integer List1<T>::rightLength (void)
{
	return lengthOfRight;
}	// rightLength

//-----------------------------------------------------------------------

template <class T>
wostream& operator<<(wostream& os, List1<T>& s)
{
	os << L"(<";
	int lengthOfLeft = s.leftLength();

	s.moveToStart();
	for (int k = 0, lastItem = lengthOfLeft - 1; k < lengthOfLeft; k++) {
		os << s.rightFront();
		s.advance();
		if (k < lastItem) {
			os << L",";
		} // end if
	}
	os << L">,<";

	int lengthOfRight = s.rightLength();
	for (int k = 0, lastItem = lengthOfRight - 1; k < lengthOfRight; k++) {
		os << s.rightFront();
		s.advance();
		if (k < lastItem) {
			os << L",";
		} // end if
	}
	os << L">)";

	// reset fence to original location
	s.moveToStart();
	for (int k = 0; k < lengthOfLeft; k++) {
		s.advance();
	}
	return os;
}