#pragma once
/*
	BoundedList kernel component with primary methods.
*/

//-----------------------------------------------------------------------
// Template Class Specification	
//-----------------------------------------------------------------------

template <class BoundedListOfT, class T, int maxLength>
class BoundedListKernel 		
		//! BoundedListOfT - type BoundedListX<T>, where X is an implementation number
		//! requires 1 <= maxLength
		//! T - type of BoundedListKernel entries
		//! maxLength - max size of list allowed
		//!  
		//! Mathematical Subtypes:
		//! BOUNDED_LIST_MODEL is (
		//!    left: string of T,
		//!    right : string of T
		//! )
		//! 
		//! Mathematical Model (abstract value and abstract invariant of self):
		//! type BoundedListKernel is modeled by BOUNDED_LIST_MODEL
		//! exemplar self
		//! initially 
		//!    ensures: self = (<>,<>)	
		//! //! constraint |self.left| + |self.right| <= maxLength
{
public: // BoundedList Specific Operations
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
    //! requires: |self.left| + |self.right| + 1 <= maxLength
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
	virtual void swapRights(BoundedListOfT& otherS) = 0;
	//! updates self.right, otherS.right
	//! ensures: self.left = #self.left  and  otherS.left = #otherS.left  and
	//!          otherS.right = #self.right  and  self.right = #otherS.right
	virtual Integer leftLength(void) = 0;
	//! restores self
	//! ensures: leftLength = |self.left|
	virtual Integer rightLength(void) = 0;
	//! restores self
	//! ensures: rightLength = |self.right|
	virtual Integer remainingCapacity(void) = 0;
	//! restores self
	//! ensures: remainingCapacity  = maxLength - (|self.left| + |self.right|)
};
