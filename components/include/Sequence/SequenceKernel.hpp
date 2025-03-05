#pragma once

/*
	Sequence kernel component with primary methods
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class SequenceOfT, class T>
class SequenceKernel
		//! SequenceOfT - type SequenceX<T>, where X is an implementation number
		//! T - type of SequenceKernel entries
		//! 
		//! Mathematical Model (abstract value and abstract invariant of self):
		//! type SequenceKernel is modeled by string of T
		//! exemplar self
		//! initially 
		//!    ensures: self = <>
{
public: // Sequence Specific Operations
	virtual void add (Integer pos, T& x) = 0;
	//! updates self
	//! restores pos
	//! clears x
	//! requires: 0 <= pos <= |self|
	//! ensures: self = #self[0, pos) * <#x> * #self[pos, |#self|)
	virtual void remove (Integer pos, T& x) = 0;
	//! updates self
	//! restores pos
	//! replaces x
	//! requires: 0 <= pos < |self|
	//! ensures: <x> = #self[pos, pos+1) and
	//!          self = #self[0, pos) * #self[pos+1, |#self|)
	virtual void replaceEntry (Integer pos, T& x) = 0;
	//! updates self, x
	//! restores pos
	//! requires: 0 <= pos < |self|
	//! ensures: <x> = #self[pos, pos+1)  and
	//!          self = #self[0, pos) * <#x> * #self[pos+1, |#self|)
	virtual T& entry (Integer pos) = 0;
	//! restores self, pos
	//! requires: 0 <= pos < |self|
	//! ensures: <entry> = self[pos, pos+1)
	virtual void append (SequenceOfT& sToAppend) = 0;
	//! updates self
	//! clears sToAppend
	//! ensures: self = #self * sToAppend
	virtual void split (Integer pos, SequenceOfT& receivingS) = 0;
	//! updates self
	//! restores pos
	//! replaces receivingS
	//! requires: 0 <= pos <= |self|
	//! ensures: self = #self[0, pos) and receivingS = #self[pos, |self|)
	virtual Integer length (void) = 0;
	//! restores self
	//! ensures: length = |self|
};
