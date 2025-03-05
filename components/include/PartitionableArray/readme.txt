PArr1 - Partitionable_Array encapsulates raw C++ dynamically defined
         arrays.  Partitionable_Array exports constructor, destructor,
         swap operator and Clear operations.  Partitionable_Array 
         types can be seamlessly combined with other software
         components.

	A Partitionable_Array requires a 2nd template parameter which
	is a class that statically exports a Boolean function named:
	Is_Partitionable.  Is_Partitionable must be parameterized by the
	type Item stored in the array.  Is_Partitionable returns true
	when it is called with an Item that meets some property for
	that type Item.  For example, if Item = Integer, then 
	Is_Partitionable might return true for even Integers, or return
	true for odd Integers, or prime Integers, etc.

	Partitionable_Array exports two other operations that are used
	with the "partition" feature of this array: P_Holds_Somewhere
	and Index_Where_P_Holds.  P_Holds_Somewhere if there is an
	Item in the array where Is_Partitionable would return true.
	Index_Where_P_Holds returns the index in the array where
	there exists an Item such that Is_Partitionable is true for 
	that Item.

