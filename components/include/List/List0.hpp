#pragma once
#include "List/ListKernel.hpp"
/*
	Realization of Queue using raw nodes & pointers
	Author: Dr. Holly
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T>
class List0 : public StdOps<List0<T>>, public ListKernel<List0<T>, T>

{
public: // Standard Operations
	List0();
	List0(const List0& s) = delete;
	~List0();
	void clear(void);
	void transferFrom(List0& source);
	List0& operator = (List0& rhs);

// List0 Specific Operations
	void moveToStart(void);
	void moveToFinish(void);
	void advance(void);
	void addRightFront(T& x);
	void removeRightFront(T& x);
	T& rightFront(void);
	void replaceRightFront(T& x);
	void swapRights(List0& otherS);
	Integer leftLength(void);
	Integer rightLength(void);

	friend wostream& operator<< <T>(wostream& os, List0<T>& s);
	//! updates os
	//! restores s

private: // Representation

	class NodeRecord {
	public:
		T value;
		NodeRecord* next;

		NodeRecord()
		{
			next = NULL;
		}

		NodeRecord(T& newValue)
		{
			value.transferFrom(newValue);
			next = NULL;
		}	// NodeRecord

		NodeRecord(T& newValue, NodeRecord* nextNode)
		{
			value.transferFrom(newValue);
			next = nextNode;
		}	// NodeRecord
	};

	NodeRecord* preFront;
	NodeRecord* lastLeft;
	NodeRecord* lastNode;
	Integer lengthOfLeft;
	Integer lengthOfRight;


private: // Local Operations
	void createNewRep(void);
	void reclaimAllNodes (NodeRecord*& p);
	void displayRep (wostream& os);
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Local Operations
//-----------------------------------------------------------------------

template <class T>
void List0<T>::createNewRep(void)
{
	T temp;
	
	NodeRecord* newNode = new NodeRecord;
	preFront = new NodeRecord();
	lastLeft = preFront;
	lastNode = preFront;
	lengthOfLeft.clear();
	lengthOfRight.clear();
}

//-----------------------------------------------------------------------

template <class T>
void List0<T>::reclaimAllNodes (NodeRecord*& p)
	// ensures: p = NULL;
{
	while (p != NULL) {
		NodeRecord* nodeToDelete = p;
		p = p->next;
		delete nodeToDelete;
	} // end while
}	// reclaimAllNodes

//-----------------------------------------------------------------------

template <class T>
void List0<T>::displayRep (wostream& os)
{
	NodeRecord* p;
	Integer c;

	os << endl << L" preFront: " << preFront << endl;
	os << L" lengthOfLeft: " << lengthOfLeft << endl;
	os << L" lengthOfRight: " << lengthOfRight << endl;
	c = 1;
	p = preFront;
	while (p != NULL) {
		os << L" Node: #" << c;
		os << L" Address: " << p;
		os << L"\t(" << p->value;
		os << L", " << p->next << L")" << endl;
		p = p->next;
		c++;
	}	// end while
}	// displayRep

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

template <class T>
List0<T>::List0()
{
	self.createNewRep();
}	// List0

//-----------------------------------------------------------------------

template <class T>
List0<T>::~List0()
{
	self.reclaimAllNodes(preFront);
}	// ~List0

//-----------------------------------------------------------------------

template <class T>
void List0<T>::clear(void)
{
	self.reclaimAllNodes(preFront);
	self.createNewRep();
}	// clear

//-----------------------------------------------------------------------

template <class T>
void List0<T>::transferFrom(List0& source)
{
	self.reclaimAllNodes(preFront);
	preFront = source.preFront;
	lastLeft = source.lastLeft;
	lastNode = source.lastNode;

	lengthOfLeft = source.lengthOfLeft;
	lengthOfRight = source.lengthOfRight;
	source.createNewRep();
}

//-----------------------------------------------------------------------

template <class T>
List0<T>& List0<T>::operator = (List0& rhs)
{
	self.reclaimAllNodes(preFront);
	self.createNewRep();

	NodeRecord* recvPos = preFront;
	NodeRecord* oldPos = rhs.preFront->next;
	while (oldPos != NULL) {
		T x;
		x = oldPos->value;
		recvPos->next = new NodeRecord(x);
		recvPos = recvPos->next;
		if (oldPos == rhs.lastLeft) {
			// in the rhs list we have found lastLeft location
			// set the lastLeft in the receiving list
			lastLeft = recvPos;
		} // end if
		oldPos = oldPos->next;
	} // end while
	lastNode = recvPos;
	lengthOfLeft = rhs.lengthOfLeft;
	lengthOfRight = rhs.lengthOfRight;

	return *this;
} // operator =

//-----------------------------------------------------------------------

template <class T>
void List0<T>::moveToStart(void)
{
	lastLeft = preFront;
	lengthOfRight += lengthOfLeft;
	lengthOfLeft = 0;
}	// moveToStart

//-----------------------------------------------------------------------

template <class T>
void List0<T>::moveToFinish(void)
{
	lastLeft = lastNode;
	lengthOfLeft += lengthOfRight;
	lengthOfRight = 0;
}	// moveToFinish

//-----------------------------------------------------------------------

template <class T>
void List0<T>::advance(void)
{
	lastLeft = lastLeft->next;
	lengthOfLeft++;
	lengthOfRight--;
}	// advance

//-----------------------------------------------------------------------

template <class T>
void List0<T>::addRightFront(T& x)
{
	NodeRecord* newPos;

	newPos = new NodeRecord(x, lastLeft->next);
	lastLeft->next = newPos;
	lengthOfRight++;
	if (lengthOfRight == 1) {
		lastNode = newPos;
	} // end if
}	// addRightFront

//-----------------------------------------------------------------------

template <class T>
void List0<T>::removeRightFront(T& x)
{
	NodeRecord* temp;

	temp = lastLeft->next;
	x.transferFrom(temp->value);
	lastLeft->next = temp->next;
	delete temp;
	lengthOfRight--;
	if (lengthOfRight == 0) {
		lastNode = lastLeft;
} // end if
}	// removeRightFront

//-----------------------------------------------------------------------

template <class T>
T& List0<T>::rightFront(void)
{
	return lastLeft->next->value;
}  // rightFront


//-----------------------------------------------------------------------

template <class T>
void List0<T>::replaceRightFront(T& x)
{
	T temp;

	temp.transferFrom(x);
	x.transferFrom(lastLeft->next->value);
	lastLeft->next->value.transferFrom(temp);
} // replaceRightFront

//-----------------------------------------------------------------------

template <class T>
void List0<T>::swapRights(List0& s)
{
	// Swap lastLefts
	NodeRecord* temp = lastLeft->next;
	lastLeft->next = s.lastLeft->next;
	s.lastLeft->next = temp;

	// Swap lastNodes
	temp = lastNode;
	lastNode = s.lastNode;
	s.lastNode = temp;

	// Swap left lengths
	int lengthT = lengthOfRight;
	lengthOfRight = s.lengthOfRight;
	s.lengthOfRight = lengthT;

	// Fixup lastNodes
	if (lengthOfRight == 0) {
		lastNode = lastLeft;
	} // end if
	if (s.lengthOfRight == 0) {
		s.lastNode = s.lastLeft;
	} // end if
}	// swapRights

//-----------------------------------------------------------------------

template <class T>
Integer List0<T>::leftLength(void)
{
	return lengthOfLeft;
}	// leftLength

//-----------------------------------------------------------------------

template <class T>
inline Integer List0<T>::rightLength(void)
{
	return lengthOfRight;
}	// rightLength

//-----------------------------------------------------------------------
/*
template <class T>
wostream& operator<<(wostream& os, List0<T>& s)
{
	//s.displayRep(os);
	os << L"(<";
	int lengthOfLeft = s.leftLength();

	s.moveToStart();
	for (int k = 0, lastItem = lengthOfLeft - 1; k < lengthOfLeft; k++) {
		os << s.rightFront();
		s.advance();
		if (k < lastItem) {
			os << L",";
		} // end if
	}
	os << L">,<";

	int lengthOfRight = s.rightLength();
	for (int k = 0, lastItem = lengthOfRight - 1; k < lengthOfRight; k++) {
		os << s.rightFront();
		s.advance();
		if (k < lastItem) {
			os << L",";
		} // end if
	}
	os << L">)";

	// reset fence to original location
	s.moveToStart();
	for (int k = 0; k < lengthOfLeft; k++) {
		s.advance();
	}
	return os;
}
*/

