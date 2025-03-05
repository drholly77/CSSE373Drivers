#pragma once

/*
	Checking Version of BinaryTree
	Author: Dr. Holly
*/


template <
	class T,
	class UncheckedBinaryTree
>
class BinaryTreeChecking1: public UncheckedBinaryTree
{
	typedef UncheckedBinaryTree BtOfT;
public:

//-------------------------------------------------------------------

void decompose (T& x, BinaryTree1& left, BinaryTree1& right)
{
	// assert that tree size > 0
	if (BtOfT::size () <= 0) {
		OutputDebugString (L"Operation: decompose\n");
		OutputDebugString (L"Assertion failed: |t| > 0\n");
		DebugBreak ();
	}	// end if 

	BtOfT::decompose (x, left, right);
}	// decompose

//-------------------------------------------------------------------

T& label(void)
{
	// assert that tree size > 0
	if (BtOfT::size () <= 0) {
		OutputDebugString (L"Operation: label\n");
		OutputDebugString (L"Assertion failed: |t| > 0\n");
		DebugBreak ();
	}	// end if 

	return BtOfT::label ();
}	// label
};



