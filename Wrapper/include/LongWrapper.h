#pragma once
/*
Declaration of wrapper for the scalar type long
Author: Dr. Holly
*/

class LongInteger: public StdOps<LongInteger>
{
public:
	LongInteger (long x = 0) { i = x; };
	LongInteger (const LongInteger &x) { i = x.i; };
	inline ~LongInteger () {};

	void clear (void) {	i = 0; };
	void transferFrom(LongInteger& source) {i = source.i; source.clear();};
	LongInteger& operator = (LongInteger& rhs) { i = rhs.i; return *this;};
	LongInteger& operator = (bool rhs) { i = rhs; return *this;};

	void operator += (const LongInteger& rhs) { i += rhs.i; };
	void operator -= (const LongInteger& rhs) { i -= rhs.i; };
	void operator *= (const LongInteger& rhs) { i *= rhs.i; };
	void operator /= (const LongInteger& rhs) { i /= rhs.i; };
	void operator %= (const LongInteger& rhs) { i %= rhs.i; };

	LongInteger operator ++ ()    { i++; return LongInteger(i);};     // prefix ++x
	LongInteger operator ++ (int) { i++; return LongInteger(i-1);};   // postfix x++
	LongInteger operator -- ()    { i--; return LongInteger(i); };    // prefix --x
	LongInteger operator -- (int) { i--; return LongInteger(i+1); };  // postfix x--

	inline operator long int () const { return i; };

	friend std::wostream& operator << (std::wostream& s, LongInteger& x);
	friend std::istream& operator >> (std::istream& s, LongInteger& x);
	friend std::wistream& operator >> (std::wistream& s, LongInteger& x);

private:
	long int i;

	// don't allow ASCII character output
	__declspec(deprecated("** Use 'wcout' for type LongInteger **"))
		friend std::ostream& operator << (std::ostream& s, LongInteger& x);

}; // class LongInteger



