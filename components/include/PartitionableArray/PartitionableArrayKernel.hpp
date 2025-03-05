#pragma once

/*
	PartitionableArray kernel component with primary methods
*/

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class PartitionableArrayKernel
{
public: // PartitionableArray Specific Operations
	virtual void setBounds(Integer lower, Integer upper) = 0;
	virtual void getBounds(Integer& lower, Integer& upper) = 0;
	virtual T& operator [] (Integer index) = 0;
	virtual void giveIndexOfInterestingEntry(Integer& interestingEntryIndex) = 0;
	virtual void giveIndexOfUninterestingEntry(Integer& uninterestingEntryIndex) = 0;
	virtual Integer numberOfInterestingEntries(void) = 0;
	virtual Integer numberOfUninterestingEntries(void) = 0;
};