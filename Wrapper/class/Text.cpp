// Basic Text
// Author: Dr. Holly
#include "wrapper.h"

// Convention
/*
When !inListRep, linked list rep looks like the following:

rep.s
					|----|     |-------------|
 s.smartNode  |  *-+---->|      | NULL |
					|----|     |-------------|
 s.current		|  *-+-----------^
					|----|
 s.position		|  0 |
					|----|


When inListRep, cString rep looks like the following:
rep.cString = NULL;
*/

//-----------------------------------------------------------------------
// Local Operations
//-----------------------------------------------------------------------


void Text::createNewRep(const wchar_t* cString)
{
	rep = new TextRep;	
	rep->length = (int)wcslen(cString);
	rep->cString = (wchar_t *)new wchar_t[rep->length + 1];
	wcscpy (rep->cString, cString);

	rep->s.smartNode = new NodeRep;
	rep->s.smartNode->target = NULL;
	rep->s.current = rep->s.smartNode;
} // createNewRep

  //-----------------------------------------------------------------------

void Text::createNewRep(wchar_t* cString)
{
	rep = new TextRep;
	rep->length = (int)wcslen(cString);
	rep->cString = (wchar_t *)new wchar_t[rep->length + 1];
	wcscpy(rep->cString, cString);

	rep->s.smartNode = new NodeRep;
	rep->s.smartNode->target = NULL;
	rep->s.current = rep->s.smartNode;
} // createNewRep

//-----------------------------------------------------------------------

void Text::reclaimRepsString ()
{
	Node p;
	Node old_node;

	// Dispose of Linked List
	p = rep->s.smartNode;
	while (p != NULL) {
		old_node = p;
		p = p->target;
		delete old_node;
	}	// end while

	// Dispose of cString
	delete [] rep->cString;

	delete rep;
}	// ~Text

//-----------------------------------------------------------------------

void Text::convertToListRep (void)
{
	Node p;
	Node new_node;
	Integer i;

	p = rep->s.smartNode;
	for (i = 0; i < rep->length; i++) {
		new_node = new NodeRep;
		new_node->c = (char)rep->cString[i];
		p->target = new_node;
		p = new_node;
	}	// end for
	// NULL at end of linked list
	p->target = NULL;

	delete [] rep->cString;
	rep->cString = NULL;
	rep->inListRep = true;
}	// convertToListRep

//-----------------------------------------------------------------------

void Text::convertToCStringRep (void)
{
	Node p;
	Node old_node;
	Integer i;
	Character c;

	rep->cString = (wchar_t *)new wchar_t[rep->length + 1];
	p = rep->s.smartNode->target;
	rep->s.smartNode->target = NULL;
	rep->s.current = rep->s.smartNode;
	rep->s.position = 0;

	for (i = 0; i < rep->length; i++) {
		rep->cString[i] = p->c;
		old_node = p;
		p = p->target;
	  delete old_node;
	}	// end for

	rep->cString[rep->length] = '\0';
	rep->inListRep = false;
}	// convertToCStringRep

//-----------------------------------------------------------------------

void Text::moveCurrentIntoPosition (
		Integer position
	)
{
	Integer i;

	if (!rep->inListRep) {
		convertToListRep ();
	} else {
	// already inListRep
		if (rep->s.position > position) {
			rep->s.position = 0;
			rep->s.current = rep->s.smartNode;
		}	// end if
	}	// end if
	// Move into position
	for (i = rep->s.position; i < position; i++) {
		rep->s.current = rep->s.current->target;
	}	// end for
	rep->s.position = position;
}	// moveCurrentIntoPosition

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

Text::Text ()
{
	createNewRep(L"");
}	// Text

//-------------------------------------------------------------------------

Text::Text (wchar_t* cString)
{
	createNewRep(cString);
}	// Text

	//-------------------------------------------------------------------------

Text::Text(const wchar_t* cString)
{
	createNewRep(cString);
}	// Text

	//-------------------------------------------------------------------------

