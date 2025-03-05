/*
Implementation of wrapper for the scalar type wchar_t
Author:	Dr. Holly
*/

#include "wrapper.h"

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

std::wostream& operator << (std::wostream& s, Character& x)
{
	s << x.c;
	return s;
} // operator <<

//-------------------------------------------------------------------------

std::wistream& operator >> (std::wistream& s, Character& x)
{
	wchar_t inputLine[100];

	std::wcin.getline(inputLine, 99);
	x.c = inputLine[0];
	return s;
}  // operator >>

   //-------------------------------------------------------------------------

std::istream& operator >> (std::istream& s, Character& x)
{
	char inputLine[100], firstCharacter;

	std::cin.getline(inputLine, 99);
	firstCharacter = inputLine[0];
	mbtowc(&x.c, &firstCharacter, 1);
	return s;
}  // operator >>