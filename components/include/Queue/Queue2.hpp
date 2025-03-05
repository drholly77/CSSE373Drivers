#pragma once
#include "Queue/QueueKernel.hpp"
#include "List/List1.hpp"

/*
	Realization of Queue using List
*/

template <class T>
class Queue2 : public StdOps<Queue2<T>>, public QueueKernel<T>
{
public: // Standard Operations
	Queue2 ();
	Queue2(const Queue2& s) = delete;
	~Queue2 ();
	void clear (void);
	void transferFrom (Queue2& source);
	Queue2& operator = (Queue2& rhs);

	// Queue2 Specific Operations
	void enqueue (T& x);
	void dequeue (T& x);
	void replaceFront (T& x);
	T& front(void);
	Integer length (void);

	friend wostream& operator<< <T> (wostream& os, Queue2<T>& q);
		//! updates os
		//! restores q

private: // Representation

	typedef List1 <T> ListOfT;

	ListOfT s;
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Local Operations
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

template <class T>
Queue2<T>::Queue2()
{
}	// Queue2

//-----------------------------------------------------------------------

template <class T>
Queue2<T>::~Queue2()
{
}	// ~Queue2

//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::clear(void)
{
	s.clear();
}	// clear

//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::transferFrom (Queue2& source)
{
	s.transferFrom(source.s);
}

//-----------------------------------------------------------------------

template <class T>
Queue2<T>& Queue2<T>::operator = (Queue2& rhs)
{
	s = rhs.s;
	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::enqueue (T& x)
{
	s.moveToFinish();
	s.addRightFront(x);
}	// enqueue

//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::dequeue (T& x)
{
	s.moveToStart();
	s.removeRightFront(x);
}	// dequeue

//-----------------------------------------------------------------------

template <class T>
void Queue2<T>::replaceFront(T& x)
{
	s.moveToStart();
	s.replaceRightFront(x);
}	// replaceFront

//-----------------------------------------------------------------------

template <class T>
T& Queue2<T>::front(void)
{
	s.moveToStart();
	return s.rightFront();
}  // front

//-----------------------------------------------------------------------

template <class T>
Integer Queue2<T>::length (void)
{
	return s.leftLength() + s.rightLength();
}	// size

//-----------------------------------------------------------------------

template <class T>
wostream& operator<<(wostream& os, Queue2<T>& q)
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
}