Text::Text(char* cStringNarrow)
{
	size_t stringLength = strlen(cStringNarrow);
	wchar_t* cStringWide = (wchar_t *)new wchar_t[stringLength + 1];
	for (size_t k = 0; k < stringLength; k++) {
		mbtowc(&cStringWide[k], &cStringNarrow[k], sizeof(char));
	} // end for
	cStringWide[stringLength] = '\0';	
	self.createNewRep(cStringWide);
	delete[] cStringWide;
}	// Text

//-------------------------------------------------------------------------

Text::~Text ()
{
	reclaimRepsString();
}	// ~Text

//-------------------------------------------------------------------------

Text& Text::operator = (wchar_t* cString)
{
	self.reclaimRepsString();
	self.createNewRep(cString);

	return *this;
}	// operator =

	//-------------------------------------------------------------------------

Text& Text::operator = (const wchar_t* cString)
{
	self.reclaimRepsString();
	self.createNewRep(cString);

	return *this;
}	// operator =

	//-------------------------------------------------------------------------

Text& Text::operator = (char* cStringNarrow)
{
	self.reclaimRepsString();
	size_t stringLength = strlen(cStringNarrow);
	wchar_t* cStringWide = (wchar_t *)new wchar_t[stringLength + 1];
	for (size_t k = 0; k < stringLength; k++) {
		mbtowc(&cStringWide[k], &cStringNarrow[k], sizeof(char));
	} // end for
	cStringWide[stringLength] = '\0';
	self.createNewRep(cStringWide);
	delete[] cStringWide;

	return *this;
}	// operator =

//-------------------------------------------------------------------------

Text& Text::operator = (Text& rhs)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();
	self.reclaimRepsString();
	self.createNewRep(rhs.rep->cString);
	return *this;
}	// operator = 

//-------------------------------------------------------------------------

void Text::transferFrom(Text& source)
{
	if (source.rep->inListRep)
		source.convertToCStringRep ();
	self.reclaimRepsString();
	self.createNewRep(source.rep->cString);
	source.reclaimRepsString();
	source.createNewRep(L"");
}	// transferFrom

//-------------------------------------------------------------------------

void Text::clear (void)
{
	self.reclaimRepsString();
	self.createNewRep(L"");
}	// clear

//-------------------------------------------------------------------------

Boolean Text::operator == (Text& rhs)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (rep->cString, rhs.rep->cString) == 0;
}	// operator ==

//-------------------------------------------------------------------------

Boolean Text::operator == (wchar_t* rhsWide)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return wcscmp (rep->cString, rhsWide) == 0;
}	// operator ==

	//-------------------------------------------------------------------------

Boolean Text::operator == (char* rhsNarrow)
{
	Text rhsWide = rhsNarrow;

	return wcscmp(rep->cString, rhsWide.rep->cString) == 0;
}	// operator ==

//-------------------------------------------------------------------------

Boolean operator == (wchar_t* lhsWide, Text& rhs)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (lhsWide, rhs.rep->cString) == 0;
}	// operator ==

	//-------------------------------------------------------------------------

Boolean operator == (char* lhsNarrow, Text& rhs)
{
	Text lhsWide = lhsNarrow;

	if (rhs.rep->inListRep)
		rhs.convertToCStringRep();
	return wcscmp(lhsWide.rep->cString, rhs.rep->cString) == 0;
}	// operator ==

//-------------------------------------------------------------------------

Boolean Text::operator != (Text& rhs)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (rep->cString, rhs.rep->cString) != 0;
}	// operator !=

//-------------------------------------------------------------------------

Boolean Text::operator != (wchar_t* rhsWide)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return wcscmp (rep->cString, rhsWide) != 0;
}	// operator !=

	//-------------------------------------------------------------------------

Boolean Text::operator != (char* rhsNarrow)
{
	Text rhsWide = rhsNarrow;

	return wcscmp(rep->cString, rhsWide.rep->cString) != 0;
}	// operator !=

//-------------------------------------------------------------------------

