#pragma once
#include "Wrapper.h"
#include "Map/MapKernel.hpp"
#include "ChainPosition/ChainPosition.hpp"

/*
	Realization of Map layered on Chain Position using brute force search
*/

template <class K, class V, Boolean (*areEqual)(K&, K&)>
class Map1 : public StdOps<Map1<K, V, areEqual>>, public MapKernel<K, V>
{
public: // Standard Operations
	Map1 ();
	Map1(const Map1& s) = delete;
	~Map1 ();
	void clear (void);
	void transferFrom (Map1& source);
	Map1& operator = (Map1& rhs);

	// Map1 Specific Operations
	void add (K& key, V& value);
	void remove (K& key, K& keyFromMap, V& valueFromMap);
	V& value (K& key);
	void removeAny (K& key, V& value);
	Boolean hasKey (K& key);
	Integer size (void);

	friend wostream& operator<< <K, V, areEqual>(wostream& os, Map1& m);
		//! updates os
		//! restores m

private: // Representation
	class MapPairRecord {
	public:
		K keyItem; 
		V valueItem;

		MapPairRecord() {}
		MapPairRecord(K& key, V& value) 
		{
			keyItem.transferFrom(key);
			valueItem.transferFrom(value);
		} // MapPairRecord
		~MapPairRecord() {}

		void clear (void)
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

		friend wostream& operator <<(wostream& os, MapPairRecord& r)
		{
			os << L"(" << r.keyItem << L"," << r.valueItem << L")";
			return os;
		}
	};

private: // Representation
	typedef ChainPosition1 <MapPairRecord> ChainPositionOfMapPair;

	ChainPositionOfMapPair chain;
	Integer mapSize;
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

// convention: chain == smartPosition

template <class K, class V, Boolean (*areEqual)(K&, K&)>
Map1<K, V, areEqual>::Map1 ()
{
	ChainPositionOfMapPair smartPosition;
	MapPairRecord label;

	smartPosition.labelNew (label);
	chain.transferFrom(smartPosition);
}	// Map1

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
Map1<K, V, areEqual>::~Map1 ()
{
}	// ~Map1

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
void Map1<K, V, areEqual>::clear(void)
{
	ChainPositionOfMapPair smartPosition;
	MapPairRecord label;

	chain.clear();
	smartPosition.labelNew(label);
	chain.transferFrom(smartPosition);
	mapSize = 0;
}	// clear

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
void Map1<K, V, areEqual>::transferFrom(Map1& source)
{
	chain.transferFrom(source.chain);
	mapSize.transferFrom(source.mapSize);
} // transferFrom

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
Map1<K, V, areEqual>& Map1<K, V, areEqual>::operator = (Map1& rhs)
{
	ChainPositionOfMapPair newPos, oldPos, current;
	MapPairRecord x;

	current.labelNew (x);
	chain = current;

	oldPos = rhs.chain;
	oldPos.applyTarget ();
	while (!oldPos.isZero ()) {
		x = oldPos.label();
		newPos.labelNew (x);
		current.swapWithTarget (newPos);
		current.applyTarget ();
		oldPos.applyTarget ();
	} // end while
	mapSize = rhs.mapSize;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
void Map1<K, V, areEqual>::add (K& key, V& value)
{
	MapPairRecord newPair (key, value);
	ChainPositionOfMapPair newPosition;
	ChainPositionOfMapPair firstPosition;

	chain.swapWithTarget (firstPosition);

	newPosition.labelNew (newPair);
	newPosition.swapWithTarget (firstPosition);
	chain.swapWithTarget (newPosition);

	mapSize++;
}	// add

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
void Map1<K, V, areEqual>::remove (K& key, K& keyFromMap, V& valueFromMap)
{
	ChainPositionOfMapPair trailingPosition;
	ChainPositionOfMapPair currentPosition;
	MapPairRecord existingPair;

	trailingPosition = chain;
	currentPosition = trailingPosition;
	currentPosition.applyTarget ();

	while (!areEqual (key, currentPosition.label().keyItem)) {
		trailingPosition = currentPosition;
		currentPosition.applyTarget ();
	}  // end while
	currentPosition.replaceLabel (existingPair);

	currentPosition.applyTarget ();
	trailingPosition.swapWithTarget (currentPosition);

	keyFromMap.transferFrom(existingPair.keyItem);
	valueFromMap.transferFrom(existingPair.valueItem);

	mapSize--;
}	// remove

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
V& Map1<K, V, areEqual>::value (K& key)
{
	ChainPositionOfMapPair currentPosition;

	currentPosition = chain;
	currentPosition.applyTarget ();

	while (!areEqual (key, currentPosition.label().keyItem)) {
		currentPosition.applyTarget ();
	}  // end while
	return currentPosition.label().valueItem;
}  // value

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
void Map1<K, V, areEqual>::removeAny (K& key, V& value)
{
	ChainPositionOfMapPair position;
	MapPairRecord existingPair;

	position = chain;
	position.applyTarget ();

	position.replaceLabel (existingPair);
	position.applyTarget ();
	chain.swapWithTarget (position);

	key.transferFrom(existingPair.keyItem);
	value.transferFrom(existingPair.valueItem);

	mapSize--;
}	// removeAny

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
Boolean Map1<K, V, areEqual>::hasKey (K& key)
{
	ChainPositionOfMapPair position;

	position = chain;
	position.applyTarget ();

	while (!position.isZero () && !areEqual (key, position.label().keyItem)) {
		position.applyTarget ();
	}	// end while

	return !position.isZero ();
}	// hasKey

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
Integer Map1<K, V, areEqual>::size (void)
{
	return mapSize;
}	// size

//-----------------------------------------------------------------------

template <class K, class V, Boolean (*areEqual)(K&, K&)>
wostream& operator<<(wostream& os, Map1<K, V, areEqual>& m)
{
	Map1<K, V, areEqual> temp;

	os << L"{";
	for (int k = 0, z = m.size(), lastItem = z - 1; k < z; k++) {
		K key;
		V value;

		m.removeAny (key, value);
		os << L"(" << key << L"," << value << L")";
		if (k < lastItem) {
			os << L",";
		} // end if
		temp.add (key, value);
	}	// end for
	os << L"}";
	m.transferFrom(temp);

	return os;
} // operator<<
