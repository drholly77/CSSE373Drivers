#pragma once

/*
	First-in-first-out (FIFO) queue kernel component with primary methods
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T>
class SortingMachineKernel
    //! SortingMachine1 is modeled by (
    //!      contents: FiniteMultiSet(T)
    //!      inserting: boolean
    //!   )
    //! exemplar self
	//! initially 
	//!    ensures: ({},true)

    //! math operation IS_FIRST (
    //!          s: FiniteMultiSet(T),
    //!          x: T
    //!      ): boolean
    //!      definition
    //!          x is in s  and
    //!          for all y: Item where (y is in s)
    //!             (areOrdered (x, y))

    //! 
    //! Boolean areOrdered (T& lhs, T& rhs)
    //! restores lhs, rhs
    //!   areOrdered returns true iff the two items compared
    //!      are in order relative to each other.
    //!   lhs stands for left hand side
    //!   rhs stands for right hand side
{
public: // SortingMachine Specific Operations

    virtual void add(T& x) = 0;
    //! updates self.contents
    //! clears x
    //! requires: self.inserting
    //! ensures: self.contents = #self.contents  union  {#x}  and
    //!          self.inserting = true
    virtual void changeToExtractionMode(void) = 0;
    //! updates self.inserting
    //! requires: self.inserting
    //! ensures: self.inserting = false  and  self.contents = #self.contents
    virtual void removeFirst(T& x) = 0;
    //! updates self.contents
    //! replaces x
    //! requires: not self.inserting  and  |self.contents| > 0
    //! ensures: IS_FIRST (#self.contents, x)  and
    //!          self.contents = #self.contents \ {x}  and
    //!          self.inserting = false
    virtual Integer size(void) = 0;
    //! restores self
    //! ensures: size = |self.contents|
    virtual Boolean isInInsertionMode(void) = 0;
    //! restores self
    //! ensures: isInInsertionMode = self.inserting
};
