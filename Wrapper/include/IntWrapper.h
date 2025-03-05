#pragma once
/*
Declaration of wrapper for the scalar type int
Author: Dr. Holly
*/

class Integer: public StdOps<Integer>
{
public:
	Integer (int x = 0) { i = x; };
	Integer (const Integer &x) { i = x.i; };
	inline ~Integer () {};

	void clear (void) {	i = 0; };
	void transferFrom(Integer& source) {i = source.i; source.clear();};
	Integer& operator = (Integer& rhs) { i = rhs.i; return *this;};
	Integer& operator = (int rhs) { i = rhs; return *this;};

	void operator += (const Integer& rhs) { i += rhs.i; };
	void operator -= (const Integer& rhs) { i -= rhs.i; };
	void operator *= (const Integer& rhs) { i *= rhs.i; };
	void operator /= (const Integer& rhs) { i /= rhs.i; };
	void operator %= (const Integer& rhs) { i %= rhs.i; };

	Integer operator ++ ()    { i++; return Integer(i);};     // prefix ++x
	Integer operator ++ (int) { i++; return Integer(i-1);};   // postfix x++
	Integer operator -- ()    { i--; return Integer(i); };    // prefix --x
	Integer operator -- (int) { i--; return Integer(i+1); };  // postfix x--

	inline operator int () const { return i; };


	friend std::wostream& operator << (std::wostream& s, Integer& x);
	friend std::istream& operator >> (std::istream& s, Integer& x);
	friend std::wistream& operator >> (std::wistream& s, Integer& x);

private:
	int i;

	// don't allow ASCII character output
	__declspec(deprecated("** Use 'wcout' for type Integer **"))
		friend std::ostream& operator << (std::ostream& s, Integer& x);
}; // class Integer




