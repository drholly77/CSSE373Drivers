#pragma once

/*
	First-in-first-out (FIFO) bounded queue kernel component with primary methods
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T, int maxLength>
class BoundedQueueKernel
		//! requires 1 <= maxLength
		//! T - type of BoundedQueueKernel entries
		//! maxLength - max size of queue allowed
		//! 
		//! Mathematical Model (abstract value and abstract invariant of self):
		//! type BoundedQueueKernel is modeled by string of T
		//! exemplar self
		//! constraint |self| <= maxLength
		//! initially 
		//!    ensures: self = <>
{
public: // Queue Specific Operations
	virtual void enqueue (T& x) = 0;
	//! updates self
	//! clears x
	//! ensures: self = #self * <#x>
	virtual void dequeue (T& x) = 0;
	//! updates self
	//! replaces x
	//! requires: self /= <>
	//! ensures: <x> = #self[0,1)  and  
	//!          self = #self[1,|#self|)
	virtual void replaceFront (T& x) = 0;
	//! updates self, x
	//! requires: self /= <>
	//! ensures: <x> = #self[0,1) and
	//!          self = <#x> * #self[1,|#self|)
	virtual T& front(void) = 0;
	//! restores self
	//! requires: self /= <>
	//! ensures: <front> = #self[0,1)
	virtual Integer length (void) = 0;
	//! restores self
	//! ensures: length = |self|
	virtual Integer remainingCapacity(void) = 0;
	//! restores self
	//! ensures: remainingCapacity = maxLength - |self|
};
