#pragma once

// Basic Text
// Author: Dr. Holly

//------------------------------------------------------------------------
//-- Interface -----------------------------------------------------------
//------------------------------------------------------------------------

class Text: public StdOps<Text>
  //! is modeled by string(Character)
  //!   exemplar self
{
public: // Standard Operations
	Text ();
	//! replaces self
	//! ensures: self = < >
	~Text ();
	void clear (void);
	//! alters self
	//! ensures: self = < >
	void transferFrom(Text& source);
	//! replaces self
	//! clears source
	//! ensures self = #source

	// Text Specific Operations
	Text (wchar_t* cString);
	//! replaces self
	//! restores cString
	//! requires: cString to be \0 terminated
	//!  ensures: self = cString

	Text(const wchar_t* cString);
	//! replaces self
	//! restores cString
	//! requires: cString to be \0 terminated
	//!  ensures: self = cString

	Text(char* cStringNarrow);
	//! replaces self
	//! restores cStringNarrow
	//! requires: cStringNarrow to be \0 terminated
	//!  ensures: self = cStringNarrow

	Text& operator = (wchar_t* cString);
	//! replaces self
	//! restores cString
	//! requires: cString to be \0 terminated
	//!  ensures: self = cString

	Text& operator = (const wchar_t* cString);
	//! replaces self
	//! restores cString
	//! requires: cString to be \0 terminated
	//!  ensures: self = cString

	Text& operator = (char* cStringNarrow);
	//! replaces self
	//! restores cStringNarrow
	//! requires: cStringNarrow to be \0 terminated
	//!  ensures: self = cStringNarrow

	Text& operator = (Text& rhs);
	//! replaces self
	//! ensures: self = rhs

	// operator ==

	Boolean operator == (Text& rhs);
	//! restores self, rhs
	//! ensures: "operator ==" = (self = rhs)

	Boolean operator == (wchar_t* rhsWide);
	//! restores self, rhsWide
	//! ensures: "operator ==" = (self = rhsWide)

	Boolean operator == (char* rhsNarrow);
	//! restores self, rhsNarrow
	//! ensures: "operator ==" = (self = rhsNarrow)

	friend 	Boolean operator == (wchar_t* lhsWide, Text& rhs);
	//! restores lhsWide, rhs
	//! ensures: "operator ==" = (lhsWide = rhs)

	friend 	Boolean operator == (char* lhsNarrow, Text& rhs);
	//! restores lhsNarrow, rhs
	//! ensures: "operator ==" = (lhsNarrow = rhs)

	// operator !=

	Boolean operator != (Text& rhs);
	//! restores self, rhs
	//! ensures: "operator !=" = (self = rhs)

	Boolean operator != (wchar_t* rhsWide);
	//! restores self, rhsWide
	//! ensures: "operator !=" = (self <> rhsWide)

	Boolean operator != (char* rhsNarrow);
	//! restores self, rhsNarrow
	//! ensures: "operator !=" = (self <> rhsNarrow)

	friend 	Boolean operator != (wchar_t* lhsWide, Text& rhs);
	//! restores lhsWide, rhs
	//! ensures: "operator !=" = (lhsWide <> rhs)

	friend 	Boolean operator != (char* lhsNarrow, Text& rhs);
	//! restores lhsNarrow, rhs
	//! ensures: "operator !=" = (lhsNarrow <> rhs)

	// operator <

	Boolean operator < (Text& rhs);
	//! restores self, rhs
	//! ensures: "operator <" = (self < rhs)

	Boolean operator < (wchar_t* rhsWide);
	//! restores self, rhsWide
	//! ensures: "operator <" = (self < rhsWide)
	
	Boolean operator < (char* rhsNarrow);
	//! restores self, rhsNarrow
	//! ensures: "operator <" = (self < rhsNarrow)

	friend 	Boolean operator < (wchar_t* lhsWide, Text& rhs);
	//! restores lhsWide, rhs
	//! ensures: "operator <" = (lhsWide < rhs)

	friend 	Boolean operator < (char* lhsNarrow, Text& rhs);
	//! restores lhsNarrow, rhs
	//! ensures: "operator <" = (lhsNarrow < rhs)

	// operator <=

	Boolean operator <= (Text& rhs);
	//! restores self, rhs
	//! ensures: "operator <=" = (self <= rhs)

	Boolean operator <= (wchar_t* rhsWide);
	//! restores self, rhsWide
	//! ensures: "operator <=" = (self <= rhsWide)

	Boolean operator <= (char* rhsNarrow);
	//! restores self, rhsNarrow
	//! ensures: "operator <=" = (self <= rhsNarrow)

	friend 	Boolean operator <= (wchar_t* lhsWide, Text& rhs);
	//! restores lhsWide, rhs
	//! ensures: "operator <=" = (lhsWide <= rhs)

	friend 	Boolean operator <= (char* lhsNarrow, Text& rhs);
	//! restores lhsNarrow, rhs
	//! ensures: "operator <=" = (lhsNarrow <= rhs)

	// operator >

	Boolean operator > (Text& rhs);
	//! restores self, rhs
	//! ensures: "operator >" = (self > rhs)

	Boolean operator > (wchar_t* rhsWide);
	//! restores self, rhsWide
	//! ensures: "operator >" = (self > rhsWide)

	Boolean operator > (char* rhsNarrow);
	//! restores self, rhsNarrow
	//! ensures: "operator >" = (self > rhsNarrow)

	friend 	Boolean operator > (wchar_t* lhsWide, Text& rhs);
	//! restores lhsWide, rhs
	//! ensures: "operator >" = (lhsWide > rhs)

	friend 	Boolean operator > (char* lhsNarrow, Text& rhs);
	//! restores lhsNarrow, rhs
	//! ensures: "operator >" = (lhsNarrow > rhs)

	// operator >=

	Boolean operator >= (Text& rhs);
	//! restores self, rhs
	//! ensures: "operator >=" = (self >= rhs)

	Boolean operator >= (wchar_t* rhsWide);
	//! restores self, rhsWide
	//! ensures: "operator >=" = (self >= rhsWide)

	Boolean operator >= (char* rhsNarrow);
	//! restores self, rhsNarrow
	//! ensures: "operator >=" = (self >= rhsNarrow)

	friend 	Boolean operator >= (wchar_t* lhsWide, Text& rhs);
	//! restores lhsWide, rhs
	//! ensures: "operator >=" = (lhsWide >= rhs)

	friend 	Boolean operator >= (char* lhsNarrow, Text& rhs);
	//! restores lhsNarrow, rhs
	//! ensures: "operator >=" = (lhsNarrow >= rhs)

	void add (Integer position, Character c);
	//! updates self
	//! restores position, c
	//! requires:  0 <= position <= |self|
	//!  ensures:  self = #self[0,position) * <#c> * #self[position,|self|)

	void remove (Integer position, Character& c);
	//! updates self
	//! restores position
	//! produces c
	//! requires:  0 <= position < |self|
	//!  ensures:  self = #self[0,position) * #self[position + 1,|self|)

	Integer size (void);
	//! restores self
	//! ensures:   size = |self|

	void append (Text& from);
	//! restores	from
	//! ensures:	self = #self * from

	void copyToCString (wchar_t* cStringWide);
	//! restores	self
	//! replaces    cStringWide
	//! requires:	|cStringWide| > |self|
	//!  ensures:	cStringWide = self

	friend std::wostream& operator << (std::wostream& s, Text& x);
	//! updates s
	//! restores x

	friend std::wistream& operator >> (std::wistream& s, Text& x);
	//! updates s, x

	friend std::istream& operator >> (std::istream& s, Text& x);
	//! updates s, x

	operator wchar_t* ();
	//! restores self
	//! ensures:   wchar_t* () = rep->cString

private:
   // local operations
	void createNewRep(const wchar_t* cString);
	void createNewRep(wchar_t* cString);
	void reclaimRepsString(void);
	void convertToListRep (void);
	void convertToCStringRep (void);
	void moveCurrentIntoPosition (Integer position);

   // Unimplemented local operations
	Text (const Text& s);
	Text* operator & (void);
	const Text* operator & (void) const;

	// don't allow ASCII character output
	__declspec(deprecated("** Use 'wcout' for type Text **"))
		friend std::ostream& operator << (std::ostream& s, Text& x);

private:	// Representation
	class NodeRep;
	typedef NodeRep* Node;
	class NodeRep {
	public:
		Character c;
		Node target;

		NodeRep() {}
	};

	class CharacterListRep {
	public:
		Node smartNode;
		Node current;
		Integer position;
		CharacterListRep() {}
	};

	class TextRep {
	public:
		wchar_t* cString;
		CharacterListRep s;
		Boolean inListRep;
		Integer length;

		TextRep() {};
	};

	TextRep* rep;
};

template <class T>
void toText(T& x, Text& y)
// restores x
// replaces y
// ensures y = Text version of x
{
	std::wostringstream oss;

	oss << x;
	std::wstring s = oss.str();
	y = s.c_str();
} // toText