Boolean operator != (wchar_t* lhsWide, Text& rhs)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (lhsWide, rhs.rep->cString) != 0;
}	// operator !=

	//-------------------------------------------------------------------------

Boolean operator != (char* lhsNarrow, Text& rhs)
{
	Text lhsWide = lhsNarrow;

	if (rhs.rep->inListRep)
		rhs.convertToCStringRep();
	return wcscmp(lhsWide.rep->cString, rhs.rep->cString) != 0;
}	// operator !=

//-------------------------------------------------------------------------

Boolean Text::operator < (Text& rhs)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (rep->cString, rhs.rep->cString) < 0;
}	// operator <

//-------------------------------------------------------------------------

Boolean Text::operator < (wchar_t* rhsWide)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return wcscmp (rep->cString, rhsWide) < 0;
}	// operator <

	//-------------------------------------------------------------------------

Boolean Text::operator < (char* rhsNarrow)
{
	Text rhsWide = rhsNarrow;

	if (rep->inListRep)
		convertToCStringRep();

	return wcscmp(rep->cString, rhsWide.rep->cString) < 0;
}	// operator <

//-------------------------------------------------------------------------

Boolean operator < (wchar_t* lhsWide, Text& rhs)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (lhsWide, rhs.rep->cString) < 0;
}	// operator <

	//-------------------------------------------------------------------------

Boolean operator < (char* lhsNarrow, Text& rhs)
{
	Text lhsWide = lhsNarrow;

	if (rhs.rep->inListRep)
		rhs.convertToCStringRep();

	return wcscmp(lhsWide.rep->cString, rhs.rep->cString) < 0;
}	// operator <

//-------------------------------------------------------------------------

Boolean Text::operator <= (Text& rhs)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (rep->cString, rhs.rep->cString) <= 0;
}	// operator <=

//-------------------------------------------------------------------------

Boolean Text::operator <= (wchar_t* rhsWide)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return wcscmp (rep->cString, rhsWide) <= 0;
}	// operator <=

	//-------------------------------------------------------------------------

Boolean Text::operator <= (char* rhsNarrow)
{
	Text rhsWide = rhsNarrow;

	if (rep->inListRep)
		convertToCStringRep();

	return wcscmp(rep->cString, rhsWide.rep->cString) <= 0;
}	// operator <=

//-------------------------------------------------------------------------

Boolean operator <= (wchar_t* lhsWide, Text& rhs)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (lhsWide, rhs.rep->cString) <= 0;
}	// operator <=

	//-------------------------------------------------------------------------

Boolean operator <= (char* lhsNarrow, Text& rhs)
{
	Text lhsWide = lhsNarrow;

	if (rhs.rep->inListRep)
		rhs.convertToCStringRep();

	return wcscmp(lhsWide.rep->cString, rhs.rep->cString) <= 0;
}	// operator <=

//-------------------------------------------------------------------------

Boolean Text::operator > (Text& rhs)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (rep->cString, rhs.rep->cString) > 0;
}	// operator >

//-------------------------------------------------------------------------

Boolean Text::operator > (wchar_t* rhsWide)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return wcscmp (rep->cString, rhsWide) > 0;
}	// operator >

	//-------------------------------------------------------------------------

Boolean Text::operator > (char* rhsNarrow)
{
	Text rhsWide = rhsNarrow;

	if (rep->inListRep)
		convertToCStringRep();

	return wcscmp(rep->cString, rhsWide.rep->cString) > 0;
}	// operator >

//-------------------------------------------------------------------------

Boolean operator > (wchar_t* lhsWide, Text& rhs)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (lhsWide, rhs.rep->cString) > 0;
}	// operator >

	//-------------------------------------------------------------------------

Boolean operator > (char* lhsNarrow, Text& rhs)
{
	Text lhsWide = lhsNarrow;

	if (rhs.rep->inListRep)
		rhs.convertToCStringRep();

	return wcscmp(lhsWide.rep->cString, rhs.rep->cString) > 0;
}	// operator >


