#pragma once
#include "Sequence/SequenceKernel.hpp"
#include "ChainPosition/ChainPosition.hpp"

/*
	Realization of Sequence layered on ChainPosition
*/

template <class T>
class Sequence1 : public StdOps<Sequence1<T>>, public SequenceKernel<Sequence1<T>, T>
{
public: // Standard Operations
	Sequence1 ();
	Sequence1(const Sequence1& s) = delete;
	~Sequence1 ();
	void clear (void);
	void transferFrom (Sequence1& source);
	Sequence1& operator = (Sequence1& rhs);

	// Sequence1 Specific Operations
	void add (Integer pos, T& x);
	void remove (Integer pos, T& x);
	void replaceEntry (Integer pos, T& x);
	T& entry (Integer pos);
	void append (Sequence1& sToAppend);
	void split (Integer pos, Sequence1& receivingS);
	Integer length (void);

	friend wostream& operator<< <T>(wostream& os, Sequence1& s);
		//! updates os
		//! restores s

private: // Representation

	typedef ChainPosition1 <T> ChainPositionOfT;

	ChainPositionOfT preFront;
	Integer lengthOfSeq;

private: // Local Operations
	void moveToPosition (ChainPositionOfT& chainPos, Integer pos);
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Local Operations
//-----------------------------------------------------------------------

template <class T>
void Sequence1<T>::moveToPosition (ChainPositionOfT& chainPos, Integer pos)
{
	chainPos = preFront;
	for (int k = 0; k < pos; k++) {
		chainPos.applyTarget ();
	}	// end for
}	// moveToPosition

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

template <class T>
Sequence1<T>::Sequence1 ()
{
	T temp;

	preFront.labelNew (temp);
}	// Sequence1

//-----------------------------------------------------------------------

template <class T>
Sequence1<T>::~Sequence1 ()
{
}	// ~Sequence1

//-----------------------------------------------------------------------

template <class T>
void Sequence1<T>::clear(void)
{
	T temp;

	preFront.labelNew(temp);
	lengthOfSeq = 0;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void Sequence1<T>::transferFrom(Sequence1& source)
{
	preFront.transferFrom(source.preFront);
	lengthOfSeq.transferFrom(source.lengthOfSeq);
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
Sequence1<T>& Sequence1<T>::operator = (Sequence1& rhs)
{
	ChainPositionOfT newPos, oldPos, current;
	T x;

	preFront.labelNew (x);
	current = preFront;

	oldPos = rhs.preFront;
	oldPos.applyTarget ();
	while (!oldPos.isZero ()) {
		x = oldPos.label();
		newPos.labelNew (x);
		current.swapWithTarget (newPos);
		current.applyTarget ();
		oldPos.applyTarget ();
	} // end while
	lengthOfSeq = rhs.lengthOfSeq;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void Sequence1<T>::add (Integer pos, T& x)
{
	ChainPositionOfT addPos;
	ChainPositionOfT newPos, temp;

	moveToPosition (addPos, pos);
	newPos.labelNew (x);
	temp = newPos;
	addPos.swapWithTarget (temp);
	newPos.swapWithTarget (temp);
	lengthOfSeq++;
}	// add

//-----------------------------------------------------------------------

template <class T>
void Sequence1<T>::remove (Integer pos, T& x)
{
	ChainPositionOfT removePos, temp;

	moveToPosition (removePos, pos);

	temp = removePos;
	temp.applyTarget ();
	temp.replaceLabel (x);
	temp.applyTarget ();
	removePos.swapWithTarget (temp);
	lengthOfSeq--;
}	// remove

//-----------------------------------------------------------------------

template <class T>
void Sequence1<T>::replaceEntry (Integer pos, T& x)
{
	ChainPositionOfT swapPos;

	moveToPosition (swapPos, pos + 1);

	swapPos.replaceLabel (x);
}	// replaceEntry

//-----------------------------------------------------------------------

template <class T>
T& Sequence1<T>::entry (Integer pos)
{
	ChainPositionOfT accessPos;

	moveToPosition (accessPos, pos + 1);
	return accessPos.label();
}	// entry

//-----------------------------------------------------------------------

template <class T>
void Sequence1<T>::append (Sequence1& sToAppend)
{
	ChainPositionOfT endPos, temp;

	moveToPosition (endPos, lengthOfSeq);

	sToAppend.preFront.swapWithTarget (temp);
	endPos.swapWithTarget (temp);
	lengthOfSeq += sToAppend.lengthOfSeq;
	sToAppend.lengthOfSeq = 0;
}	// append

//-----------------------------------------------------------------------

template <class T>
void Sequence1<T>::split (Integer pos, Sequence1& receivingS)
{
	ChainPositionOfT splitPos, temp;

	moveToPosition (splitPos, pos);
	splitPos.swapWithTarget (temp);
	receivingS.preFront.swapWithTarget (temp);
	receivingS.lengthOfSeq = lengthOfSeq - pos;
	lengthOfSeq = pos;
}	// split

//-----------------------------------------------------------------------

template <class T>
Integer Sequence1<T>::length (void)
{
	return lengthOfSeq;
}	// length

//-----------------------------------------------------------------------

template <class T>
wostream& operator<<(wostream& os, Sequence1<T>& s)
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