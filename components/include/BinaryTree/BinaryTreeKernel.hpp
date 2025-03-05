#pragma once

/*
	BinaryTree kernel component with primary methods
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class BinaryTreeOfT, class T>
class BinaryTreeKernel 
//! BinaryTreeKernel is modeled by tuple of
//!      label: T
//!      leftSubtree: BinaryTree1
//!      rightSubtree: BinaryTree1
//! exemplar self
//! 
//! initially 
//!      self = EMPTY
{
public: // BinaryTreeKernel Specific Operations
	virtual void compose(T& x, BinaryTreeOfT& left, BinaryTreeOfT& right) = 0;
	//! replaces self
	//! clears x, left, right
	//! ensures: self = (#x, #left, #right)
	virtual void decompose(T& x, BinaryTreeOfT& left, BinaryTreeOfT& right) = 0;
	//! clears self
	//! replaces x, left, right
	//! requires: self /= EMPTY
	//! ensures: #self = (x, left, right)
	virtual T& label(void) = 0;
	//! restores self
	//! requires: self /= EMPTY
	//! ensures: label = self.label
	virtual Integer size(void) = 0;
	//! restores self
	//! ensures: size = |self|
	virtual Integer height(void) = 0;
	//! restores self
	//! ensures: height = height of self
};
