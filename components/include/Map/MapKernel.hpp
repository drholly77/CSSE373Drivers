#pragma once

/*
	Map kernel component with primary methods
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class K, class V>
class MapKernel 
		//! K - type of MapKernel domain (key) entries
		//! V - type of MapKernel range (associated value) entries is modeled by PARTIAL_FUNCTION
		//! 
		//! Mathematical Subtypes:
		//! PARTIAL_FUNCTION is finite set of (key: K, value: V)
		//! 	exemplar m
		//! 	constraint
		//! 	for all key1, key2: K, value1, value2 : V
		//! 		where((key1, value1) is in m and (key2, value2) is in m)
		//! 		(if key1 = key2 then value1 = value2)
		//! 
		//! Mathematical Definitions:
		//! 	DOMAIN(m: PARTIAL_FUNCTION) : finite set of K satisfies
		//! 	for all key : K (key is in DOMAIN(m) iff
		//! 		there exists value : V((key, value) is in m))
		//! 
		//! Mathematical Model (abstract value and abstract invariant of self):
		//! type MapKernel is modeled by PARTIAL_FUNCTION
		//! exemplar self
		//! initially 
		//!    ensures: self = {}
{
public: // MapKernel Specific Operations
	virtual void add (K& key, V& value) = 0;
		//! updates self
		//! clears key, value
		//! requires: key is not in DOMAIN(self)
		//! ensures: self = #self  union  {(#key, #value)}
	virtual void remove (K& key, K& keyFromMap, V& valueFromMap) = 0;
		//! updates self
		//! restores key
		//! replaces  keyFromMap, valueFromMap
		//! requires: key is in DOMAIN(self)
		//! ensures: (key, valueFromMap) is in #self  and
		//!          self = #self \ {(keyFromMap, valueFromMap)}  and  keyFromMap = key
	virtual V& value (K& key) = 0;
		//! restores self, key
		//! requires: key is in DOMAIN(self)
		//! ensures: (key, value) is in self
	virtual void removeAny (K& key, V& value) = 0;
		//! updates self
		//! replaces key, value
		//! requires: |self| > 0
		//! ensures: (key, value) is in #self  and  self = #self \ {(key, value)}
	virtual Boolean hasKey (K& key) = 0;
		//! restores self
		//! restores key
		//! ensures: hasKey = (key is in DOMAIN(self))
	virtual Integer size (void) = 0;
		//! restores self
		//! ensures: size = |self|
};
