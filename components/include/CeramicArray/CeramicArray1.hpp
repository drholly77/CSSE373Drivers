#pragma once
#include "Wrapper.h"
#include "CeramicArray/CeramicArrayKernel.hpp"

//
// ceramicArray template
// author: Dr. Holly
//

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class CeramicArray1 : public StdOps<CeramicArray1<T>>, public CeramicArrayKernel<T>

{
public: // standard Operations
	CeramicArray1 ();
	CeramicArray1(const CeramicArray1& s) = delete;
	~CeramicArray1 ();
	void clear (void);
	void transferFrom(CeramicArray1& source);
	CeramicArray1& operator = (CeramicArray1& rhs);

	// CeramicArray1 Specific Operations
	void setBounds (Integer lower, Integer upper);
	void getBounds (Integer& lower, Integer& upper);
	T& operator [] (Integer index);

	friend wostream & operator<< <T>(wostream &os, CeramicArray1& a);
	//! updates os
	//! restores a

private: // representation
	Integer lowerBound;
	Integer upperBound;
	T* items;

private: // local Operations
	T* createNewRep(int lb, int ub);
	void reclaimRep(T* rep);
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------


template <class T>
T* CeramicArray1<T>::createNewRep(int lb, int ub)
{
	return (new T[ub - lb + 1]);
}

//-----------------------------------------------------------------------

template <class T>
void CeramicArray1<T>::reclaimRep(T* rep)
{
	delete [] rep;
}

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
CeramicArray1<T>::CeramicArray1 ()
{
	items = createNewRep(lowerBound, upperBound);
}  // CeramicArray1 ()

//-----------------------------------------------------------------------

template <class T>
CeramicArray1<T>::~CeramicArray1 ()
{
	reclaimRep(items);
}  // ~CeramicArray1 ()

//-----------------------------------------------------------------------

template <class T>
void CeramicArray1<T>::transferFrom(CeramicArray1& source)
{
	reclaimRep(items);
	items = source.items;
	lowerBound.transferFrom(source.lowerBound);
	upperBound.transferFrom(source.upperBound);
	source.items = createNewRep(source.lowerBound, source.upperBound);
} // transferFrom

//-----------------------------------------------------------------------

template <class T>
CeramicArray1<T>& CeramicArray1<T>::operator = (CeramicArray1& rhs)
{
	reclaimRep(items);
	items = createNewRep(rhs.lowerBound, rhs.upperBound);
	lowerBound = rhs.lowerBound;
	upperBound = rhs.upperBound;

	for (int index = 0, size = rhs.upperBound - rhs.lowerBound + 1; index < size; index++) {
		items[index] = rhs.items[index];
	} // end for
	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void CeramicArray1<T>::clear (void)
{
	reclaimRep(items);
	lowerBound.clear();
	upperBound.clear();
	items = createNewRep(lowerBound, upperBound);
}  // clear

//-----------------------------------------------------------------------

template <class T>
void CeramicArray1<T>::setBounds (Integer lower, Integer upper)
{
	self.lowerBound = lower;
	self.upperBound = upper;
	reclaimRep(items);
	items = createNewRep(lower, upper);
}  // setBounds

//-----------------------------------------------------------------------

template <class T>
void CeramicArray1<T>::getBounds (Integer& lower, Integer& upper)
{
	lower = self.lowerBound;
	upper = self.upperBound;
}  // getBounds

//-----------------------------------------------------------------------

template <class T>
T& CeramicArray1<T>::operator [] (Integer index)
{
	return (items[index - lowerBound]);
}  // operator []

//-----------------------------------------------------------------------

template <class T>
wostream & operator<<(wostream &os, CeramicArray1<T>& a)
{
	Integer i, lb, ub;

	a.getBounds (lb, ub);
	os << L"[";
	for (i = lb; i <= ub; i++) {
		os << a[i];
		if (i < ub) {
			os << L",";
		} // endif
	}	// end for
	os << L"]";

	return (os);
} // operator<<