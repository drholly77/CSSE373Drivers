#pragma once

/*
Declaration of wrapper for the scalar type wchar_t
Author: Dr. Holly
*/

class Character: public StdOps<Character>
{
public:
	Character (wchar_t x = 0) { c = x; };
	Character (const Character &x) { c = x.c; };
	inline ~Character () {};

	void clear (void) { c = 0; };	
	void transferFrom(Character& source) {c = source.c; source.clear();};
	Character& operator = (Character& rhs) { c = rhs.c; return *this;};
	Character& operator = (char rhs) { c = rhs; return *this;};

	Character operator ++ () { c++;	return Character(c); };          // prefix ++x
	Character operator ++ (int) { c++; return Character (c - 1); };       // postfix x++
	Character operator -- () { c--; return Character(c); };          // prefix --x
	Character operator -- (int) { c--; return Character(c+1); };       // postfix x--

	void operator += (const Character& rhs) { c += rhs.c; };
	void operator -= (const Character& rhs) { c -= rhs.c; };
	void operator *= (const Character& rhs) { c *= rhs.c; };
	void operator /= (const Character& rhs) { c -= rhs.c; };
	void operator %= (const Character& rhs) { c %= rhs.c; };

	inline operator wchar_t() const { return (c); };

	friend std::wostream& operator << (std::wostream& s, Character& x);	
	friend std::wistream& operator >> (std::wistream& s, Character& x);
	friend std::istream& operator >> (std::istream& s, Character& x);

private:
   wchar_t c;

   // don't allow ASCII character output
   __declspec(deprecated("** Use 'wcout' for type Character **"))
	   friend std::ostream& operator << (std::ostream& s, Character& x );
}; // class Character



