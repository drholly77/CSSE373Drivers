#pragma once

/*
	BoundedSet kernel component with primary methods
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T, int maxSize>
class BoundedSetKernel
		//! T - type of SetKernel entries
		//! 
		//! Mathematical Model (abstract value and abstract invariant of self):
		//! type SetKernel is modeled by finite set of T
		//! exemplar self
		//! initially 
		//!    ensures: self = {}
{
public: // SetKernel Specific Operations
	virtual void add (T& x) = 0;
	//! updates self
	//! clears x
	//! requires: x is not in self
	//! ensures: self = #self union {#x}
	virtual void remove (T& xFromClient, T& xFromSet) = 0;
	//! updates self
	//! restores xFromClient
	//! replaces xFromSet
	//! requires: xFromClient is in self
	//! ensures: self = #self \ {xFromSet}  and  xFromSet = xFromClient
	virtual void removeAny (T& x) = 0;
	//! updates self
	//! replaces x
	//! requires: |self| > 0
	//! ensures: self = #self \ {x}
	virtual Boolean contains (T& x) = 0;
	//! restores self, x
	//! ensures: contains = (x is in self)
	virtual Integer size (void) = 0;
	//! restores self
	//! ensures: size = |self|
	virtual Integer remainingCapacity(void) = 0;
	//! restores self
	//! ensures: remainingCapacity = (maxSize - |self|)
};
