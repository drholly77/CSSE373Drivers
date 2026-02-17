#pragma once

//
// ceramicArray Checking Version
// author: Dr. Holly
//

template <class T, class UncheckedCeramicArray>
class CeramicArrayChecking1: public UncheckedCeramicArray
{
private:
	typedef UncheckedCeramicArray CeramicArrayOfT;
public:

//-----------------------------------------------------------------------

T& operator [] (Integer index)
{
	Integer lowerBound;
	Integer upperBound;

	CeramicArrayOfT::getBounds (lowerBound, upperBound);
	// assert that index is in bounds
	if ((index < lowerBound) || (upperBound < index)) {
		OutputDebugString (L"Operation: operator []\n");
		OutputDebugString (L"Assertion failed: (lowerBound <= index) && (index <= upperBound)\n");
		DebugBreak ();
	}	// end if 
	
	return (CeramicArrayOfT::operator [] (index));
}	// operator []

//-----------------------------------------------------------------------

void setBounds (
	Integer lower,
	Integer upper
)
{
	if (lower > upper) {
		OutputDebugString (L"Operation: operator []\n");
		OutputDebugString (L"Assertion failed: (lower <= upper)\n");
		DebugBreak ();
	}	// end if 
	
	CeramicArrayOfT::setBounds (lower, upper);
}	// setBounds

};

