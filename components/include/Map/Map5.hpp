#pragma once
#include "Wrapper.h"
#include "Map/MapKernel.hpp"

//
// realization # 5 of Map layered on BinaryTree
// author: Dr. Holly
//

#include "BinaryTree\BinaryTree1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class K, class V, Boolean(*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
class Map5 : public StdOps<Map5<K, V, areEqual, areOrdered>>, public MapKernel<K, V>

{
public: // standard Operations
	Map5();
	Map5(const Map5& s) = delete;
	~Map5();
	void clear(void);
	void transferFrom(Map5& source);
	Map5& operator =(Map5& rhs);

	// Map5 Specific Operations
	void add(K& key, V& value);
	void remove(K& key, K& keyFromMap, V& valueFromMap);
	V& value(K& key);
	void removeAny(K& key, V& value);
	Boolean hasKey(K& key);
	Integer size(void);

	friend wostream& operator<< <K, V, areEqual, areOrdered>(wostream& os, Map5& m);
	//! updates os
	//! restores m

private: // representation
	class MapPairRecord {
	public:
		K keyItem; 
		V valueItem;

		MapPairRecord() {}
		~MapPairRecord() {}

		void clear(void)
		{
			keyItem.clear();
			valueItem.clear();
		} // clear

		MapPairRecord& operator = (MapPairRecord& rhs)
		{
			keyItem = rhs.keyItem;
			valueItem = rhs.valueItem;

			return *this;
		} // operator =

		void transferFrom(MapPairRecord& source) 
		{
			keyItem.transferFrom(source.keyItem);
			valueItem.transferFrom(source.valueItem);
		}

		friend wostream& operator <<(wostream &os, MapPairRecord& r)
		{
			os << L"(" << r.keyItem << L"," << r.valueItem << L")";
			return os;
		}
	};

	typedef BinaryTree1<MapPairRecord> BinaryTreeOfMapPair;

	BinaryTreeOfMapPair root;

private:
	void insertInTree(BinaryTreeOfMapPair& t, K& key, V& value);
	void displayRepHelp(wostream &os, BinaryTreeOfMapPair& t);
	Boolean inTree(BinaryTreeOfMapPair& t, K& key);
	void removeLargestFromTree(BinaryTreeOfMapPair& t, MapPairRecord& largest);
	void removeSmallestFromTree(BinaryTreeOfMapPair& t, MapPairRecord& smallest);
	void removeDeepestFromTree(BinaryTreeOfMapPair& t, MapPairRecord& deepest);
	void extractFromTree(BinaryTreeOfMapPair& t, K& key, MapPairRecord& extracted);
	V& treeAccessor(BinaryTreeOfMapPair& t, K& key);

};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::displayRepHelp(wostream &os, BinaryTreeOfMapPair& t)
{
	if (t.size() > 0) {
		MapPairRecord label;
		BinaryTreeOfMapPair left, right;
		Integer height = t.Height();

		t.decompose(label, left, right);
		displayRepHelp(os, left);
		os << L" H:" << right << setw(2) << height;
		os << setw(height) << L" ";
		os << label.keyItem << L",(...))" << endl;
		displayRepHelp(os, right);
		t.compose(label, left, right);
	}   // end if
} // displayRepHelp

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
Boolean Map5<K, V, areEqual, areOrdered>::inTree(BinaryTreeOfMapPair& t, K& key)
{
	Boolean found;

	if (t.size() > 0) {
		if (areEqual(key, t.label().keyItem)) {
			found = true;
		} else {
			MapPairRecord label;
			BinaryTreeOfMapPair left, right;

			t.decompose(label, left, right);
			if (areOrdered(key, label.keyItem)) {
				found = inTree(left, key);
			} else { 
				found = inTree(right, key);
			} // end if
			t.compose(label, left, right);
		} // end if
	} // end if
	return found;
} // inTree

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::insertInTree(BinaryTreeOfMapPair& t, K& key, V& value)
{
	BinaryTreeOfMapPair left, right;

	if (t.size() == 0) {
		MapPairRecord newPair;

		newPair.keyItem.transferFrom(key);
		newPair.valueItem.transferFrom(value);
		t.compose(newPair, left, right);
	} else {
		MapPairRecord label;

		t.decompose(label, left, right);
		if (areOrdered(key, label.keyItem)) {
			insertInTree(left, key, value);
		} else {
			insertInTree(right, key, value);
		}   // end if
		t.compose(label, left, right);
	}   // end if
} // insertInTree

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::removeLargestFromTree(BinaryTreeOfMapPair& t, MapPairRecord& largest)
{
	MapPairRecord label;
	BinaryTreeOfMapPair left, right;

	t.decompose(label, left, right);
	if (right.size() == 0) {
		t.transferFrom(left);
		largest.transferFrom(label);
	} else {
		removeLargestFromTree(right, largest);
		t.compose(label, left, right);
	} // end if
} // removeLargestFromTree

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::removeSmallestFromTree(BinaryTreeOfMapPair& t, MapPairRecord& smallest)
{
	MapPairRecord label;
	BinaryTreeOfMapPair left, right;

	t.decompose(label, left, right);
	if (left.size() == 0) {
		t.transferFrom(right);
		smallest.transferFrom(label);
	} else {
		removeLargestFromTree(left, smallest);
		t.compose(label, left, right);
	} // end if
} // removeLargestFromTree

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::removeDeepestFromTree(BinaryTreeOfMapPair& t, MapPairRecord& deepest)
{
} // removeDeepestFromTree

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::extractFromTree(BinaryTreeOfMapPair& t, K& key, MapPairRecord& extracted)
{
	MapPairRecord label;
	BinaryTreeOfMapPair left, right;

	t.decompose(label, left, right);
	if (areEqual(key, label.keyItem)) {
		extracted.transferFrom(label);
		if (left.size() == 0) {
			t.transferFrom(right);
		} else if (right.size() == 0) {
			t.transferFrom(left);
		} else {
			removeLargestFromTree(left, label);
			t.compose(label, left, right);
		} // end if
	} else {
		if (areOrdered(key, label.keyItem)) {
			extractFromTree(left, key, extracted);
		} else { 
			extractFromTree(right, key, extracted);
		} // end if
		t.compose(label, left, right);
	} // end if
} // extractFromTree

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
V& Map5<K, V, areEqual, areOrdered>::treeAccessor(BinaryTreeOfMapPair& t, K& key)
{
	if (areEqual(key, t.label().keyItem)) {
		return t.label().valueItem;
	} else {
		MapPairRecord label;
		BinaryTreeOfMapPair left, right;

		t.decompose(label, left, right);
		if (areOrdered(key, label.keyItem)) {
			V& valueItem = treeAccessor(left, key);
			t.compose(label, left, right);
			return valueItem;
		} else { 
			V& valueItem = treeAccessor(right, key);
			t.compose(label, left, right);
			return valueItem;
		} // end if
	} // end if
} // treeAccessor

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

