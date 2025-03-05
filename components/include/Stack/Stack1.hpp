#pragma once
#include "Stack/StackKernel.hpp"
#include "ChainPosition/ChainPosition.hpp"

/*
	Realization of Stack using ChainPosition
*/

template <class T>
class Stack1 : public StdOps<Stack1<T>>, public StackKernel<T>
{
public: // standard Operations
	Stack1 ();
	Stack1(const Stack1& s) = delete;
	~Stack1 ();
	void clear (void);
	void transferFrom(Stack1& source);
	Stack1& operator = (Stack1& rhs);

	// Stack1 Specific Operations
	void push (T& x);
	void pop (T& x);
	void replaceTop(T& x);
	T& top (void);
	Integer length (void);
	
	friend wostream & operator<< <T>(wostream &os, Stack1& s);
	//! updates os
	//! restores s

private: // representation
	typedef ChainPosition1 <T> ChainPositionOfT;
	
	ChainPositionOfT topOfStack;
	Integer lengthOfStack;
};
//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
Stack1<T>::Stack1 ()
{
}	// Stack1

//-----------------------------------------------------------------------

template <class T>
Stack1<T>::~Stack1 ()
{
}	// ~Stack1

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::transferFrom(Stack1& source)
{
	topOfStack.transferFrom(source.topOfStack);
	lengthOfStack.transferFrom(source.lengthOfStack);
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
Stack1<T>& Stack1<T>::operator = (Stack1& rhs)
{
	ChainPositionOfT newPos, oldPos, current;
	T x;

	oldPos = rhs.topOfStack;
	if (!oldPos.isZero()){
		// if rhs is not empty, set up first position in lhs
		x = oldPos.label();
		oldPos.applyTarget();
		current.labelNew(x);
		topOfStack = current;
	} else {
		// rhs is empty, clear out lhs
		topOfStack.clear ();
	} // end if

	while (!oldPos.isZero ()) {
		x = oldPos.label();
		newPos.labelNew (x);
		current.swapWithTarget (newPos);
		current.applyTarget();
		oldPos.applyTarget ();
	} // end while
	lengthOfStack = rhs.lengthOfStack;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::clear (void)
{
   topOfStack.clear ();
   lengthOfStack = 0;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::push (T& x)
{
	ChainPositionOfT newPos;

	newPos.labelNew (x);
	newPos.swapWithTarget (topOfStack);
	topOfStack.transferFrom(newPos);
	lengthOfStack++;
}	// push

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::pop (T& x)
{
	ChainPositionOfT oldPos;

	oldPos = topOfStack;
	topOfStack.applyTarget();
	oldPos.replaceLabel(x);
	lengthOfStack--;
}	// pop

//-----------------------------------------------------------------------

template <class T>
void Stack1<T>::replaceTop (T& x)
{
	topOfStack.replaceLabel(x);
}	// replaceTop

//-----------------------------------------------------------------------

template <class T>
T& Stack1<T>::top ()
{
   return topOfStack.label();
}  // top

//-----------------------------------------------------------------------

template <class T>
Integer Stack1<T>::length (void)
{
	return lengthOfStack;
}	// length

//-----------------------------------------------------------------------

template <class T>
wostream & operator<<(wostream &os, Stack1<T>& s)
{
	Stack1<T> temp;

	os << L"<";
	for (int i = 0, z = s.length(), lastItem = z - 1; i < z; i++) {
		T x;

		os << s.top();
		s.pop(x);
		temp.push(x);
		if (i < lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L">";

	for (int i = 0, z = temp.length(); i < z; i++) {
		T x;

		temp.pop(x);
		s.push(x);
	} // end for
	return os;
} // operator<<

