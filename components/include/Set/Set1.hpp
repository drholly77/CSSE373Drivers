#pragma once
#include "Set/SetKernel.hpp"
#include "ChainPosition/ChainPosition.hpp"
/*
	Realization of Set layered on Chain Position
*/

template <class T, Boolean (*areEqual)(T&, T&)>
class Set1 : public StdOps<Set1<T, areEqual>>, public SetKernel<T>
{
public: // Standard Operations
	Set1();
	Set1(const Set1& s) = delete;
	~Set1();
	void clear(void);
	void transferFrom(Set1& source);
	Set1& operator = (Set1& rhs);

	// Set1 Specific Operations
	void add(T& x);
	void remove(T& xFromClient, T& xFromSet);
	void removeAny(T& x);
	Boolean contains(T& x);
	Integer size(void);

	friend wostream& operator<< <T, areEqual>(wostream& os, Set1& s);
	//! updates os
	//! restores s

private: // Representation
	typedef ChainPosition1 <T> ChainPositionOfT;

	ChainPositionOfT chain;
	Integer sizeOfSet;

private: // Local Operations
	void createNewRep(void);
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
void Set1<T, areEqual>::createNewRep(void)
{
	ChainPositionOfT smartPosition;
	T x;

	smartPosition.labelNew(x);
	chain.transferFrom(smartPosition);
}   // createNewRep

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------


// convention: chain == smartPosition

template <class T, Boolean (*areEqual)(T&, T&)>
Set1<T, areEqual>::Set1()
{
	createNewRep();
}	// Set1

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
Set1<T, areEqual>::~Set1()
{
}	// ~Set1

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
void Set1<T, areEqual>::clear(void)
{
	chain.clear();
	sizeOfSet = 0;
	createNewRep();
}	// clear

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
void Set1<T, areEqual>::transferFrom(Set1& source)
{
	chain.transferFrom(source.chain);
	sizeOfSet.transferFrom(source.sizeOfSet);

	source.createNewRep();
} // transferFrom

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
Set1<T, areEqual>& Set1<T, areEqual>::operator = (Set1& rhs)
{
	ChainPositionOfT newPos, oldPos, current;
	T x;

	chain.labelNew(x);
	current = chain;

	oldPos = rhs.chain;
	oldPos.applyTarget();
	while (!oldPos.isZero()) {
		x = oldPos.label();
		newPos.labelNew(x);
		current.swapWithTarget(newPos);
		current.applyTarget();
		oldPos.applyTarget();
	} // end while
	sizeOfSet = rhs.sizeOfSet;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
void Set1<T, areEqual>::add(T& x)
{
	ChainPositionOfT newPosition;
	ChainPositionOfT firstPosition;

	chain.swapWithTarget(firstPosition);

	newPosition.labelNew(x);
	newPosition.swapWithTarget(firstPosition);
	chain.swapWithTarget(newPosition);

	sizeOfSet++;
}	// add

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
void Set1<T, areEqual>::remove(T& xFromClient, T& xFromSet)
{
	ChainPositionOfT trailingPosition;
	ChainPositionOfT currentPosition;

	trailingPosition = chain;
	currentPosition = trailingPosition;
	currentPosition.applyTarget();

	while (!areEqual(xFromClient, currentPosition.label())) {
		trailingPosition = currentPosition;
		currentPosition.applyTarget();
	}  // end while
	currentPosition.replaceLabel(xFromSet);

	currentPosition.applyTarget();
	trailingPosition.swapWithTarget(currentPosition);

	sizeOfSet--;
}	// remove

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
void Set1<T, areEqual>::removeAny(T& x)
{
	ChainPositionOfT position;

	position = chain;
	position.applyTarget();

	position.replaceLabel(x);
	position.applyTarget();
	chain.swapWithTarget(position);

	sizeOfSet--;
}	// removeAny

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
Boolean Set1<T, areEqual>::contains(T& x)
{
	ChainPositionOfT position;

	position = chain;
	position.applyTarget();

	while (!position.isZero() && !areEqual(x, position.label())) {
		position.applyTarget();
	}	// end while

	return !position.isZero();
}	// contains

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
Integer Set1<T, areEqual>::size(void)
{
	return sizeOfSet;
}	// size

//-----------------------------------------------------------------------

template <class T, Boolean (*areEqual)(T&, T&)>
wostream& operator<<(wostream& os, Set1<T, areEqual>& s)
{
	Set1<T, areEqual> temp;

	os << L"{";
	for (int k = 0, z = s.size(), lastItem = z - 1; k < z; k++) {
		T x;

		s.removeAny(x);
		os << x;
		temp.add(x);
		if (k < lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L"}";

	s.transferFrom(temp);
	return os;
} // operator<<