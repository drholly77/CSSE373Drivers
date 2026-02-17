#pragma once

//
// StaticArray Checking Version
// author: Dr. Holly
//

template <class T, int lowerBound, int upperBound, class UncheckedStaticArray>
class StaticArrayChecking1:	public UncheckedStaticArray
{
private:
	typedef UncheckedStaticArray StaticArrayOfT;
public:
T& operator [] (Integer index)
{
	// assert that index is in bounds
	if ((index < lowerBound) || (upperBound < index)) {
		OutputDebugString (L"Operation: operator []\n");
		OutputDebugString (L"Assertion failed: (lowerBound <= index) && (index <= upperBound)\n");
		DebugBreak ();
	}	// end if 

	return StaticArrayOfT::operator [] (index);
}	// operator []

};


