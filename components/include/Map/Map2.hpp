#pragma once

#include "Wrapper.h"
#include "Map/MapKernel.hpp"
//
// Realization #2 of PartialMapTemplate layered on Array of Sequences
// using a hashing implementation
// author: Dr. Holly
//

#include "Sequence\Sequence1.hpp"
#include "StaticArray\StaticArray1.hpp"

//-----------------------------------------------------------------------
// template Class Specification
//-----------------------------------------------------------------------

template <class K, class V, Boolean(*areEqual)(K&, K&), Integer(*hashCode)(K&)>
class Map2 : public StdOps<Map2<K, V, areEqual, hashCode>>, public MapKernel<K, V>
{
public: // standard Operations
	Map2 ();
	Map2(const Map2& s) = delete;
	~Map2 ();
	void clear (void);
	void transferFrom(Map2& source);
	Map2& operator = (Map2& rhs);

	// Map2 Specific Operations
	void add (K& key, V& value);
	void remove (K& key, K& keyFromMap, V& valueFromMap);
	V& value (K& key);
	void removeAny (K& key, V& value);
	Boolean hasKey (K& key);
	Integer size(void);

	friend wostream& operator<< <K, V, areEqual, hashCode>(wostream& os, Map2& m);
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

	typedef Sequence1 <MapPairRecord> SequenceOfMapPair;

	enum {lowerBound = 0, upperBound = 6, arraySize = 7};
	typedef StaticArray1 <SequenceOfMapPair, lowerBound, upperBound> ArrayOfSequences;

	ArrayOfSequences map;
	Integer mapSize;
};

//-----------------------------------------------------------------------
// member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// exported Operations
//-----------------------------------------------------------------------

// convention: 

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
Map2<K, V, areEqual, hashCode>::Map2 ()
{
}	// Map2

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
Map2<K, V, areEqual, hashCode>::~Map2 ()
{
}	// ~Map2

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
void Map2<K, V, areEqual, hashCode>::transferFrom(Map2& source)
{
	map.transferFrom(source.map);
	mapSize.transferFrom(source.mapSize);
} // transferFrom

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
Map2<K, V, areEqual, hashCode>& Map2<K, V, areEqual, hashCode>::operator = (Map2& rhs)
{
	map = rhs.map;
	mapSize = rhs.mapSize;

	return (*this);
} // operator =

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
void Map2<K, V, areEqual, hashCode>::clear (void)
{
	map.clear();
	mapSize = 0;
}	// clear

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
void Map2<K, V, areEqual, hashCode>::add (
			K& key,
			V& value
		)
{
	MapPairRecord newPair;
	Integer index = hashCode(key) % arraySize;

	newPair.keyItem.transferFrom(key);
	newPair.valueItem.transferFrom(value);

	map[index].add(0, newPair);
	mapSize++;
}	// add

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
void Map2<K, V, areEqual, hashCode>::remove (
			K& key,
			K& keyFromMap,
			V& valueFromMap
		)
{
	MapPairRecord existingPair;
	Integer index = hashCode(key) % arraySize;
	Integer position;

	while(!areEqual(map[index].entry(position).keyItem, key)) {
		position++;
	} // end while
	map[index].remove(position, existingPair);
	keyFromMap.transferFrom(existingPair.keyItem);
	valueFromMap.transferFrom(existingPair.valueItem);
	mapSize--;
}	// remove

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
V& Map2<K, V, areEqual, hashCode>::value (K& key)
{
	Integer index = hashCode(key) % arraySize;
	Integer position;

	while(!areEqual(map[index].entry(position).keyItem, key)) {
		position++;
	} // end while

	return(map[index].entry(position).valueItem);
}  // value

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
void Map2<K, V, areEqual, hashCode>::removeAny (
			K& key,
			V& value
		)
{
	MapPairRecord existingPair;
	Integer index;

	while(map[index].length() == 0) {
		index++;
	} // end while
	map[index].remove(0, existingPair);
	key.transferFrom(existingPair.keyItem);
	value.transferFrom(existingPair.valueItem);
	mapSize--;
}	// removeAny

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
Boolean Map2<K, V, areEqual, hashCode>::hasKey (
			K& key
		)
{
	Integer index = hashCode(key) % arraySize;
	Integer z = map[index].length();
	Integer position;
	Boolean found;

	while((position < z) && !areEqual(map[index].entry(position).keyItem, key)) {
		position++;
	} // end while

	found = (position < z);
	return found;
}	// hasKey

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
Integer Map2<K, V, areEqual, hashCode>::size (void)
{
	return mapSize;
}	// size

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&), Integer(*hashCode)(K&)>
wostream & operator<<(wostream &os,Map2<K, V, areEqual, hashCode>& m)
{
	Map2<K, V, areEqual, hashCode> temp;

	os << L"{";
	for (int i = 0, z = m.size(), lastItem = z - 1; i < z; i++) {
		K key;
		V value;

		m.removeAny (key, value);
		os << L"(" << key << L"," << value << L")";
		if (i < lastItem) {
			os << L",";
		} // end if
		temp.add (key, value);
	}	// end for
	os << L"}";
	m.transferFrom(temp);

#ifndef NDEBUG
	os << endl;
	os << L"(" << m.map << L"," << m.mapSize << L")";
#endif

	return (os);
} // operator<<
