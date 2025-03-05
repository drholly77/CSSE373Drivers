/*
Implementation of wrapper for the scalar type int
Author: Dr. Holly
*/

#include "wrapper.h"


std::wostream& operator << (std::wostream& s, Integer& x)
{
	s << x.i;
	return s;
} // operator <<

std::istream& operator >> (std::istream& s, Integer& x)
{
	char input_line[100];
	int value;

	std::cin.getline (input_line, 99);
	sscanf (input_line, "%d", &value);
	x = value;
	return s;
}  // operator >>

std::wistream& operator >> (std::wistream& s, Integer& x)
{
	wchar_t input_line[100];
	int value;

	std::wcin.getline(input_line, 99);
	swscanf(input_line, L"%d", &value);
	x = value;
	return s;
}  // operator >>

