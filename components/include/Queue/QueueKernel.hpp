#pragma once

/*
	First-in-first-out (FIFO) queue kernel component with primary methods
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T>
class QueueKernel
		//! T - type of QueueKernel entries
		//! 
		//! Mathematical Model (abstract value and abstract invariant of self):
		//! type QueueKernel is modeled by string of T
		//! exemplar self
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
};
