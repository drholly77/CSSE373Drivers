#pragma once
#include "BinaryTree/BinaryTreeKernel.hpp"

/*
	Realization of BinaryTree using 2WayDagPosition
	Author: Dr. Holly
*/

#include "DAGPosition/DAGPosition1.hpp"

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T>
class BinaryTree1 : public StdOps<BinaryTree1<T>>, public BinaryTreeKernel<BinaryTree1<T>, T>
{
public: // Standard Operations
	BinaryTree1 ();
	BinaryTree1(const BinaryTree1& s) = delete;
	~BinaryTree1 ();
	void clear (void);
	void transferFrom (BinaryTree1& source);
	BinaryTree1& operator = (BinaryTree1& rhs);

	// BinaryTree1 Specific Operations
	void compose (T& x, BinaryTree1& left, BinaryTree1& right);
	void decompose (T& x, BinaryTree1& left, BinaryTree1& right);
	T& label (void);
	Integer size (void);
	Integer height (void);

	friend wostream& operator<< <T>(wostream& os, BinaryTree1& x);
		//! updates os
		//! restores x

private: // Representation
	enum {leftSubtree = 0, rightSubtree = 1};

	// Create BinaryTree's label
	class TreeLabelRecord {
	public:
		T item;
		Integer size;
		Integer height;

		TreeLabelRecord() {}
		~TreeLabelRecord() {}

		void clear(void) {
			item.clear();
			size.clear();
			height.clear();
		} // clear
		void transferFrom(TreeLabelRecord& source) {
			item.transferFrom(source.item);
			size.transferFrom(source.size);
			height.transferFrom(source.height);
		} // transferFrom

		TreeLabelRecord& operator = (TreeLabelRecord& rhs) {
			item = rhs.item;
			size = rhs.size;
			height = rhs.height;
			return *this;
		} // operator =

		friend wostream& operator<< (wostream& os, TreeLabelRecord& r) {
			os << "(" << r.item << "," << r.size << "," << r.height << ")";
			return os;
		} // operator <<
	};

	typedef DagPosition1 <TreeLabelRecord, 2> TwoWayDagPosition;
	TwoWayDagPosition node;

private: // Local Operations
	inline Integer treeSize (void);
	inline Integer treeHeight (void);
	void copy (TwoWayDagPosition& from, TwoWayDagPosition& to);
	void displayRepInOrder (wostream& os, TwoWayDagPosition& root);
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Local Operations
//-----------------------------------------------------------------------

template <class T>
inline Integer BinaryTree1<T>::treeSize (void)
{
	return node.label().size;
}   // treeSize

//-----------------------------------------------------------------------

template <class T>
inline Integer BinaryTree1<T>::treeHeight (void)
{
   return node.label().height;
}   // treeHeight

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::copy (
		TwoWayDagPosition& from,
		TwoWayDagPosition& to
	)
	// pre: to.label() = (T.init, 0, 0)
{
	if (!from.isZero()) {
		TreeLabelRecord label;
		TwoWayDagPosition left, right, leftCopy, rightCopy;

		from.swapWithTarget(leftSubtree, left);
		from.swapWithTarget(rightSubtree, right);
		copy(left, leftCopy);
		copy(right, rightCopy);
		from.swapWithTarget(leftSubtree, left);
		from.swapWithTarget(rightSubtree, right);

		label = from.label();
		to.labelNew(label);
		to.swapWithTarget(leftSubtree, leftCopy);
		to.swapWithTarget(rightSubtree, rightCopy);
	} // end if
} // copy

//------------------------------------------------------------

template <class T>
void BinaryTree1<T>::displayRepInOrder (wostream& os, TwoWayDagPosition& root)
{
	if (!root.isZero()) {
		Integer height = root.label().height;
		TwoWayDagPosition left = root;
		left.applyTarget(leftSubtree);
		displayRepInOrder(os, left);
		os << L" H:" << right << setw(2) << height;
		os << setw(height) << L" ";
		os << root.label() << endl;
		TwoWayDagPosition right = root;
		right.applyTarget(rightSubtree);
		displayRepInOrder(os, right);
	} // end if
}	// displayRepInOrder

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

template <class T>
BinaryTree1<T>::BinaryTree1 ()
{
}   // BinaryTree1

//-----------------------------------------------------------------------

template <class T>
BinaryTree1<T>::~BinaryTree1 ()
{
}   // ~BinaryTree1

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::transferFrom(BinaryTree1& source)
{
	node.transferFrom(source.node);
}   // transferFrom

//-----------------------------------------------------------------------

template <class T>
BinaryTree1<T>& BinaryTree1<T>::operator = (BinaryTree1& rhs)
{
	node.clear();
	copy(rhs.node, node);
	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::clear (void)
{
   node.clear();
}   // clear

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::compose (T& x, BinaryTree1& left, BinaryTree1& right)
{
   TreeLabelRecord label;
   Integer leftHeight, rightHeight;

   label.item.transferFrom(x);
   leftHeight = left.treeHeight();
   rightHeight = right.treeHeight();
   label.height =
      ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
   label.size = left.treeSize() + right.treeSize() + 1;
   node.labelNew(label);

   node.swapWithTarget(leftSubtree, left.node);
   node.swapWithTarget(rightSubtree, right.node);
}   // compose

//-----------------------------------------------------------------------

template <class T>
void BinaryTree1<T>::decompose (T& x, BinaryTree1& left, BinaryTree1& right)
{
   TreeLabelRecord label;

   node.replaceLabel(label);
   x.transferFrom(label.item);
   node.swapWithTarget(leftSubtree, left.node);
   node.swapWithTarget(rightSubtree, right.node);
   node.clear();
}   // decompose

//-----------------------------------------------------------------------

template <class T>
T& BinaryTree1<T>::label (void)
{
   return node.label().item;
}  // label

//-----------------------------------------------------------------------

template <class T>
Integer BinaryTree1<T>::size (void)
{
   return self.treeSize();
}   // size

//-----------------------------------------------------------------------

template <class T>
Integer BinaryTree1<T>::height (void)
{
   return self.treeHeight();
}   // height

//-----------------------------------------------------------------------

template <class T>
wostream& operator<<(wostream& os, BinaryTree1<T>& root)
{
#ifdef NDEBUG
	root.displayRepInOrder(os, root.node);
#else
	os << root.node << endl;
#endif
	return os;
} // operator<<
