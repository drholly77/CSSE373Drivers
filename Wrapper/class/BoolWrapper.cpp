/*
Implementation of scalar type Boolean
Author: Dr. Holly
*/

#include "wrapper.h"

std::wostream& operator << (std::wostream& s, Boolean& x)
{
	if (x) {
		s << L"true";
	} else {
		s << L"false";
	}	// end if
   return s;
}  // operator <<

//-------------------------------------------------------------------------

std::istream& operator >> (std::istream& s, Boolean& x)
{
	char inputLine[100];

	std::cin.getline (inputLine, 99);
	if	(
			(strcmp (inputLine, "0") == 0) ||
			(_stricmp (inputLine, "false")))
	{
		x = false;
	} else {
		x = true;
	}	// end if
	return s;
}  // operator >>

   //-------------------------------------------------------------------------

std::wistream& operator >> (std::wistream& s, Boolean& x)
{
	wchar_t inputLine[100];

	std::wcin.getline(inputLine, 99);
	if (
		(wcscmp(inputLine, L"0") == 0) ||
		(_wcsicmp(inputLine, L"false")))
	{
		x = false;
	}
	else {
		x = true;
	}	// end if
	return s;
}  // operator >>