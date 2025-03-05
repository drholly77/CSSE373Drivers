#pragma once
/*
	Standard Ops Interface for all Formal Mehthods C++ classes
	Author: Dr. Holly
*/

//-----------------------------------------------------------------------
// Standard Operations used by all Formal Methods C++ classes
//-----------------------------------------------------------------------
template <class T>
class StdOps
{
public: // Standard Operations
	virtual void clear (void) = 0;
		//! clears self
	virtual void transferFrom (T& source) = 0;
		//! replaces self
		//! clears source
		//! ensures: self = #source
	virtual T& operator = (T& rhs) = 0;
		//! replaces self
		//! restores rhs
		//! ensures: self = rhs

	T* operator & (void) = delete;
	const T * operator & (void) const = delete;
private:
	// Note: Each subclass must delete T's copy constructor

};