// convention: the tree rooted at root is a Binary Search Tree

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
Map5<K, V, areEqual, areOrdered>::Map5()
{
}	// Map5

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
Map5<K, V, areEqual, areOrdered>::~Map5()
{
}	// ~Map5

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::transferFrom(Map5& source)
{
	root.transferFrom(source.root);
} // transferFrom

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
Map5<K, V, areEqual, areOrdered>& Map5<K, V, areEqual, areOrdered>::operator =(Map5& rhs)
{
	root = rhs.root;
	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::clear(void)
{
	root.clear();
}	// clear

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::add(K& key, V& value)
{
	insertInTree(root, key, value);
}	// add

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::remove(K& key, K& keyFromMap, V& valueFromMap)
{
	MapPairRecord r;

	extractFromTree(root, key, r);
	keyFromMap.transferFrom(r.keyItem);
	valueFromMap.transferFrom(r.valueItem);
}	// remove

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
V& Map5<K, V, areEqual, areOrdered>::value(K& key)
{
	return treeAccessor(root, key);
}  // value

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
void Map5<K, V, areEqual, areOrdered>::removeAny(K& key, V& value)
{
	MapPairRecord r;

	removeSmallestFromTree(root, r);
	key.transferFrom(r.keyItem);
	value.transferFrom(r.valueItem);
}	// removeAny

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
Boolean Map5<K, V, areEqual, areOrdered>::hasKey(K& key)
{
	return inTree(root, key);
}	// hasKey

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
Integer Map5<K, V, areEqual, areOrdered>::size(void)
{
	return root.size();
}	// size

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Boolean(*areOrdered)(K&, K&)>
wostream & operator<<(wostream &os, Map5<K, V, areEqual, areOrdered>& m)
{
	Map5<K, V, areEqual, areOrdered> temp;

	os << L"{";
	for(int i = 0, z = m.size(), lastItem = z - 1; i < z; i++) {
		K key;
		V value;

		m.removeAny(key, value);
		os << L"(" << key << L"," << value << L")";
		if (i < lastItem) {
			os << L",";
		} // end if
		temp.add(key, value);
	}	// end for
	os << L"}";
	m.transferFrom(temp);
	return os;
} // operator<<

