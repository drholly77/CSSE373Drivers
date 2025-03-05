/*
Implementation of wrapper for the scalar type long int
Author: Dr. Holly
*/

#include "wrapper.h"

std::wostream& operator << (std::wostream& s, LongInteger& x)
{
	s << x.i;
	return s;
} // operator <<

  //-------------------------------------------------------------------------

std::istream& operator >> (std::istream& s, LongInteger& x)
{
	char inputLine[100];
	long int value;

	std::cin.getline (inputLine, 99);
	sscanf (inputLine, "%ld", &value);
	x = value;
	return s;
}  // operator >>

   //-------------------------------------------------------------------------

std::wistream& operator >> (std::wistream& s, LongInteger& x)
{
	wchar_t inputLine[100];
	long int value;

	std::wcin.getline(inputLine, 99);
	swscanf(inputLine, L"%ld", &value);
	x = value;
	return s;
}  // operator >>