//-------------------------------------------------------------------------

Boolean Text::operator >= (Text& rhs)
{
	if (rep->inListRep)
		convertToCStringRep ();
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (rep->cString, rhs.rep->cString) >= 0;
}	// operator >=

//-------------------------------------------------------------------------

Boolean Text::operator >= (wchar_t* rhsWide)
{
	if (rep->inListRep)
		convertToCStringRep ();

	return wcscmp (rep->cString, rhsWide) >= 0;
}	// operator >=

	//-------------------------------------------------------------------------

Boolean Text::operator >= (char* rhsNarrow)
{
	Text rhsWide = rhsNarrow;

	if (rep->inListRep)
		convertToCStringRep();

	return wcscmp(rep->cString, rhsWide.rep->cString) >= 0;
}	// operator >=

//-------------------------------------------------------------------------

Boolean operator >= (wchar_t* lhsWide, Text& rhs)
{
	if (rhs.rep->inListRep)
		rhs.convertToCStringRep ();

	return wcscmp (lhsWide, rhs.rep->cString) >= 0;
}	// operator >=

	//-------------------------------------------------------------------------

Boolean operator >= (char* lhsNarrow, Text& rhs)
{
	Text lhsWide = lhsNarrow;

	if (rhs.rep->inListRep)
		rhs.convertToCStringRep();

	return wcscmp(lhsWide.rep->cString, rhs.rep->cString) >= 0;
}	// operator >=

//-------------------------------------------------------------------------

void Text::add (Integer position, Character c)
{
	Node new_node;

	moveCurrentIntoPosition (position);
	new_node = new NodeRep;
	new_node->c = c;
	new_node->target = rep->s.current->target;
	rep->s.current->target = new_node;
	rep->length++;
}	// add

//-------------------------------------------------------------------------

void Text::remove (Integer position, Character& c)
{
	Node old_node;

	moveCurrentIntoPosition (position);
	old_node = rep->s.current->target;
	rep->s.current->target = old_node->target;
	c = old_node->c;
	delete old_node;
	rep->length--;
}	// remove

//-------------------------------------------------------------------------

Integer Text::size (void)
{
	return rep->length;
}	// size

//-------------------------------------------------------------------------

void Text::append (Text& from)
{
	wchar_t* cString;
	Integer length;

	if (rep->inListRep)
		convertToCStringRep ();
	if (from.rep->inListRep)
		from.convertToCStringRep ();

	length = (int)wcslen (rep->cString) + 
			 (int)wcslen (from.rep->cString);
	cString = (wchar_t *)new wchar_t[length + 1];
	wcscpy (cString, rep->cString);
	wcscat(cString, from.rep->cString);

	// Dispose of original cString
	delete [] rep->cString;

	rep->cString = cString;
	rep->length = (int)wcslen (rep->cString);
}  // append

//-------------------------------------------------------------------------

void Text::copyToCString (wchar_t* cStringWide)
{
	if (rep->inListRep)
		convertToCStringRep ();
	wcscpy (cStringWide, rep->cString);
}  // copyToCString

//-------------------------------------------------------------------------

Text::operator wchar_t* () 
{ 
	if (rep->inListRep)
		convertToCStringRep ();

	return rep->cString;
} // operator wchar_t* ()

//-------------------------------------------------------------------------

std::wostream& operator << (std::wostream& os, Text& x)
{
 	if (x.rep->inListRep)
		x.convertToCStringRep ();

	os << L"\"" << x.rep->cString << L"\"";
   return os;
}  // operator <<

//-------------------------------------------------------------------------

std::wistream& operator >> (std::wistream& s, Text& x)
{
	wchar_t input_line[100];

	std::wcin.getline(input_line, 99);
	x = input_line;
	return s;
}  // operator >>

   //-------------------------------------------------------------------------

std::istream& operator >> (std::istream& s, Text& x)
{
	char input_line[100];

	std::cin.getline(input_line, 99);
	x = input_line;
	return s;
}  // operator >>
