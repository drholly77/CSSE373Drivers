#pragma once
#include "Sequence/SequenceKernel.hpp"
#include "Queue/Queue1.hpp"

/*
	Realization of Sequence layered on Queue
*/

template <class T>
class Sequence4 : public StdOps<Sequence4<T>>, public SequenceKernel<Sequence4<T>, T>
{
public: // Standard Operations
	Sequence4();
	Sequence4(const Sequence4& s) = delete;
	~Sequence4();
	void clear(void);
	void transferFrom(Sequence4& source);
	Sequence4& operator = (Sequence4& rhs);

	// Sequence4 Specific Operations
	void add(Integer pos, T& x);
	void remove(Integer pos, T& x);
	void replaceEntry(Integer pos, T& x);
	T& entry(Integer pos);
	void append(Sequence4& sToAppend);
	void split(Integer pos, Sequence4& receivingS);
	Integer length(void);

	friend wostream & operator<< <T>(wostream &os, Sequence4& s);
		//! updates os
		//! restores s


private: // representation

	typedef Queue1 <T> QueueOfT;

	QueueOfT qBefore;
	QueueOfT qAfter;

		//! corresponence
		//!    self = qBefore * qAfter

private: // local operations
	void moveElements(QueueOfT& toQ, QueueOfT& fromQ, Integer count);
};


//-----------------------------------------------------------------------
// local Operations
//-----------------------------------------------------------------------

template <class T>
void Sequence4<T>::moveElements(QueueOfT& toQ, QueueOfT& fromQ, Integer count)
	//! alters toQ, fromQ
	//! preserves count
	//! requires:  0 <= count <= |fromQ|
	//!  ensures: toQ = #toQ[0, |toQ|) * #fromQ[0, count) and fromQ = #fromQ[count, |fromQ|)
{
	for (int i = 0; i < count; i++) {
		T x;
		fromQ.dequeue(x);
		toQ.enqueue(x);
	} // end for
}	// rotateElements

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
Sequence4<T>::Sequence4()
{
}	// Sequence4

//-----------------------------------------------------------------------

template <class T>
Sequence4<T>::~Sequence4()
{
}	// ~Sequence4

//-----------------------------------------------------------------------

template <class T>
void Sequence4<T>::transferFrom(Sequence4& source)
{
	qBefore.transferFrom(source.qBefore);
	qAfter.transferFrom(source.qAfter);
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
Sequence4<T>& Sequence4<T>::operator = (Sequence4& rhs)
{
	qBefore = rhs.qBefore;
	qAfter = rhs.qAfter;
	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void Sequence4<T>::clear(void)
{
	qBefore.clear();
	qAfter.clear();
}	// clear

//-----------------------------------------------------------------------

template <class T>
void Sequence4<T>::add(Integer position, T& x)
{
	moveElements(qBefore, qAfter, qAfter.length());
	moveElements(qAfter, qBefore, position);
	qAfter.enqueue(x);
	moveElements(qAfter, qBefore, qBefore.length());
}	// add

//-----------------------------------------------------------------------

template <class T>
void Sequence4<T>::remove(Integer position, T& x)
{
	moveElements(qBefore, qAfter, qAfter.length());
	moveElements(qAfter, qBefore, position);
	qBefore.dequeue(x);
	moveElements(qAfter, qBefore, qBefore.length());
}	// remove

//-----------------------------------------------------------------------

template <class T>
void Sequence4<T>::replaceEntry(Integer position, T& x)
{
	moveElements(qBefore, qAfter, qAfter.length());
	moveElements(qAfter, qBefore, position);
	qAfter.enqueue(x);
	qBefore.dequeue(x);
	moveElements(qAfter, qBefore, qBefore.length());
}	// replaceEntry

//-----------------------------------------------------------------------

template <class T>
T& Sequence4<T>::entry(Integer position)
{
	moveElements(qBefore, qAfter, qAfter.length());
	qAfter.transferFrom(qBefore);
	moveElements(qBefore, qAfter, position);
	return qAfter.front();
}	// entry

//-----------------------------------------------------------------------

template <class T>
void Sequence4<T>::append(Sequence4& otherS)
{
	moveElements(qBefore, qAfter, qAfter.length());
	moveElements(otherS.qBefore, otherS.qAfter, otherS.qAfter.length());
	moveElements(qBefore, otherS.qBefore, otherS.qBefore.length());
}	// append

//-----------------------------------------------------------------------

template <class T>
void Sequence4<T>::split(Integer position,	Sequence4& receivingS)
{
	receivingS.qBefore.clear();
	receivingS.qAfter.clear();
	moveElements(qBefore, qAfter, qAfter.length());
	qAfter.transferFrom(qBefore);
	moveElements(qBefore, qAfter, position);
	moveElements(receivingS.qAfter, qAfter, qAfter.length());
}	// split

//-----------------------------------------------------------------------

template <class T>
Integer Sequence4<T>::length(void)
{
	return qBefore.length() + qAfter.length();
}	// length

//-----------------------------------------------------------------------

template <class T>
wostream & operator<<(wostream &os, Sequence4<T>& s)
{
	os << L"<";
	for (int p = 0, z = s.length(), lastItem = z - 1; p < z; p++) {
		T x;

		os << s.entry(p);
		if (p < lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L">";

	return os;
} // operator<<

