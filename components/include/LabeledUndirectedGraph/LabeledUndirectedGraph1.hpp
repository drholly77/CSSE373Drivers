#pragma once
#include "LabeledUndirectedGraph/LabeledUndirectedGraphKernel.hpp"
#include "ChainPosition/ChainPosition.hpp"

/*
	Realization of UnlabeledUndirectedGraph using ChainPosition
	Author: Dr. Holly
*/


//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

template <class T>
class LabeledUndirectedGraph1 : public StdOps<LabeledUndirectedGraph1<T>>, public LabeledUndirectedGraphKernel
{
public: // Standard Operations
	LabeledUndirectedGraph1 ();
	LabeledUndirectedGraph1(const LabeledUndirectedGraph1& s) = delete;
	~LabeledUndirectedGraph1 ();
	void clear (void);
	void transferFrom (LabeledUndirectedGraph1& source);
	LabeledUndirectedGraph1& operator = (LabeledUndirectedGraph1& rhs);

	// LabeledUndirectedGraph1 Specific Operations
	void setNumberOfVertices (Integer nv);
	void addEdge (Integer v1, Integer v2);
	void removeEdge (Integer v1, Integer v2);
	void removeAnyIncidentEdge (Integer v1, Integer& v2);
	void removeAnyEdge (Integer& v1, Integer& v2);
	Integer numberOfVertices ();
	Integer numberOfEdges ();
	Integer degree (Integer v);
	Boolean isEdge (Integer v1, Integer v2);

	friend wostream& operator << (wostream& os, LabeledUndirectedGraph1& g);
		//! updates os
		//! restores g

private: // Representation
	class GraphTupleRecord {
	public:
		Integer v1;
		Integer v2;

		GraphTupleRecord() {}
		GraphTupleRecord(Integer v1, Integer v2)
		{
			self.v1 = v1;
			self.v2 = v2;
		} // GraphTupleRecord
		~GraphTupleRecord() {}

		void clear(void)
		{
			v1.clear();
			v2.clear();
		} // clear

		GraphTupleRecord& operator = (GraphTupleRecord& rhs)
		{
			self.v1 = rhs.v1;
			self.v2 = rhs.v2;
			return *this;
		} // operator =

		void transferFrom(GraphTupleRecord& source)
		{
			v1.transferFrom(source.v1);
			v2.transferFrom(source.v2);
		}

		Boolean areEqual(Integer v1, Integer v2)
		{
			return ((self.v1 == v1) && (self.v2 == v2)) || ((self.v1 == v2) && (self.v2 == v1));
		}

		Boolean isIncidentWithVertex(Integer v)
		{
			return (self.v1 == v) || (self.v2 == v);
		}

		Integer getOtherVertex(Integer incidentV)
			// requires: self.v1 = incidentV || self.v2 = incidentV
			// ensures: (incidentV = self.v1 && getOtherVertex = self.v2) ||
			//          (incidentV = self.v2 && getOtherVertex = self.v1)
		{
			if (self.v1 == incidentV) {
				return self.v2;
			}
			else {
				return self.v1;
			} // end if
		}

		friend wostream& operator <<(wostream& os, GraphTupleRecord& r)
		{
			os << L"(" << r.v1 << L"," << r.v1 << L")";
			return os;
		}
	};

	typedef ChainPosition1 <GraphTupleRecord> ChainPositionOfGraphTuple;

	ChainPositionOfGraphTuple chain;
	Integer vertexCount;
	Integer edgeCount;
};


//-----------------------------------------------------------------------
// Member Function Implementations
//-----------------------------------------------------------------------



//-----------------------------------------------------------------------
// Exported Operations
//-----------------------------------------------------------------------

LabeledUndirectedGraph1::LabeledUndirectedGraph1()
{
	ChainPositionOfGraphTuple smartPosition;
	GraphTupleRecord label;

	smartPosition.labelNew(label);
	chain.transferFrom(smartPosition);
}	// LabeledUndirectedGraph1

//-----------------------------------------------------------------------


LabeledUndirectedGraph1::~LabeledUndirectedGraph1()
{
}	// ~LabeledUndirectedGraph1

//-----------------------------------------------------------------------


void LabeledUndirectedGraph1::clear(void)
{
	ChainPositionOfGraphTuple smartPosition;
	GraphTupleRecord label;

	chain.clear();
	smartPosition.labelNew(label);
	chain.transferFrom(smartPosition);
	vertexCount = 0;
	edgeCount = 0;
}	// clear

//-----------------------------------------------------------------------


void LabeledUndirectedGraph1::transferFrom(LabeledUndirectedGraph1& source)
{
	chain.transferFrom(source.chain);
	vertexCount.transferFrom(source.vertexCount);
	edgeCount.transferFrom(source.edgeCount);
} // transferFrom

//-----------------------------------------------------------------------


LabeledUndirectedGraph1& 
LabeledUndirectedGraph1::operator = (LabeledUndirectedGraph1& rhs)
{
	ChainPositionOfGraphTuple newPos, oldPos, current;
	GraphTupleRecord x;

	current.labelNew(x);
	chain = current;

	oldPos = rhs.chain;
	oldPos.applyTarget();
	while (!oldPos.isZero()) {
		x = oldPos.label();
		newPos.labelNew(x);
		current.swapWithTarget(newPos);
		current.applyTarget();
		oldPos.applyTarget();
	} // end while
	vertexCount = rhs.vertexCount;
	edgeCount = rhs.edgeCount;

	return *this;
} // operator =

