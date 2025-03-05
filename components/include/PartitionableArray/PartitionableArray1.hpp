#pragma once

#include "PartitionableArray/PartitionableArrayKernel.hpp"
#include "CyclePosition/CyclePosition.hpp"
#include "CeramicArray/CeramicArray1.hpp"

//
// Realization of PartitionableArray layered on Ceramic Array and Cycle Position
// author: Dr. Holly
//

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
class PartitionableArray1 : public StdOps<PartitionableArray1<T, isInteresting>>, 
	public PartitionableArrayKernel<T>
{
public: // Standard Operations
	PartitionableArray1 ();
	PartitionableArray1(const PartitionableArray1& s) = delete;
	~PartitionableArray1 ();
	void clear (void);
	void transferFrom(PartitionableArray1& source);
	PartitionableArray1& operator = (PartitionableArray1& rhs);

	// PartitionableArray1 Specific Operations
	void setBounds (Integer lower, Integer upper);
	void getBounds (Integer& lower, Integer& upper);
	T& operator [] (Integer index);
	void giveIndexOfInterestingEntry(Integer& interestingEntryIndex);
	void giveIndexOfUninterestingEntry(Integer& uninterestingEntryIndex);
	Integer numberOfInterestingEntries(void);
	Integer numberOfUninterestingEntries(void);

	// for debugging
	//void traverseCycles(void);


	friend wostream& operator<< <T, isInteresting>(wostream& os, PartitionableArray1& a);
		//! updates os
		//! restores a

private: // Representation
	// build Cycle Position
	typedef CyclePosition1 <Integer> IntCyclePos;

	// build Array of PartitionRecord
	class PartitionRec {
	public:
		T x;
		IntCyclePos p;
	};
	typedef CeramicArray1 <PartitionRec> PartitionRecordArray;

	// build Partitionable Array Rep
	Integer countOfInteresting;
	Boolean partitionMightNeedUpdating;
	Boolean updateLocInterestingStatus;
	Integer updateLoc;
	IntCyclePos rootInterestingCycle;
	IntCyclePos rootUninterestingCycle;
	PartitionRecordArray array;

private: // Local Operations
	void makeInteresting(IntCyclePos& p, Integer index);
	void makeUninteresting(IntCyclePos& p, Integer index);
	void doUpdateIfNecessary(void);
	void updatePartition(PartitionRec& r, Integer index, Boolean updateLocInterestingStatus);
	void updateCyclesOnIntializedArray (void);
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
// Local Operations
//-----------------------------------------------------------------------
/*
template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::traverseCycles(void)
{
	IntegerCyclePosition p;

	wcout << "Indices of interesting: ";
	p = rootInterestingCycle;
	p.applyTarget();
	while (p != rootInterestingCycle) {
		wcout << p.label() << " ";
		p.applyTarget();
	}
	wcout << endl;

	wcout << "Indices of uninteresting: ";
	p = rootUninterestingCycle;
	p.applyTarget();
	while (p != rootUninterestingCycle) {
		wcout << p.label() << " ";
		p.applyTarget();
	}
	wcout << endl;

} // traverseCycles
*/
//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::makeInteresting(IntCyclePos& p, Integer index)
{
	IntCyclePos q;
	//wcout << "*** makeInteresting at index: " << index << endl;

	// remove p from uninteresting cycle
	q = p;
	q.applyInverseTarget();
	q.transposeAfter(p);

	// add p to interesting cycle
	p.replaceLabel(index);
	rootInterestingCycle.transposeAfter(p);
	countOfInteresting++;
}

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::makeUninteresting(IntCyclePos& p, Integer index)
{
	IntCyclePos q;
	//wcout << "*** makeUninteresting at index: " << index << endl;

	// remove p from interesting cycle
	q = p;
	q.applyInverseTarget();
	q.transposeAfter(p);
	countOfInteresting--;

	// add p to uninteresting cycle
	p.replaceLabel(index);
	rootUninterestingCycle.transposeAfter(p);
}
//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::updatePartition(PartitionRec& r, Integer index, Boolean wasInteresting)
{
	Boolean isNowInteresting = isInteresting(r.x);

	if (wasInteresting && !isNowInteresting) { 
		makeUninteresting(r.p, index);
	}	// end if
	if (!wasInteresting && isNowInteresting) { 
		makeInteresting(r.p, index);
	}	// end if

	// Note: Do nothing for no change in the 'interesting' status
	// 1) wasInteresting && isNowInteresting
	// 2) !wasInteresting && !isNowInteresting
}	// updatePartition

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::doUpdateIfNecessary(void) {
	if (partitionMightNeedUpdating) {
		updatePartition(array[updateLoc], updateLoc, updateLocInterestingStatus);
		partitionMightNeedUpdating = false;
	}	// end if
}

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::updateCyclesOnIntializedArray (void)
// post: updates interesting and uninteresting cycles for an initialized array
{
	Integer lowerBound, upperBound;
	array.getBounds(lowerBound, upperBound);
	Boolean isNowInteresting = isInteresting((array[lowerBound]).x);

	if (isNowInteresting) {
		// array full of interesting entries
		for (int k = lowerBound; k <= upperBound; k++) {
			Integer label = k;
			(array[k]).p.replaceLabel(label);
			rootInterestingCycle.transposeAfter((array[k]).p);
			countOfInteresting++;
		}	// end for
	}
	else {
		// array full of uninteresting entries
		for (int k = lowerBound; k <= upperBound; k++) {
			Integer label = k;
			(array[k]).p.replaceLabel(label);
			rootUninterestingCycle.transposeAfter((array[k]).p);
		}	// end for
	}// end if
}	// updateCyclesOnIntializedArray ()

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
PartitionableArray1<T, isInteresting>::PartitionableArray1 ()
{
	updateCyclesOnIntializedArray();
}	// PartitionableArray1 ()

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
PartitionableArray1<T, isInteresting>::~PartitionableArray1 ()
{
}	// ~PartitionableArray1 ()

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::clear(void)
{
	countOfInteresting.clear();
	partitionMightNeedUpdating.clear();
	updateLocInterestingStatus.clear();
	updateLoc.clear();
	rootInterestingCycle.clear();
	rootUninterestingCycle.clear();
	array.clear();
	updateCyclesOnIntializedArray();
}	// clear

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::transferFrom(PartitionableArray1& source)
{
	countOfInteresting.transferFrom(source.countOfInteresting);
	partitionMightNeedUpdating.transferFrom(source.partitionMightNeedUpdating);
	updateLocInterestingStatus.transferFrom(source.updateLocInterestingStatus);
	updateLoc.transferFrom(source.updateLoc);
	rootInterestingCycle.transferFrom(source.rootInterestingCycle);
	rootUninterestingCycle.transferFrom(source.rootUninterestingCycle);
	array.transferFrom(source.array);
	source.updateCyclesOnIntializedArray();
} // transferFrom

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
PartitionableArray1<T, isInteresting>& PartitionableArray1<T, isInteresting>::operator = (PartitionableArray1& rhs)
{
	Integer lower, upper;

	rhs.array.getBounds(lower, upper);
	array.setBounds(lower, upper);
	countOfInteresting.clear();
	partitionMightNeedUpdating.clear();
	updateLocInterestingStatus.clear();
	rootInterestingCycle.clear();
	rootUninterestingCycle.clear();
	updateCyclesOnIntializedArray();
	// array was just reset to initial value
	// determine if entry's initial value is interesting or not
	updateLocInterestingStatus = isInteresting((array[lower]).x);

	for (int index = lower; index <= upper; index++) {
		array[index].x = rhs.array[index].x;
		updatePartition(array[index], index, updateLocInterestingStatus);
	} // end for
	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::setBounds (
         Integer lower,
         Integer upper
      )
{
	array.setBounds(lower, upper);
	countOfInteresting.clear();
	partitionMightNeedUpdating.clear();
	updateLocInterestingStatus.clear();
	rootInterestingCycle.clear();
	rootUninterestingCycle.clear();
	updateCyclesOnIntializedArray();
}  // setBounds

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::getBounds (Integer& lower, Integer& upper)
{
	array.getBounds(lower, upper);
}	// getBounds

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
T& PartitionableArray1<T, isInteresting>::operator [] (Integer index)
{
	doUpdateIfNecessary();
	partitionMightNeedUpdating = true;
	updateLoc = index;
	updateLocInterestingStatus = isInteresting((array[updateLoc]).x);
	return array[index].x;
}	// operator []

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::giveIndexOfInterestingEntry(Integer& interestingEntryIndex)
{
	IntCyclePos q;

	doUpdateIfNecessary();
	q = rootInterestingCycle;
	q.applyTarget();
	interestingEntryIndex = q.label();
}

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
void PartitionableArray1<T, isInteresting>::giveIndexOfUninterestingEntry(Integer& uninterestingEntryIndex)
{
	IntCyclePos q;

	doUpdateIfNecessary();
	q = rootUninterestingCycle;
	q.applyTarget();
	uninterestingEntryIndex = q.label();
}

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
Integer PartitionableArray1<T, isInteresting>::numberOfInterestingEntries(void)
{
	doUpdateIfNecessary();
	return countOfInteresting;
}

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
Integer PartitionableArray1<T, isInteresting>::numberOfUninterestingEntries(void)
{
	Integer lower, upper;

	doUpdateIfNecessary();
	array.getBounds(lower, upper);
	return (upper - lower + 1) - countOfInteresting;
}

//-----------------------------------------------------------------------

template <class T, Boolean(*isInteresting)(T&)>
wostream& operator<<(wostream& os, PartitionableArray1<T, isInteresting>& a)
{
	Integer lb, ub;

	a.getBounds (lb, ub);
	os << L"[";
	for (int k = lb; k <= ub; k++) {
		os << a[k];
		if (k < ub) {
			os << L",";
		} // endif
	}	// end for
	os << L"]";

	return os;
} // operator<<