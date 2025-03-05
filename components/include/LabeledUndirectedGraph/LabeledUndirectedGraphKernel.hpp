#pragma once

/*
	UnlabeledUndirectedGraph kernel component with primary methods
*/

//-----------------------------------------------------------------------
// Template Class Specification
//-----------------------------------------------------------------------

class UnlabeledUndirectedGraphKernel

	/*!
		math subtype BARE_EDGE is finite set of integer
		exemplar e
		constraint
		| e | = 2

		math subtype EDGE is (
			endpoints: BARE_EDGE,
			label : T
		)

		math subtype UNDIRECTED_GRAPH_MODEL is (
			vertices: finite set of integer,
			edges : finite set of EDGE
		)
		exemplar g
		constraint
		there exists nv : integer such that
		(g.vertices = { v: integer where(1 <= v <= nv) (v) }) and
		for all e : EDGE where(e is in g.edges)
			(for all v : integer
				where(v is in e.endpoints)
				(v is in g.vertices)) and
			for all v1, v2, v3, v4 : integer, y1, y2 : T
				where(({ v1, v2 }, y1) is in g.edges and
					({ v3, v4), y2) is in g.edges)
		 ({v1, v2} = {v3, v4} implies y1 = y2)

		 type UndirectedGraph is modeled by UNDIRECTED_GRAPH_MODEL
		 exemplar self
		 initially ensures
			 self = ({},{})
		!*/
{
public: // UnlabeledUndirectedGraph Specific Operations

	virtual void setNumberOfVertices(Integer nv) = 0;
	//! updates self
	//! restores nv
	//! ensures: self.nodes = {n: integer where (1 <= n <= nv) (n)}  and
	//!          self.edges = {}

	virtual void addEdge(Integer v1, Integer v2) = 0;
	//! updates self
	//! restores v1, v2
	//! requires: v1 is in g.vertices and 
	//!           v2 is in g.vertices and
	//!           {v1, v2} is not in g.edges
	//! ensures: g.vertices = #g.vertices and
	//!          g.edges = #g.edges union {{v1, v2}}

	virtual void removeEdge(Integer v1, Integer v2) = 0;
	//! updates self
	//! restores v1, v2
	//! requires: v1 is in g.vertices and 
	//!           v2 is in g.vertices and
	//!           {v1, v2} is in g.edges
	//! ensures: g.vertices = #g.vertices and
	//!          {v1, v2} is in #g.edges and g.edges = #g.edges - {{v1, v2}}

	virtual void removeAnyIncidentEdge(Integer v1, Integer& v2) = 0;
	//! updates self
	//! restores v1
	//! replaces v2
	//! requires: v1 is in g.vertices and 
	//!           there exists v : integer such that ({v1, v} is in g.edges)
	//! ensures: g.vertices = #g.vertices and
	//!          {v1, v2} is in #g.edges and g.edges = #g.edges - {{v1, v2}}

	virtual void removeAnyEdge(Integer& v1, Integer& v2) = 0;
	//! updates self
	//! replaces v1, v2
	//! requires: g.edges /= {}
	//! ensures: g.vertices = #g.vertices and
	//!          {v1, v2} is in #g.edges and g.edges = #g.edges - {{v1, v2}}

	virtual Integer numberOfVertices() = 0;
	//! restores self
	//! ensures: numberOfVertices = |g.vertices|

	virtual Integer numberOfEdges() = 0;
	//! restores self
	//! ensures: numberOfEdges = |g.edges|

	virtual Integer degree(Integer v) = 0;
	//! updates self
	//! restores v
	//! ensures: degree = |{v2: integer where ({v, v2} is in g.edges) (v2)}|

	virtual Boolean isEdge(Integer v1, Integer v2) = 0;
	//! updates self
	//! restores v1
	//! restores v2
	//! ensures: isEdge = {v1, v2} is in g.edges
};
