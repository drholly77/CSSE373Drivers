#pragma once

/*
	CeramicArray kernel component with primary methods
*/

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class CeramicArrayKernel
	//! CeramicArray1 is modeled by tuple of
	//!   contents: function from integer to T
	//!   lowerBound: integer
	//!   upperBound: integer
	//! constraint: for all k: integer
	//!    ((k < self.lowerBound) or (k > self.upperBound) 
	//!    implies T.Init(self.contents(k))
	//! exemplar self
	//! initially
	//! ensures: self.lowerBound = 0  and  self.upperBound = 0  and
	//!          T.Init(self.contents(0))
{
public: // PartitionableArray Specific Operations
	virtual void setBounds(Integer lower, Integer upper) = 0;
	//! updates self
	//! restores lower, upper
	//! requires: lower <= upper
	//!  ensures: self.lowerBound = lower  and  self.upperBound = upper  and
	//!           for all k: integer
	//!                 ((k < self.lowerBound) or (k > self.upperBound) 
	//!                 implies T.Init(self.contents(k))

	virtual void getBounds(Integer& lower, Integer& upper) = 0;
	//! restores self
	//! replaces lower, upper
	//! ensures: lower = self.lowerBound  and  upper = self.upperBound

	virtual T& operator [] (Integer index) = 0;
	//! restores self, index
	//! requires: index >= self.lowerBound  and  index <= self.upperBound
	//! ensures: operator [] = self.contents(index)
};