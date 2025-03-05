#pragma once
#include "PreemptableQueue/PreemptableQueueKernel.hpp"

/*
	Realization of PreemptableQueue using ChainPosition
	Author: Dr. Holly
*/

#include "ChainPosition/ChainPosition.hpp"

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T>
class PreemptableQueue1 : public StdOps<PreemptableQueue1<T>>, public PreemptableQueueKernel<T>
		//! is modeled by string of T
		//! exemplar self
{
public: // Standard Operations
	PreemptableQueue1 ();
	PreemptableQueue1(const PreemptableQueue1& s) = delete;
	~PreemptableQueue1 ();
	void clear (void);
	void transferFrom (PreemptableQueue1& source);
	PreemptableQueue1& operator = (PreemptableQueue1& rhs);

	// PreemptableQueue1 Specific Operations
	void enqueue (T& x);
	void inject(T& x);
	void dequeue (T& x);
	void replaceFront (T& x);
	T& front(void);
	Integer length (void);
		//! ensures: length = |self|

	friend wostream& operator << <T>(wostream& os, PreemptableQueue1& q);
		//! updates os
		//! restores q

private: // Representation
	
	typedef ChainPosition1 <T> ChainPositionOfT;

	ChainPositionOfT preFront;
	ChainPositionOfT rear;
	Integer lengthOfQueue;

private: // Local Operations
	void createNewRep(void);
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::createNewRep(void)
{
	T temp;

	preFront.labelNew(temp);
	rear = preFront;
}   // createNewRep

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

template <class T>
PreemptableQueue1<T>::PreemptableQueue1 ()
{
	createNewRep();
}	// PreemptableQueue1

//-----------------------------------------------------------------------

template <class T>
PreemptableQueue1<T>::~PreemptableQueue1 ()
{
}	// ~PreemptableQueue1

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::clear(void)
{
	T temp;

	preFront.labelNew(temp);
	rear = preFront;
	lengthOfQueue = 0;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::transferFrom (PreemptableQueue1& source)
{
	preFront.transferFrom(source.preFront);
	rear.transferFrom(source.rear);
	lengthOfQueue.transferFrom(source.lengthOfQueue);

	source.createNewRep();
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
PreemptableQueue1<T>& PreemptableQueue1<T>::operator = (PreemptableQueue1& rhs)
{
	T x;
	ChainPositionOfT newPos, existingPos;

	preFront.labelNew(x);
	rear = preFront;

	existingPos = rhs.preFront;
	existingPos.applyTarget();
	while (!existingPos.isZero()) {
		x = existingPos.label();
		newPos.labelNew(x);
		rear.swapWithTarget(newPos);
		rear.applyTarget();
		existingPos.applyTarget();
	} // end while
	lengthOfQueue = rhs.lengthOfQueue;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::enqueue (T& x)
{
	ChainPositionOfT newPos;

	newPos.labelNew(x);
	rear.swapWithTarget(newPos);
	rear.applyTarget();
	lengthOfQueue++;
}	// enqueue

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::inject(T& x)
{
	ChainPositionOfT newPreFront;
	T temp;

	preFront.replaceLabel(x);
	newPreFront.labelNew(temp);
	newPreFront.swapWithTarget(preFront);
	preFront = newPreFront;
	lengthOfQueue++;
}	// inject

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::dequeue( T& x)
{
	preFront.applyTarget();
	preFront.replaceLabel(x);
	lengthOfQueue--;
}	// dequeue

//-----------------------------------------------------------------------

template <class T>
void PreemptableQueue1<T>::replaceFront (T& x)
{
	ChainPositionOfT pos;
	pos = preFront;
	pos.applyTarget();
	pos.replaceLabel(x);
}	// replaceFront

//-----------------------------------------------------------------------

template <class T>
T& PreemptableQueue1<T>::front(void)
{
	ChainPositionOfT pos;
	pos = preFront;
	pos.applyTarget();
	return pos.label();
}  // front

//-----------------------------------------------------------------------

template <class T>
Integer PreemptableQueue1<T>::length (void)
{
	return lengthOfQueue;
}	// length

//-----------------------------------------------------------------------

template <class T>
wostream& operator<< (wostream& os, PreemptableQueue1<T>& q)
{
	os << L"<";
	for (int k = 0, z = q.length(), lastItem = z - 1; k < z; k++) {
		T x;

		q.dequeue(x);
		os << x;
		q.enqueue(x);
		if (k < lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L">";
	return os;
} // operator<<



