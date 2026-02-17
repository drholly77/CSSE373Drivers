#pragma once

//
// Checking version of Map 
// author: Dr. Holly
//

template <class K, class V, class UncheckedMap>
class MapChecking1: public UncheckedMap
{
private:
	typedef UncheckedMap MapOfKV;
public:

//-------------------------------------------------------------------

void add (K& key, V& value)
{
	// assert that key is not defined in map m
	if (MapOfKV::hasKey (key)) {
		OutputDebugString (L"Operation: add\n");
		OutputDebugString (L"Assertion failed: !hasKey(key)\n");
		DebugBreak ();
	}	// end if 

	MapOfKV::add (key, value);
}	// add

//-------------------------------------------------------------------

void remove (K& key, K& dCopy, V& value)
{
	// assert that key is defined in map m
	if (!MapOfKV::hasKey (key)) {
		OutputDebugString (L"Operation: remove\n");
		OutputDebugString (L"Assertion failed: hasKey(key)\n");
		DebugBreak ();
	}	// end if 

	MapOfKV::remove (key, dCopy, value);
}	// remove

//-------------------------------------------------------------------

V& value (K& key)
{
	// assert that key is defined in map m
	if (!MapOfKV::hasKey (key)) {
		OutputDebugString (L"Operation: value\n");
		OutputDebugString (L"Assertion failed: hasKey(key)\n");
		DebugBreak ();
	}	// end if 

	return MapOfKV::value(key);
}	// value

//-------------------------------------------------------------------

void removeAny (K& key, V& value)
{
	// assert that |m| > 0
	if (MapOfKV::size () <= 0) {
		OutputDebugString (L"Operation: removeAny\n");
		OutputDebugString (L"Assertion failed: |m| > 0\n");
		DebugBreak ();
	}	// end if 

	MapOfKV::removeAny (key, value);
}	// removeAny
};

