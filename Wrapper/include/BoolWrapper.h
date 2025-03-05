#pragma once

/*
Declaration of scalar type Boolean
Author: Dr. Holly
*/

class Boolean: public StdOps<Boolean>
{
public:
	Boolean (const Boolean &x) {b = x.b;};
	Boolean (bool x = false) {b = x ? true : false;};
	Boolean (int x) {b = x ? true : false;};
	inline ~Boolean () {};
	void clear (void) {	b = false; };
	void transferFrom(Boolean& source) {b = source.b; source.clear();};
	Boolean& operator = (Boolean& rhs) { b = rhs.b; return *this;};
	Boolean& operator = (bool rhs) { b = rhs; return *this;};

	operator bool() const {return (b);};

	friend std::wostream& operator << (std::wostream& s, Boolean& x);
	friend std::istream& operator >> (std::istream& s, Boolean& x);
	friend std::wistream& operator >> (std::wistream& s, Boolean& x);

private:
   bool b;

   // don't allow ASCII character output
   __declspec(deprecated("** Use 'wcout' for type Boolean **"))
	   friend std::ostream& operator << (std::ostream& s, Boolean& x);
};





