#pragma once
#include "BinaryTree/BinaryTreeKernel.hpp"

/*
	Realization of BinaryTree using raw nodes & pointers
	Author: Dr. Holly
*/

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class T>
class BinaryTree0 : public StdOps<BinaryTree0<T>>, public BinaryTreeKernel<BinaryTree0<T>, T>
{
public: // standard Operations
	BinaryTree0 ();
	BinaryTree0(const BinaryTree0& s) = delete;
	~BinaryTree0 ();
	void clear (void);
	void transferFrom(BinaryTree0& source);
	BinaryTree0& operator = (BinaryTree0& rhs);

	// BinaryTree0 Specific Operations
	void compose (T& x, BinaryTree0& left, BinaryTree0& right);            
	void decompose (T& x, BinaryTree0& left, BinaryTree0& right);
	T& label(void);
	Integer size(void);
	Integer height(void);

private: // representation

	class NodeClass {
	public:
		T value;
		NodeClass* left;
		NodeClass* right;
		Integer size;
		Integer height;
	};

	NodeClass* root;

private: // local Operations
	void deleteNodes (NodeClass*& p);
	inline Integer treeSize (void);
	inline Integer treeHeight (void);
	void copy (NodeClass*& from, NodeClass*& to);
};


//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

// module Level Invariant
// when the tree is empty root = NULL

//-----------------------------------------------------------------------
// local Operations
//-----------------------------------------------------------------------

template <class T>
inline Integer BinaryTree0<T>::treeSize (void)
{
	if (root == NULL) {
		return 0;
	} else {
        return root->size;
	} // end if
}   // treeSize

//-----------------------------------------------------------------------

template <class T>
inline Integer BinaryTree0<T>::treeHeight (void)
{
	if (root == NULL) {
		return 0;
	} else {
        return root->height;
	} // end if
}   // treeHeight

//-----------------------------------------------------------------------

template <class T>
void BinaryTree0<T>::copy (NodeClass*& from, NodeClass*& to)
{
	if (from != NULL) {
		to = new NodeClass;

		to->value = from->value;
		copy(from->left, to->left);
		copy(from->right, to->right);
		to->size = from->size;
		to->height = from->height;
	} else {
		to = NULL;
	} // end if
} // copy

//-----------------------------------------------------------------------

template <class T>
void BinaryTree0<T>::deleteNodes (NodeClass*& p)
{
	if (p != NULL) {
		deleteNodes(p->left);
		deleteNodes(p->right);
		delete p;
	} // end if
}   // deleteNodes

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

template <class T>
BinaryTree0<T>::BinaryTree0 ()
{
	root = NULL;
}   // BinaryTree0

//-----------------------------------------------------------------------

template <class T>
BinaryTree0<T>::~BinaryTree0 ()
{
	deleteNodes(root);
}   // ~BinaryTree0

//-----------------------------------------------------------------------

template <class T>
void BinaryTree0<T>::transferFrom(BinaryTree0& source)
{
	deleteNodes(root);
	root = source.root;
	source.root = NULL;
}   // transferFrom

//-----------------------------------------------------------------------

template <class T>
BinaryTree0<T>& BinaryTree0<T>::operator = (BinaryTree0& rhs)
{
	deleteNodes(root);
	copy(rhs.root, root);
	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void BinaryTree0<T>::clear (void)
{
	deleteNodes(root);
	root = NULL;
}   // clear

//-----------------------------------------------------------------------

template <class T>
void BinaryTree0<T>::compose(T& x, BinaryTree0& left, BinaryTree0& right)
{
	deleteNodes(root);
	root = new NodeClass;
	root->value.transferFrom(x);
	root->left = left.root;
	root->right = right.root;
	root->size = left.treeSize() + right.treeSize() + 1;
	root->height = max (left.treeHeight(), right.treeHeight()) + 1;

	left.root = NULL;
	right.root = NULL;
}   // compose

//-----------------------------------------------------------------------

template <class T>
void BinaryTree0<T>::decompose(T& x, BinaryTree0& left, BinaryTree0& right)
{
	deleteNodes(left.root);
	deleteNodes(right.root);
	left.root = root->left;
	right.root = root->right;
	x.transferFrom(root->value);
	delete root;
	root = NULL;
}   // decompose

//-----------------------------------------------------------------------

template <class T>
T& BinaryTree0<T>::label(void)
{
	return root->value;
}  // label

//-----------------------------------------------------------------------

template <class T>
Integer BinaryTree0<T>::size (void)
{
    return treeSize();
}   // size

//-----------------------------------------------------------------------

template <class T>
Integer BinaryTree0<T>::height (void)
{
	return treeHeight();
}   // height
