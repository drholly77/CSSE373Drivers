#pragma once
#include "Sequence/SequenceKernel.hpp"
#include "BinaryTree/BinaryTree0.hpp"
#include "BinaryTree/BinaryTree1.hpp"
#include "BinaryTree/BinaryTreeChecking.hpp"
#include "BinaryTree/BinaryTreeAVL.hpp"

template <class T>
class Sequence2 : public StdOps<Sequence2<T>>, public SequenceKernel<Sequence2<T>, T>
{
public: // standard Operations
	Sequence2 ();
	Sequence2(const Sequence2& s) = delete;
	~Sequence2 ();
	void clear (void);
	void transferFrom(Sequence2& source);
	Sequence2& operator = (Sequence2& rhs);

	// Sequence2 Specific Operations
	void add (Integer pos, T& x);
	void remove (Integer pos, T& x);
	void replaceEntry (Integer pos, T& x);
	T& entry (Integer pos);
	void append (Sequence2& sToAppend);
	void split (Integer pos, Sequence2& receivingS);
	Integer length (void);

	friend wostream & operator<< <T>(wostream &os, Sequence2& s);
	//! updates os
	//! restores s

private: // representation

#ifdef NDEBUG
	typedef BinaryTree1 <T> TreeOfTBase;
#else
	typedef BinaryTreeChecking1<T, BinaryTree1 <T>> TreeOfTBase;
#endif // NDEBUG

	typedef BinaryTreeAVL <T, TreeOfTBase> TreeOfT;

	TreeOfT rep;

private: // local Operations
	void insertInTree (
		 TreeOfT& t,
		 Integer pos,
		 T& x
	  );
	void extractFromTree (
			TreeOfT& t,
			Integer pos,
			T& x
		 );
	T& peekInTree (
			TreeOfT& t,
			Integer pos
		);
	void concatenateTree (
			TreeOfT& t1,
			TreeOfT& t2
		 );
	void splitTree (
			TreeOfT& t1,
			Integer pos,
			TreeOfT& t2
		 );
};


template <class T>
void Sequence2<T>::insertInTree (
         TreeOfT& t,
         Integer pos,
         T& x
      )
{
	TreeOfT left, right;
	T label;

	if (t.size () == 0) {
		t.compose (x, left, right);
	} else {
		t.decompose (label, left, right);
		if (pos <= left.size ()) {
			insertInTree (left, pos, x);
		} else {
			pos = pos - (left.size () + 1);
			insertInTree (right, pos, x);
		}  // end if
		t.composeBalanced (label, left, right);
	}   // end if
}  // insertInTree
     
//------------------------------------------------------------
     
template <class T>
void Sequence2<T>::extractFromTree (
            TreeOfT& t,
            Integer pos,
            T& x
         )
{
	TreeOfT left, right;
	T label;

	t.decompose (label, left, right);
	if (pos < left.size ()) {
		extractFromTree (left, pos, x);
		t.composeBalanced (label, left, right);
	} else if (pos > left.size ()) {
		extractFromTree (right, (pos - (left.size () + 1)), x);
		t.composeBalanced (label, left, right);
	} else {
		x.transferFrom(label);
		if (left.size () == 0) {
			t.transferFrom(right);
		} else if (right.size () == 0) {
			t.transferFrom(left);
		} else if (left.size () > right.size ()) {
			// (left.size () - 1) is largest position in left tree
			extractFromTree (left, (left.size () - 1), label);
			t.composeBalanced (label, left, right);
		} else {
			extractFromTree (right, 0, label);
			t.composeBalanced (label, left, right);
		}  // end if
	}   // end if
}  // extractFromTree
     
//-----------------------------------------------------------------------

template <class T>
T& Sequence2<T>::peekInTree (
			TreeOfT& t,
			Integer pos
		)
{
   TreeOfT left, right;
   T label;
   Integer leftSize;

   t.decompose (label, left, right);
   leftSize = left.size ();
   if (pos < leftSize) {
       T& i = peekInTree (left, pos);
	   t.compose (label, left, right);
	   return (i);
   } else if (pos > leftSize) {
       T& i = peekInTree (right, (pos - (leftSize + 1)));
	   t.compose (label, left, right);
	   return (i);
   } else {
	   t.compose (label, left, right);
	   return (t.label());
   }  // end if
}   // peekInTree

