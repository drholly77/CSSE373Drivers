#pragma once

/*
	Last-in-first-out (LIFO) stack kernel component with primary methods
*/

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class StackKernel
		//! T - type of StackKernel entries
		//! 
		//! Mathematical Model (abstract value and abstract invariant of self):
		//! type StackKernel is modeled by string of T
		//! exemplar self
		//! initially 
		//!    ensures: self = <>
{
public: // Stack Specific Operations
	virtual void push (T& x) = 0;
	virtual void pop (T& x) = 0;
	virtual void replaceTop(T& x) = 0;
	virtual T& top (void) = 0;
	virtual Integer length (void) = 0;
};