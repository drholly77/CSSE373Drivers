#pragma once
#include "Queue/QueueKernel.hpp"

/*
	Realization of Queue using C++ nodes & pointers
*/

template <class T>
class Queue0: public StdOps<Queue0<T>>, public QueueKernel<T>
{
public: // Standard Operations
	Queue0 ();
	Queue0 (const Queue0& s) = delete;
	~Queue0 ();
	void clear (void);
	void transferFrom (Queue0& source);
	Queue0& operator = (Queue0& rhs);

	// Queue0 Specific Operations
	void enqueue (T& x);
	void dequeue (T& x);
	void replaceFront (T& x);
	T& front(void);
	Integer length (void);

	friend wostream& operator<< <T>(wostream& os, Queue0<T>& q);
		//! updates os
		//! restores q

private: // Representation
	/*
	Abstract Math Model for nodes and pointers
	-- Is a function from memory address to data stored at that address
	-- Use Natural numbers to represent concrete memory addresses
	-- NULL address = zero
	-- All non-NULL addresses are > 0
	-- Start non-NULL addresses at one and increment from there

	Abstract Math Model for Queue implemented using nodes and pointers
	-- 2-tuple representing the Queue
	-- 1st item in Queue's 2-tuple is the address stored in head
	-- 2nd item in Queue's 2-tuple is a set of 2-tuples, each of these 2-tuples
	--   This set of 2-tuples represents the function from memory address to node's value
	--   Each 2-tuple in the set represents one node in the linked list
	--   Node 2-tuple's 1st element is the value of type T
	--   Node 2-tuple's 2nd element is the abstract address to the next node in the list, or zero if last node in the linked list
	*/
	class NodeRecord {
	public:
		T value;
		NodeRecord* next;
	};

	NodeRecord* head;

#ifdef _DEBUG
public:
	static int nodeCount;
private:
#endif

private: // Local Operations
	Integer countNodes (NodeRecord* p);
	void copyNodes (NodeRecord*& toHead, NodeRecord* fromHead);
	void reclaimAllNodes (NodeRecord*& p);
};

//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Local Operations
//-----------------------------------------------------------------------

#ifdef _DEBUG

template <class T>
int Queue0<T>::nodeCount = 0;

#define new(dataType) new dataType; nodeCount++;
#define delete(dataType) delete dataType; nodeCount--;

#endif

template <class T>
Integer Queue0<T>::countNodes (NodeRecord* p)
	// ensures: countNodes = number of nodes in linked list starting with node located at address p;
{
	if (p != NULL) {
		return countNodes(p->next) + 1;
	} else {
		return 0;
	} // end if
}	// countNodes

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::copyNodes (NodeRecord*& toP, NodeRecord* fromP)
{
	if (fromP == NULL) {
		toP = NULL;
	} else {
		toP = new(NodeRecord);

		toP->value = fromP->value;
		copyNodes(toP->next, fromP->next);
	} // end if
} // copyNodes

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::reclaimAllNodes (NodeRecord*& p)
	// ensures: p = NULL;
{
	if (p != NULL) {
		reclaimAllNodes(p->next);
		delete(p);
	} // end if
}	// reclaimAllNodes

//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

template <class T>
Queue0<T>::Queue0 ()
{
	head = NULL;
}	// Queue0

//-----------------------------------------------------------------------

template <class T>
Queue0<T>::~Queue0 ()
{
	reclaimAllNodes(head);
}	// ~Queue0

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::clear(void)
{
	reclaimAllNodes(head);
	head = NULL;
}	// clear

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::transferFrom(Queue0& source)
{
	reclaimAllNodes(Queue0::head);
	head = source.head;
	source.head = NULL;
}	// transferFrom

//-----------------------------------------------------------------------

template <class T>
Queue0<T>& Queue0<T>::operator = (Queue0& rhs)
{
	reclaimAllNodes(head);
	copyNodes(head, rhs.head);
	return *this;
}	// operator =

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::enqueue (T& x)
{
	NodeRecord* newNode = new(NodeRecord);

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

template <class T>
void Queue0<T>::dequeue (T& x)
{
	NodeRecord* existingNode;

	existingNode = head;
	x.transferFrom(existingNode->value);
	head = existingNode->next;
	delete(existingNode);
}	// dequeue

//-----------------------------------------------------------------------

template <class T>
void Queue0<T>::replaceFront(T& x)
{
	T temp;

	temp.transferFrom(head->value);
	head->value.transferFrom(x);
	x.transferFrom(temp);
}	// replaceFront

//-----------------------------------------------------------------------

template <class T>
T& Queue0<T>::front(void)
{
	return head->value;
}  // front

//-----------------------------------------------------------------------

template <class T>
Integer Queue0<T>::length (void)
{
	return countNodes(head);
}	// length

//-----------------------------------------------------------------------

template <class T>
wostream& operator<<(wostream& os, Queue0<T>& q)
{
#ifdef NDEBUG
	Queue0<T> temp;

	os << L"<";

	for (int k = 0, z = q.length(), lastItem = z - 1; k < z; k++) {
		T x;

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
	Queue0<T>::NodeRecord* p;
	Integer currAbsNodeAddr, nextAbsNodeAddr;

	currAbsNodeAddr = 1;
	if (q.head == NULL) {
		os << L"(0,";
	}
	else {
		os << L"(1,";
	}

	os << L"{";
	p = q.head;
	while (p != NULL) {
		Boolean noNextNode = (p->next == NULL);
		nextAbsNodeAddr = noNextNode ? 0 : (currAbsNodeAddr + 1);
		os << L"(" << currAbsNodeAddr << ",(" << p->value << "," << nextAbsNodeAddr << "))";
		if (!noNextNode) {
			os << ",";
		}
		p = p->next;
		currAbsNodeAddr++;
	}	// end while
	os << L"})";
#endif
	return os;
}

