#pragma once

/*
Declaration of wrapper for float
Author: Dr. Holly
*/

class Float: public StdOps<Float>
{
public:
	Float (float x = 0.0) { f = x; };
	Float (const Float& x) { f = x.f; };
	inline ~Float () {};

	void clear (void) { f = 0.0; };
	void transferFrom(Float& source) {f = source.f; source.clear();};
	Float& operator = (Float& rhs) { f = rhs.f; return *this;};
	Float& operator = (float rhs) { f = rhs; return *this;};


	void operator += (const Float& rhs) { f += rhs.f; };
	void operator -= (const Float& rhs) { f -= rhs.f; };
	void operator *= (const Float& rhs) { f *= rhs.f; };
	void operator /= (const Float& rhs) { f /= rhs.f; };


	inline operator float () const { return f; };


	friend std::wostream& operator << (std::wostream& s, Float& x);
	friend std::istream& operator >> (std::istream& s, Float& x);
	friend std::wistream& operator >> (std::wistream& s, Float& x);

private:
	float f;

	// don't allow ASCII character output
	__declspec(deprecated("** Use 'wcout' for type Float **"))
		friend std::ostream& operator << (std::ostream& s, Float& x);
}; // class Float