template <class T>
wostream& operator<<(wostream& os, List0<T>& s)
{
	// Do not change this operation
#ifdef _DEBUG
	// In Debug mode, this code traverses the linked list
	// and builds a Text representation of the Node values
	List0<T>::NodeRecord* p;
	Integer c;

	os << L"{";
	c = 0;
	p = s.preFront;
	while (p != NULL) {
		os << L"(" << c << "," << p->value << ")";
		if (p->next != NULL) {
			os << ",";
		}
		p = p->next;
		c++;
	}	// end while
	os << L"}";
#else
	os << L"(<";
	int lengthOfLeft = s.leftLength();

	s.moveToStart();
	for (int k = 0, lastItem = lengthOfLeft - 1; k < lengthOfLeft; k++) {
		os << s.rightFront();
		s.advance();
		if (k < lastItem) {
			os << L",";
		} // end if
	}
	os << L">,<";

	int lengthOfRight = s.rightLength();
	for (int k = 0, lastItem = lengthOfRight - 1; k < lengthOfRight; k++) {
		os << s.rightFront();
		s.advance();
		if (k < lastItem) {
			os << L",";
		} // end if
	}
	os << L">)";

	// reset fence to original location
	s.moveToStart();
	for (int k = 0; k < lengthOfLeft; k++) {
		s.advance();
	}
#endif

	return os;
}