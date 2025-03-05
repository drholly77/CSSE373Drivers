#pragma once

//
// realization of Sequence Template by layering on OWL
//

#include "Sequence/SequenceKernel.hpp"
#include "List\List1.hpp"

template <class T>
class Sequence3 : public StdOps<Sequence3<T>>, public SequenceKernel<Sequence3<T>, T>
{
public: // standard Operations
	Sequence3 ();
	Sequence3(const Sequence3& s) = delete;
	~Sequence3 ();
	void clear (void);
	void transferFrom(Sequence3& source);
	Sequence3& operator = (Sequence3& rhs);

	// Sequence3 Specific Operations
	void add (Integer pos, T& x);
	void remove (Integer pos, T& x);
	void replaceEntry (Integer pos, T& x);
	T& entry (Integer pos);
	void append (Sequence3& sToAppend);
	void split (Integer pos, Sequence3& receivingS);
	Integer length (void);

	friend wostream & operator<< <T>(wostream &os, Sequence3& s);
	//! updates os
	//! restores s

private: // representation
	typedef List1 <T> ListOfT;
	ListOfT s;

		//! convention
		//!    s's fence can be anywhere

		//! corresponence
		//!    self = s.left  o  s.right

private: // local operations
	void moveToPosition(ListOfT& s1, Integer position);
};


//-----------------------------------------------------------------------
// local Operations
//-----------------------------------------------------------------------

template <class T>
void Sequence3<T>::moveToPosition(ListOfT& s1, Integer position)
{
	s1.moveToStart();
	for (int i = 0; i < position; i++) {
		s1.advance();
	} // end for
}	// moveToPosition

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
Sequence3<T>::Sequence3()
{
}	// Sequence3

//-----------------------------------------------------------------------

template <class T>
Sequence3<T>::~Sequence3()
{
}	// ~Sequence3

//-----------------------------------------------------------------------

template <class T>
void Sequence3<T>::transferFrom(Sequence3& source)
{
	s.transferFrom(source.s);
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
Sequence3<T>& Sequence3<T>::operator = (Sequence3& rhs)
{
	s = rhs.s;
	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class T>
void Sequence3<T>::clear(void)
{
	s.clear();
}	// clear

//-----------------------------------------------------------------------

template <class T>
void Sequence3<T>::add(Integer position, T& x)
{
	moveToPosition(s, position);
	s.addRightFront(x);
}	// add

//-----------------------------------------------------------------------

template <class T>
void Sequence3<T>::remove(Integer position, T& x)
{
	moveToPosition(s, position);
	s.removeRightFront(x);
}	// remove

//-----------------------------------------------------------------------

template <class T>
void Sequence3<T>::replaceEntry(Integer position, T& x)
{
	moveToPosition(s, position);
	s.replaceRightFront(x);
}	// replaceEntry

//-----------------------------------------------------------------------

template <class T>
T& Sequence3<T>::entry(Integer position)
{
	moveToPosition(s, position);
	return(s.rightFront());
}	// entry

//-----------------------------------------------------------------------

template <class T>
void Sequence3<T>::append(Sequence3& otherS)
{
	s.moveToFinish();
	otherS.s.moveToStart();
	s.swapRights(otherS.s);
}	// append

//-----------------------------------------------------------------------

template <class T>
void Sequence3<T>::split(Integer position,	Sequence3& receivingS)
{
	moveToPosition(s, position);
	receivingS.s.clear();
	s.swapRights(receivingS.s);
}	// split

//-----------------------------------------------------------------------

template <class T>
Integer Sequence3<T>::length(void)
{
	s.moveToStart();
	return(s.rightLength());
}	// length

//-----------------------------------------------------------------------

template <class T>
wostream & operator<<(wostream &os, Sequence3<T>& s)
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

#ifndef NDEBUG
	os << endl;
	os << s.s << endl;
#endif

	return (os);
} // operator<<

