#pragma once

/*
	Set kernel component with primary methods
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T>
class SetKernel
		//! T - type of SetKernel entries
		//! 
		//! Mathematical Model (abstract value and abstract invariant of self):
		//! type SetKernel is modeled by finite set of T
		//! exemplar self
		//! initially 
		//!    ensures: self = {}
{
public: // SetKernel Specific Operations
	void add (T& x);
	//! updates self
	//! clears x
	//! requires: x is not in self
	//! ensures: self = #self union {#x}
	void remove (T& xFromClient, T& xFromSet);
	//! updates self
	//! restores xFromClient
	//! replaces xFromSet
	//! requires: xFromClient is in self
	//! ensures: self = #self \ {xFromSet}  and  xFromSet = xFromClient
	void removeAny (T& x);
	//! updates self
	//! replaces x
	//! requires: |self| > 0
	//! ensures: self = #self \ {x}
	Boolean contains (T& x);
	//! restores self, x
	//! ensures: contains = (x is in self)
	Integer size (void);
	//! restores self
	//! ensures: size = |self|
};
