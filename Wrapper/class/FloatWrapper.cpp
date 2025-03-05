/*
Implementation of wrapper for float
Author: Dr. Holly
*/

#include "wrapper.h"


std::wostream& operator << (std::wostream& s, Float& x)
{
	s << x.f;
	return s;
} // operator <<

  //-------------------------------------------------------------------------

std::istream& operator >> (std::istream& s, Float& x)
{
	char inputLine[100];
	float value;

	std::cin.getline (inputLine, 99);
	sscanf (inputLine, "%f", &value);
	x = value;
	return s;
}  // operator >>

   //-------------------------------------------------------------------------

std::wistream& operator >> (std::wistream& s, Float& x)
{
	wchar_t inputLine[100];
	float value;

	std::wcin.getline(inputLine, 99);
	swscanf(inputLine, L"%f", &value);
	x = value;
	return s;
}  // operator >>