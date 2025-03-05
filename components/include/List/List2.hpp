#pragma once
#pragma warning( disable : 4716; disable : 4172)
/*
	Author: put your name here
*/
#include "List\ListKernel.hpp"
#include "Queue\Queue1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class List2 : public StdOps<List2<T>>, public ListKernel<List2<T>, T>

{
public: // Standard Operations
	List2();
	List2(const List2& s) = delete;
	~List2();
	void clear(void);
	void transferFrom(List2& source);
	List2& operator = (List2& rhs);

	// List2 Specific Operations
	void moveToStart(void);
	void moveToFinish(void);
	void advance(void);
	void addRightFront(T& x);
	void removeRightFront(T& x);
	T& rightFront(void);
	void replaceRightFront(T& x);
	void swapRights(List2& otherS);
	Integer leftLength(void);
	Integer rightLength(void);

	friend wostream& operator<< <T>(wostream& os, List2<T>& s);
	//! updates os
	//! restores s

private: // Representation
	typedef Queue1<T> QueueOfT;

	QueueOfT leftQ;
	QueueOfT rightQ;
	//! correspondence:
	//!	self.left = leftQ  and  self.right = rightQ
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
List2<T>::List2()
{
	// TODO: Nothing - see slides for why
}	// List2

//-----------------------------------------------------------------------

template <class T>
List2<T>::~List2()
{
	// TODO: Nothing - see slides for why
}	// ~List2

//-----------------------------------------------------------------------

template <class T>
void List2<T>::transferFrom(List2& source)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me - see slides for how
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
List2<T>& List2<T>::operator = (List2& rhs)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me - see slides for how

	return *this; // The last line of all operator = in C++ must be exactly like this line
} // operator =

//-----------------------------------------------------------------------

template <class T>
void List2<T>::clear(void)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me - see slides for how
}	// clear

//-----------------------------------------------------------------------

template <class T>
void List2<T>::moveToStart(void)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me
}	// moveToStart

//-----------------------------------------------------------------------

template <class T>
void List2<T>::moveToFinish(void)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T>
void List2<T>::advance(void)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me
}	// advance

//-----------------------------------------------------------------------

template <class T>
void List2<T>::addRightFront(T& x)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold


	// TODO: Nothing - use this to help understand the correspondence 
	//                 and how to do some of the other operations

	QueueOfT tempQ;

	tempQ.enqueue(x);
	for (int k = 0, z = rightQ.length(); k < z; k++) {
		T x;
		rightQ.dequeue(x);
		tempQ.enqueue(x);
	} // end for
	rightQ.transferFrom(tempQ);
}	// addRightFront

//-----------------------------------------------------------------------

template <class T>
void List2<T>::removeRightFront(T& x)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me
}	// removeRightFront

//-----------------------------------------------------------------------

template <class T>
T& List2<T>::rightFront(void)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me
	//       You must end this with a 'return' 
	//       The return below does not provide the correct functionality for rightFront
	//       The return below is here so that this operation will compile correctly
	return T();
}  // rightFront


//-----------------------------------------------------------------------

template <class T>
void List2<T>::replaceRightFront(T& x)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me - see slides for how
} // replaceRightFront

//-----------------------------------------------------------------------

template <class T>
void List2<T>::swapRights(List2& otherS)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me 
}	// swapRights

//-----------------------------------------------------------------------

template <class T>
inline Integer List2<T>::leftLength(void)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me
	//       You must end this with a 'return' 
	//       The return below does not provide the correct functionality for leftLength
	//       The return below is here so that this operation will compile correctly
	return 0;
}	// leftLength

//-----------------------------------------------------------------------

template <class T>
inline Integer List2<T>::rightLength(void)
{
	//! correspondence:
	//!	self = leftQ * rightQ
	//  You get to assume it holds at the beginning of the call to this operation
	//  You must gurantee it holds at the end of the call to this operation
	//  During the execution of this operation it does not have to hold

	// TODO: Finish me
	//       You must end this with a 'return' 
	//       The return below does not provide the correct functionality for leftLength
	//       The return below is here so that this operation will compile correctly
	return 0;
}	// rightLength

//-----------------------------------------------------------------------

//-----------------------------------------------------------------------

template <class T>
wostream& operator<<(wostream& os, List2<T>& s)
{
// Do not change this operation
#ifdef _DEBUG
	os << "[" << s.leftQ << "," << s.rightQ << "]";
#else
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
#endif

	return os;
}