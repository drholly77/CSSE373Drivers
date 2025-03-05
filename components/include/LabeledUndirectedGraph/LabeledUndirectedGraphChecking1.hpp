#pragma once
/*
	Checking Version of UnlabeledUndirectedGraph
	Author: Dr. Holly
*/

template <
	class UncheckedUnlabeledUndirectedGraph
>
class UnlabeledUndirectedGraphChecking1:
	public UncheckedUnlabeledUndirectedGraph
{
	typedef UncheckedUnlabeledUndirectedGraph UnlabeledUndirectedGraph;
public:

//-------------------------------------------------------------------

void addEdge(Integer v1, Integer v2)
{
	// assert that length > 0
	Integer maxVertices;
	maxVertices = UnlabeledUndirectedGraph::numberOfVertices();
	if (v1 < 1 || v1 > maxVertices) {
		OutputDebugString (L"Operation: addEdge\n");
		OutputDebugString (L"Assertion failed: v1 is in g.vertices\n");
		DebugBreak ();
	}	// end if 
	if (v2 < 1 || v2 > maxVertices) {
		OutputDebugString(L"Operation: addEdge\n");
		OutputDebugString(L"Assertion failed: v2 is in g.vertices\n");
		DebugBreak();
	}	// end if 
	if (UnlabeledUndirectedGraph::isEdge(v1, v2)) {
		OutputDebugString(L"Operation: addEdge\n");
		OutputDebugString(L"Assertion failed: {v1, v2} is not in g.edges\n");
		DebugBreak();
	}	// end if 

	UnlabeledUndirectedGraph::addEdge (v1, v2);
}	// addEdge

//-------------------------------------------------------------------

void removeEdge(Integer v1, Integer v2)
{
	// assert that length > 0
	Integer maxVertices;
	maxVertices = UnlabeledUndirectedGraph::numberOfVertices();
	if (v1 < 1 || v1 > maxVertices) {
		OutputDebugString(L"Operation: removeEdge\n");
		OutputDebugString(L"Assertion failed: v1 is in g.vertices\n");
		DebugBreak();
	}	// end if 
	if (v2 < 1 || v2 > maxVertices) {
		OutputDebugString(L"Operation: removeEdge\n");
		OutputDebugString(L"Assertion failed: v2 is in g.vertices\n");
		DebugBreak();
	}	// end if 
	if (!UnlabeledUndirectedGraph::isEdge(v1, v2)) {
		OutputDebugString(L"Operation: addEdge\n");
		OutputDebugString(L"Assertion failed: {v1, v2} is in g.edges\n");
		DebugBreak();
	} // end if

	UnlabeledUndirectedGraph::removeEdge(v1, v2);
}	// removeEdge

//-------------------------------------------------------------------

void removeAnyIncidentEdge(Integer v1, Integer& v2)
{
	// assert that length > 0
	Integer maxVertices;
	maxVertices = UnlabeledUndirectedGraph::numberOfVertices();
	if (v1 < 1 || v1 > maxVertices) {
		OutputDebugString(L"Operation: removeAnyIncidentEdge\n");
		OutputDebugString(L"Assertion failed: v1 is in g.vertices\n");
		DebugBreak();
	}	// end if 
	if (UnlabeledUndirectedGraph::degree(v1) == 0) {
		OutputDebugString(L"Operation: removeAnyIncidentEdge\n");
		OutputDebugString(L"Assertion failed: there exists v : integer such that ({v1, v} is in g.edges)\n");
		DebugBreak();
	}	// end if 

	UnlabeledUndirectedGraph::removeAnyIncidentEdge(v1, v2);
}	// removeAnyIncidentEdge

//-------------------------------------------------------------------

void removeAnyEdge(Integer& v1, Integer& v2)
{
	if (UnlabeledUndirectedGraph::numberOfEdges() == 0) {
		OutputDebugString(L"Operation: removeAnyEdge\n");
		OutputDebugString(L"Assertion failed: g.edges /= {}\n");
		DebugBreak();
	}	// end if 
	UnlabeledUndirectedGraph::removeAnyEdge(v1, v2);
}	// removeAnyEdge


};

