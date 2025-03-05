#pragma once
/*
	List kernel component with primary methods.
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class ListOfT, class T>
class ListKernel
		//! ListOfT - type ListX<T>, where X is an implementation number
		//! T - type of ListKernel entries
		//!  
		//! Mathematical Subtypes:
		//! LIST_MODEL is (
		//!    left: string of T,
		//!    right : string of T
		//! )
		//! 
		//! Mathematical Model (abstract value and abstract invariant of self):
		//! type ListKernel is modeled by LIST_MODEL
		//! exemplar self
		//! initially 
		//!    ensures: self = (<>,<>)
{
public: // List Specific Operations
	virtual void moveToStart(void) = 0;
	//! updates self
	//! ensures: self.left = <>  and  self.right = #self.left * #self.right
	virtual void moveToFinish(void) = 0;
	//! updates self
	//! ensures: self.right = <>  and  self.left = #self.left * #self.right
	virtual void advance(void) = 0;
	//! updates self
	//! requires: self.right /= <>
	//! ensures: self.left * self.right = #self.left * #self.right  and
	//!          |self.left| = |#self.left| + 1
	virtual void addRightFront(T& x) = 0;
	//! updates self.right
	//! clears x
	//! ensures: self.left = #self.left  and  self.right = <#x> * #self.right
	virtual void removeRightFront(T& x) = 0;
	//! updates self.right
	//! replaces x
	//! requires: self.right /= <>
	//! ensures: self.left = #self.left  and
	//!          <x> = #self.right[0,1)  and 
	//!          self.right = #self.right[1,|#self.right|)
	virtual T& rightFront(void) = 0;
	//! restores self
	//! requires: self.right /= <>
	//! ensures: <rightFront> = self.right[0,1)
	virtual void replaceRightFront(T& x) = 0;
	//! updates self.right, x
	//! requires: self.right /= <>
	//! ensures: self.left = #self.left  and
	//!          <x> = #self.right[0,1)  and
	//!          self.right = <#x> * #self.right[1, |#self.right|)
	virtual void swapRights(ListOfT& otherS) = 0;
	//! updates self.right, otherS.right
	//! ensures: self.left = #self.left  and  otherS.left = #otherS.left  and
	//!          otherS.right = #self.right  and  self.right = #otherS.right
	virtual Integer leftLength(void) = 0;
	//! restores self
	//! ensures: leftLength = |self.left|
	virtual Integer rightLength(void) = 0;
	//! restores self
	//! ensures: rightLength = |self.right|
};