//------------------------------------------------------------
     
template <class T>
void Sequence2<T>::concatenateTree (
            TreeOfT& t1,
            TreeOfT& t2
         )
{
   TreeOfT left, right, catalyst;
   T label;

   if ((t1.size () > 0) && (t2.size () > 0)) {
      if (t1.size () > t2.size ()) {
         extractFromTree (t1, (t1.size () - 1), label);
      } else {
         extractFromTree (t2, 0, label);
      }  // end if
      catalyst.compose (label, t1, t2);
	  t1.transferFrom(catalyst);
   } else if (t2.size () > 0) {
      t1.transferFrom(t2);
   }  // end if
}  // concatenateTree

//------------------------------------------------------------

template <class T>
void Sequence2<T>::splitTree (
            TreeOfT& t1,
            Integer pos,
            TreeOfT& t2
         )
{
   if (t1.size () > 0) {
		TreeOfT left, right, catalyst;
		T label;

		t1.decompose (label, left, right);
		if (pos == left.size ()) {
			t1.transferFrom(left);
			t2.compose (label, left, right);
		} else {
			if (pos < left.size ()) {
				splitTree (left, pos, catalyst);
				t1.transferFrom(left);
				t2.compose (label, catalyst, right);
			} else {
				splitTree (right, (pos - (left.size () + 1)), catalyst);
				t2.transferFrom(catalyst);
				t1.compose (label, left, right);
			}  // end if
		} // end if
	} // end if
}  // splitTree

//------------------------------------------------------------
// exported Operations
//------------------------------------------------------------


template <class T>
Sequence2<T>::Sequence2 ()
{
}  // Sequence2

//------------------------------------------------------------
     
template <class T>
Sequence2<T>::~Sequence2 ()
{
}  // ~Sequence2 ()
     
//-----------------------------------------------------------------------

template <class T>
void Sequence2<T>::transferFrom(Sequence2& source)
{
	rep.transferFrom(source.rep);
} // transferFrom
     
//-----------------------------------------------------------------------

template <class T>
Sequence2<T>& Sequence2<T>::operator = (Sequence2& rhs)
{
	rep = rhs.rep;
	return (*this);
} // operator =

//------------------------------------------------------------
     
template <class T>
void Sequence2<T>::clear (void)
{
   rep.clear ();
}  // clear
     
//------------------------------------------------------------
     
template <class T>
void Sequence2<T>::add (Integer pos, T& x)
{
   insertInTree (rep, pos, x);
}  // add
     
//------------------------------------------------------------
     
template <class T>
void Sequence2<T>::remove (Integer pos, T& x)
{
   extractFromTree (rep, pos, x);
}  // remove
     
//------------------------------------------------------------
     
template <class T>
void Sequence2<T>::replaceEntry (Integer pos, T& x)
{
	T temp;
	T& entry = peekInTree (rep, pos);
	temp.transferFrom(entry);
	entry.transferFrom(x);
	x.transferFrom(temp);
}  // replaceEntry
     
//-----------------------------------------------------------------------

template <class T>
T& Sequence2<T>::entry (Integer pos)
{
	return (peekInTree (rep, pos));
}	// entry

//------------------------------------------------------------
     
template <class T>
void Sequence2<T>::append (Sequence2& otherS)
{
   concatenateTree (rep, otherS.rep);
}  // append
     
//------------------------------------------------------------
     
template <class T>
void Sequence2<T>::split (Integer pos, Sequence2& receivingS)
{
   splitTree (rep, pos, receivingS.rep);
}  // split

//------------------------------------------------------------

template <class T>
Integer Sequence2<T>::length (void)
{
   return (rep.size ());
}  // length

//-----------------------------------------------------------------------

template <class T>
wostream & operator<<(wostream &os, Sequence2<T>& s)
{
	os << L"<";
	for (int p = 0, z = s.length(), lastItem = z - 1; p < z; p++) {
		T x;

		os << s.entry(p);
		if (p < lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L">";

#ifndef NDEBUG
	os << endl;
	os << s.rep << endl;
#endif

	return (os);
} // operator<<

