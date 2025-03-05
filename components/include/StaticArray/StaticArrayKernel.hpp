#pragma once

/*
	StaticArray kernel component with primary methods
*/

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T, int lowerBound, int upperBound>
class StaticArrayKernel
	//! StaticArrayKernel is modeled by function from integer to T
	//! constraint: for all i: integer
	//!    ((i < lowerBound) or (i > upperBound) 
	//!    implies (self(i) = T.init))
	//! exemplar self
{
public: // PartitionableArray Specific Operations
	virtual void getBounds(Integer& lower, Integer& upper) = 0;
		//! restores self
		//! replaces lower, upper
		//! ensures: lower = lowerBound  and  upper = upperBound
	virtual T& operator [] (Integer index) = 0;
		//! restores self, index
		//! requires: index >= lowerBound  and  index <= upperBound
		//! ensures: operator [] = self(index)
};