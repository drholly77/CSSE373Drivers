#pragma once
/*
Equality Testing Capability for Set
Author: Dr. Holly
*/

template <class T, class SetBase>
class SetEqCapability1 :
	public SetBase
{
public:
	Boolean operator == (SetEqCapability1& rhs);
};


//------------------------------------------------------------------
// Exported Operations
//------------------------------------------------------------------


template <class T, class SetBase>
Boolean SetEqCapability1<T, SetBase>::operator == (SetEqCapability1& rhs)
{
	Boolean equal;

	if (SetBase::size() == rhs.size()) {
		SetBase tempSet;
		equal = true;
		for (int k = 0, z = rhs.size(); k < z; k++) {
			T x;
			rhs.removeAny(x);
			equal = equal && SetBase::contains(x);
			tempSet.add(x);
		} // end for
		rhs.transferFrom(tempSet);
	} // end if
	return equal;
}	// operator ==

