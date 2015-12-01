//Antony Robbins
//androbbi@ucsc.edu
//Assignment 5
//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT w/ DFS
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include "List.h"
#define UNDEF -1
#define NIL 0

// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;

// Constructors-Destructors ---------------------------------------------------

// newGraph() returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges.
Graph newGraph(int n);

// freeGraph() frees all dynamic memory associated with the
// Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------
// getOrder() and getSize() return the corresponding field values
int getOrder(Graph G);
int getSize(Graph G);

// getParent() will return the parent of vertex u in the Breadth-First tree created by BFS()
// or NIL if BFS() has not yet been called.
// Preconditions: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

// Manipulation procedures ----------------------------------------------------
// makeNull() deletes all edges of G, restoring it to its original (no edge) state.
// (This is called a null graph in graph theory literature).
// addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v,
// and v to the adjacency List of u. Your program is required to maintain these lists in sorted order by
// increasing vertex labels. 
//void makeNull(Graph G);

// addArc() inserts a new directed edge from u to v, i.e. v is added to the
// adjacency List of u (but not u to the adjacency List of v). Both addEdge() and addArc() have the
// precondition that their two int arguments must lie in the range 1 to getOrder(G).
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);


void DFS(Graph G, List S);

// Other Functions ------------------------------------------------------------

// printGraph() prints the adjacency list representation of G to the file pointed to by out. 
// The format of this representation should match the above examples, so all that is
// required by the client is a single call to printGraph().

// Creates a new graph that is the transpose of G
Graph transpose(Graph G);

// Creates a new graph that is a copy of G
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
#endif