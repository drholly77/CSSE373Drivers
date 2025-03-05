#pragma once
/*
	Realization of QueueOfText using raw nodes & pointers
	Author: Dr. Holly
*/


//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------


class QueueOfText
		//! is modeled by string(Text)
		//! exemplar self
{
public: // Standard Operations
	QueueOfText ();
		//! replaces self
		//! ensures: self = <>
	~QueueOfText ();
	void clear (void);
		//! clears self
	void transferFrom (QueueOfText& source);
		//! replaces self
		//! clears source
		//! ensures: self = #source
	QueueOfText& operator = (QueueOfText& rhs);
		//! replaces self
		//! restores rhs
		//! ensures: self = rhs

	// QueueOfText Specific Operations
	void enqueue (Text& x);
		//! updates self
		//! clears x
		//! ensures: self = #self * <#x>
	void dequeue (Text& x);
		//! updates self
		//! replaces x
		//! requires: self /= <>
		//! ensures: <x> = #self[0,1)  and  
		//!          self = #self[1,|#self|)
	void replaceFront (Text& x);
		//! updates self, x
		//! requires: self /= <>
		//! ensures: <x> = #self[0,1) and
		//!          self = <#x> * #self[1,|#self|)
	Text& front(void);
		//! restores self
		//! requires: self /= <>
		//! ensures: <front> = #self[0,1)
	Integer length (void);
		//! restores self
		//! ensures: length = |self|

	friend wostream& operator<< (wostream &os, QueueOfText& q);
		//! updates os
		//! restores q

private: // Representation

	class NodeRecord {
	public:
		Text value;
		NodeRecord* next;
	};

	NodeRecord* head;

private: // Local Operations
	Integer countNodes (NodeRecord* p);
	void copyNodes (NodeRecord*& toHead, NodeRecord* fromHead);
	void reclaimAllNodes (NodeRecord*& p);
	void displayRep (wostream &os);

private: // Disallowed QueueOfText Operations
	QueueOfText (const QueueOfText& s);
	QueueOfText* operator & (void) {return this;};
	const QueueOfText* operator & (void) const {return this;};
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Local Operations
//-----------------------------------------------------------------------


Integer QueueOfText::countNodes (NodeRecord* p)
	// ensures: countNodes = number of nodes in linked list starting with node located at address p;
{
	if (p != NULL) {
		return countNodes(p->next) + 1;
	} else {
		return 0;
	} // end if
}	// countNodes

//-----------------------------------------------------------------------


void QueueOfText::copyNodes (NodeRecord*& toP, NodeRecord* fromP)
{
	if (fromP == NULL) {
		toP = NULL;
	} else {
		toP = new NodeRecord;

		toP->value = fromP->value;
		copyNodes(toP->next, fromP->next);
	} // end if
} // copyNodes

//-----------------------------------------------------------------------


void QueueOfText::reclaimAllNodes (NodeRecord*& p)
	// ensures: p = NULL;
{
	if (p != NULL) {
		reclaimAllNodes(p->next);
		delete p;
	} // end if
}	// reclaimAllNodes

//-----------------------------------------------------------------------


void QueueOfText::displayRep (wostream &os)
{
	NodeRecord* p;
	Integer c;

	os << L"&head: " << &head << endl;
	os << L" head: " << head << endl;
	c = 1;
	p = head;
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

QueueOfText::QueueOfText ()
{
	head = NULL;
}	// QueueOfText

//-----------------------------------------------------------------------

QueueOfText::~QueueOfText ()
{
	reclaimAllNodes(head);
}	// ~QueueOfText

//-----------------------------------------------------------------------

void QueueOfText::clear(void)
{
	reclaimAllNodes(head);
	head = NULL;
}	// clear

//-----------------------------------------------------------------------

void QueueOfText::transferFrom(QueueOfText& source)
{
	reclaimAllNodes(head);
	head = source.head;
	source.head = NULL;
}

//-----------------------------------------------------------------------

QueueOfText& QueueOfText::operator = (QueueOfText& rhs)
{
	reclaimAllNodes(head);
	copyNodes(head, rhs.head);
	return *this;
} // operator =

//-----------------------------------------------------------------------

void QueueOfText::enqueue (Text& x)
{
	NodeRecord* newNode = new NodeRecord;

	newNode->value.transferFrom(x);
	newNode->next = NULL;

	if (head == NULL) {
		head = newNode;
	} else {
		NodeRecord* p;

		p = head;
		while (p->next != NULL) {
			p = p->next;
		}	// end while
		p->next = newNode;
	} // end if
}	// enqueue

//-----------------------------------------------------------------------

void QueueOfText::dequeue (Text& x)
{
	NodeRecord* existingNode;

	existingNode = head;
	x.transferFrom(existingNode->value);
	head = existingNode->next;
	delete existingNode;
}	// dequeue

//-----------------------------------------------------------------------

void QueueOfText::replaceFront(Text& x)
{
	Text temp;

	temp.transferFrom(head->value);
	head->value.transferFrom(x);
	x.transferFrom(temp);
}	// replaceFront

//-----------------------------------------------------------------------

Text& QueueOfText::front(void)
{
	return head->value;
}  // front

//-----------------------------------------------------------------------

Integer QueueOfText::length (void)
{
	return countNodes(head);
}	// length

//-----------------------------------------------------------------------

wostream& operator<<(wostream &os, QueueOfText& q)
{
#ifdef NDEBUG
	QueueOfText temp;

	os << L"<";

	for (int k = 0, z = q.length(), lastItem = z - 1; k < z; k++) {
		Text x;

		q.dequeue(x);
		os << x;
		temp.enqueue(x);
		if (k < lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L">";
	q.transferFrom(temp);
#else
	q.displayRep(os);
#endif
	return os;
}