//-----------------------------------------------------------------------


void LabeledUndirectedGraph1::setNumberOfVertices(Integer nv)
{
	vertexCount = nv;
} // setNumberOfVertices


void LabeledUndirectedGraph1::addEdge(Integer v1, Integer v2)
{
	GraphTupleRecord newTuple(v1, v2);
	ChainPositionOfGraphTuple newPosition;
	ChainPositionOfGraphTuple firstPosition;

	chain.swapWithTarget(firstPosition);

	newPosition.labelNew(newTuple);
	newPosition.swapWithTarget(firstPosition);
	chain.swapWithTarget(newPosition);

	edgeCount++;
}	// add

//-----------------------------------------------------------------------


void LabeledUndirectedGraph1::removeEdge(Integer v1, Integer v2)
{
	ChainPositionOfGraphTuple trailingPosition;
	ChainPositionOfGraphTuple currentPosition;
	GraphTupleRecord existingPair;

	trailingPosition = chain;
	currentPosition = trailingPosition;
	currentPosition.applyTarget();

	while (!currentPosition.label().areEqual(v1, v2)) {
		trailingPosition = currentPosition;
		currentPosition.applyTarget();
	}  // end while
	currentPosition.replaceLabel(existingPair);

	currentPosition.applyTarget();
	trailingPosition.swapWithTarget(currentPosition);

	edgeCount--;
}	// remove

//-----------------------------------------------------------------------

void LabeledUndirectedGraph1::removeAnyIncidentEdge(Integer v1, Integer& v2)
{
	ChainPositionOfGraphTuple trailingPosition;
	ChainPositionOfGraphTuple currentPosition;
	GraphTupleRecord existingPair;

	trailingPosition = chain;
	currentPosition = trailingPosition;
	currentPosition.applyTarget();

	while (!currentPosition.label().isIncidentWithVertex(v1)) {
		trailingPosition = currentPosition;
		currentPosition.applyTarget();
	}  // end while
	currentPosition.replaceLabel(existingPair);

	currentPosition.applyTarget();
	trailingPosition.swapWithTarget(currentPosition);
	v2 = existingPair.getOtherVertex(v1);

	edgeCount--;
}	// removeAnyIncidentEdge

//-----------------------------------------------------------------------


void LabeledUndirectedGraph1::removeAnyEdge(Integer& v1, Integer& v2)
{
	ChainPositionOfGraphTuple position;
	GraphTupleRecord existingPair;

	position = chain;
	position.applyTarget();

	position.replaceLabel(existingPair);
	position.applyTarget();
	chain.swapWithTarget(position);

	v1.transferFrom(existingPair.v1);
	v2.transferFrom(existingPair.v2);

	edgeCount--;
}	// removeAnyEdge

//-----------------------------------------------------------------------


Integer LabeledUndirectedGraph1::numberOfVertices(void)
{
	return vertexCount;
}	// numberOfVertices

//-----------------------------------------------------------------------

Integer LabeledUndirectedGraph1::numberOfEdges(void)
{
	return edgeCount;
}	// numberOfEdges

//-----------------------------------------------------------------------

Integer LabeledUndirectedGraph1::degree(Integer v)
{
	ChainPositionOfGraphTuple position;
	Integer degreeCount;

	position = chain;
	position.applyTarget();

	while (!position.isZero()) {
		if (position.label().isIncidentWithVertex(v)) {
			degreeCount++;
		}
		position.applyTarget();
	}	// end while

	return degreeCount;
} // degree

//-----------------------------------------------------------------------

Boolean LabeledUndirectedGraph1::isEdge(Integer v1, Integer v2) {
	ChainPositionOfGraphTuple position;
	Integer degreeCount;

	position = chain;
	position.applyTarget();

	while (!position.isZero() && !position.label().areEqual(v1, v2)) {
		position.applyTarget();
	}	// end while
	return !position.isZero();
} // isEdge

//-----------------------------------------------------------------------

wostream& operator<<(wostream& os, LabeledUndirectedGraph1& g)
{
	LabeledUndirectedGraph1 temp;

	os << L"({";
	for (int k = 1, z = g.numberOfVertices(), lastItem = z - 1; k <= z; k++) {
		os << k;		
		if (k <= lastItem) {
			os << L",";
		} // end if
	} // end for
	os << L"},{";

	temp.setNumberOfVertices(g.numberOfVertices());
	while (g.numberOfEdges() > 0) {
		Integer v1, v2;

		g.removeAnyEdge(v1, v2);
		os << L"{" << ((v1 < v2) ? v1 : v2) << L"," << ((v1 < v2) ? v2 : v1) << L"}";
		if(g.numberOfEdges() > 0) {
			os << L",";
		} // end if
		temp.addEdge(v1, v2);
	}	// end for
	os << L"})";
	g.transferFrom(temp);

	return os;
} // operator<<


