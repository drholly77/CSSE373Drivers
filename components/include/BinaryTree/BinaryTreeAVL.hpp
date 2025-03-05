#pragma once
/*
	BinaryTree - Layred rotation operations
	Author: Dr. Holly
*/

template <class T, class BinaryTreeOfT>
class BinaryTreeAVL:
	public BinaryTreeOfT
{
public:

	void composeBalanced (
			T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		);

private:
   void balanceRight (
			T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		);
   void balanceLeft (
			T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		);
   void rotateRight (
			T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		);
   void rotateLeft (
			T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		);
};


//-----------------------------------------------------------------------
// local Operations
//-----------------------------------------------------------------------

template <class T, class BinaryTreeOfT>
void BinaryTreeAVL<T, BinaryTreeOfT>::rotateRight (
			T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		)
{
   T leftsLabel;
   BinaryTreeAVL leftsLeft;
   BinaryTreeAVL leftsRight;
   BinaryTreeAVL newRight;

   left.decompose (leftsLabel, leftsLeft, leftsRight);
   left.transferFrom(leftsLeft);
   newRight.compose (label, leftsRight, right);
   label.transferFrom(leftsLabel);
   right.transferFrom(newRight);
}  // rotateRight

//-----------------------------------------------------------------------

template <class T, class BinaryTreeOfT>
void BinaryTreeAVL<T, BinaryTreeOfT>::rotateLeft (
			T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		)
{
   T rightsLabel;
   BinaryTreeAVL rightsLeft;
   BinaryTreeAVL rightsRight;
   BinaryTreeAVL newLeft;

   right.decompose (rightsLabel, rightsLeft, rightsRight);
   right.transferFrom(rightsRight);
   newLeft.compose (label, left, rightsLeft);
   label.transferFrom(rightsLabel);
   left.transferFrom(newLeft);
}  // rotateLeft

//-----------------------------------------------------------------------

template <class T, class BinaryTreeOfT>
void BinaryTreeAVL<T, BinaryTreeOfT>::balanceRight (
			T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		)
{
	T rightsLabel;
	BinaryTreeAVL rightsLeft;
	BinaryTreeAVL rightsRight;
	BinaryTreeAVL newLeft;

   right.decompose (rightsLabel, rightsLeft, rightsRight);
   if (rightsLeft.height () > rightsRight.height ()) {
      rotateRight (rightsLabel, rightsLeft, rightsRight);
   }  // end if
   newLeft.compose (label, left, rightsLeft);
   self.compose (rightsLabel, newLeft, rightsRight);
}	// balanceRight

//-----------------------------------------------------------------------

template <class T, class BinaryTreeOfT>
void BinaryTreeAVL<T, BinaryTreeOfT>::balanceLeft (
			T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		)
{
	T leftsLabel;
	BinaryTreeAVL leftsLeft;
	BinaryTreeAVL leftsRight;
	BinaryTreeAVL newRight;

   left.decompose (leftsLabel, leftsLeft, leftsRight);
   if (leftsRight.height () > leftsLeft.height ()) {
      rotateLeft (leftsLabel, leftsLeft, leftsRight);
   }  // end if
   newRight.compose (label, leftsRight, right);
   self.compose (leftsLabel, leftsLeft, newRight);
}	// balanceLeft

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T, class BinaryTreeOfT>
void BinaryTreeAVL<T, BinaryTreeOfT>::composeBalanced (
         T& label,
			BinaryTreeAVL& left,
			BinaryTreeAVL& right
		)
{
	enum {
		leftHigherBy2 = -2,
		leftHigherBy1 = -1,
		balanced          = 0,
		rightHigherBy1 = 1,
		rightHigherBy2 = 2
	};
	Integer heightDifference;

	heightDifference = right.height () - left.height ();
	switch (heightDifference) {
		case rightHigherBy2:
			self.balanceRight (label, left, right);
			break;
		case leftHigherBy2:
			self.balanceLeft (label, left, right);
			break;
		default: // leftHigherBy1, balanced, rightHigherBy1
			self.compose (label, left, right);
			break;
	}  // end switch
}  // composeBalanced




