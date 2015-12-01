//Antony Robbins
//androbbi@ucsc.edu
//Assignment 5
//-----------------------------------------------------------------------------
// Graph.c
// Main file for Graph ADT w/ DFS
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// private GraphObj type
typedef struct GraphObj{
   int size;   // Number of edges
   int order;  // Number of vertices
   List *adj;   // Array of Lists whose ith element contains the neighbors of vertex i
   char *color; // Array of chars whose ith element is the color w/g/b of vertex i
   int *parent; // Array of ints whose ith element is the parent of vertex i
   int *discover;   // Array of ints whose ith element is the position discovered
   int *finish; // Array of ints whose ith element is the position finished
} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph() returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges.
Graph newGraph(int n) {
   Graph G = malloc(sizeof(GraphObj));
   G->adj = calloc((n+1), sizeof(List));
   G->color = calloc((n+1), sizeof(char));
   G->parent = calloc((n+1), sizeof(int));
   G->discover = calloc((n+1), sizeof(int));
   G->finish = calloc((n+1), sizeof(int));
   for(int i = 1; i <= n; i++) {
      G->adj[i] = newList();
	  G->color[i] = 'w';
	  G->parent[i] = NIL;
	  G->discover[i] = UNDEF;
	  G->finish[i] = UNDEF;
   }
   G->size = 0;
   G->order = n;
   return G;
}

// freeGraph() frees all dynamic memory associated with the
// Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {
   for(int i = 1; i <= getOrder(*pG); i++) {
      freeList(&((*pG)->adj[i]));
   }
   free((*pG)->adj);
   free((*pG)->color);
   free((*pG)->parent);
   free((*pG)->discover);
   free((*pG)->finish);
   free(*pG);
   *pG = NULL;
}

// Access functions -----------------------------------------------------------

// getOrder() and getSize() return the corresponding field values
int getOrder(Graph G) {
   if(G == NULL) {
      printf("Graph Error: calling getOrder() on a Null Graph\n");
      exit(1);
   }
   return G->order;
}
int getSize(Graph G) {
   if(G == NULL) {
      printf("Graph Error: calling getSize() on a Null Graph\n");
      exit(1);
   }
   return G->size;
}

// getParent() will return the parent of vertex u in the Breadth-First tree created by BFS()
// or NIL if BFS() has not yet been called.
// Preconditions: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
   if(G == NULL) {
      printf("Graph Error: calling getParent() on a Null Graph\n");
      exit(1);
   }
   if( u < 1) {
      printf("Graph Error: calling getParent() with a vertex < 0\n");
      exit(1);
   }
   if( getOrder(G) < u) {
      printf("Graph Error: calling getParent() with a vertex > getOrder(G)\n");
      exit(1);
   }
   return G->parent[u];
}

// getDiscover() returns the discovered time of the vertex
// Preconditions: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u) {
   if(G == NULL) {
      printf("Graph Error: calling getDiscover() on a Null Graph\n");
      exit(1);
   }
   if( u < 1) {
      printf("Graph Error: calling getDiscover() with a vertex < 0\n");
      exit(1);
   }
   if( getOrder(G) < u) {
      printf("Graph Error: calling getDiscover() with a vertex > getOrder(G)\n");
      exit(1);
   }
   return G->discover[u];
}

// getFinish() returns the finish time of the vertex
// Preconditions: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u) {
   if(G == NULL) {
      printf("Graph Error: calling getFinish() on a Null Graph\n");
      exit(1);
   }
   if( u < 1) {
      printf("Graph Error: calling getFinish() with a vertex < 0\n");
      exit(1);
   }
   if( getOrder(G) < u) {
      printf("Graph Error: calling getFinish() with a vertex > getOrder(G)\n");
      exit(1);
   }
   return G->finish[u];
}

// Manipulation procedures ----------------------------------------------------
/*
// makeNull() deletes all edges of G, restoring it to its original (no edge) state.
// (This is called a null graph in graph theory literature). 
void makeNull(Graph G) {
   for(int i = 1; i <= getOrder(G); i++) {
      clear(G->adj[i]);
   }
   G->size = 0;
   G->source = NIL;
} */

// addArc() inserts a new directed edge from u to v, i.e. v is added to the
// adjacency List of u (but not u to the adjacency List of v). Both addEdge() and addArc() have the
// precondition that their two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v) {
   //preconditions
   if(G == NULL) {
      printf("Graph Error: calling addArc() on a Null Graph\n");
      exit(1);
   }
   if(u < 1) {
      printf("Graph Error: calling addArc() with a vertex u < 1\n");
      exit(1);
   }
   if(getOrder(G) < u ) {
      printf("Graph Error: calling addArc() with a vertex u > getOrder(G)\n");
      exit(1);
   }
   if(v < 1) {
      printf("Graph Error: calling addArc() with a vertex v < 1\n");
      exit(1);
   }
   if(getOrder(G) < v ) {
      printf("Graph Error: calling addArc() with a vertex v > getOrder(G)\n");
      exit(1);
   }
   // If the list is not empty, place the vertex in the appropriate spot
   // Otherwise, just add it to the list
   if(length(G->adj[u]) != 0) {
      moveTo(G->adj[u], 0);
      // If V is less than the first vertex, add it to the front of the list
      if (v < front(G->adj[u])) {
	     prepend(G->adj[u], v);
		 G->size++;
      }
	  // If V is greater than the last vertex, add it at the end of the list
      else if (v > back(G->adj[u])) {
	     append(G->adj[u], v);
         G->size++;		 
	  }
	  // If neither case works, place the vertex at the appropriate position
      else {
	     while(getIndex(G->adj[u]) != -1 ) {
		    if(v < getElement(G->adj[u])) {
			   insertBefore(G->adj[u], v);
			   G->size++;
			   break;
			}
			moveNext(G->adj[u]);
		 }
	  }
   }   
   else {
      append(G->adj[u], v);
      G->size++;
   }
}

// addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v,
// and v to the adjacency List of u. Your program is required to maintain these lists in sorted order by
// increasing vertex labels.
void addEdge(Graph G, int u, int v) {
   if(G == NULL) {
      printf("Graph Error: calling addEdge() on a Null Graph\n");
      exit(1);
   }
   if(u < 1) {
      printf("Graph Error: calling addEdge() with a vertex u < q\n");
      exit(1);
   }
   if(getOrder(G) < u ) {
      printf("Graph Error: calling addEdge() with a vertex u > getOrder(G)\n");
      exit(1);
   }
   if(v < 1) {
      printf("Graph Error: calling addEdge() with a vertex v < 1\n");
      exit(1);
   }
   if(getOrder(G) < v ) {
      printf("Graph Error: calling addEdge() with a vertex v > getOrder(G)\n");
      exit(1);
   }
   addArc(G, v, u);
   addArc(G, u, v);
}

// x is the vertex position we are working on
// visit() is a helper function to DFS
void visit(int x, Graph G, List S, List stack, int *time) {
   G->color[x] = 'g';
   (*time)++;
   G->discover[x] = *time;
   moveTo(G->adj[x], 0);
   while(getIndex(G->adj[x]) != -1) {
	  if(G->color[getElement(G->adj[x])] == 'w') {
	     G->parent[getElement(G->adj[x])] = x;
		 visit(getElement(G->adj[x]), G, S, stack, time);
	  }
	  moveNext(G->adj[x]);
   }
   G->color[x] = 'b';
   (*time)++;
   G->finish[x] = *time;
   prepend(stack, x);
}

// DFS() runs the DFS algorithm on the Graph G with List S,
// List S will be our Stack
// Preconditions: getLength(S) == getOrder(G)
void DFS(Graph G, List S) {
   if(G == NULL) {
      printf("Graph Error: calling DFS() on a Null Graph\n");
      exit(1);
   }
   if(G == NULL){
      printf("Graph Error: calling DFS() with an empty Graph\n");
      exit(1);
   }
   if(length(S) != getOrder(G)) {
      printf("Graph Error: calling DFS() with a List Length not equal to the number of vertices\n");
      exit(1);
   }
   // Initialization of the vertices, setting color to White and parent to NIL
   for(int i = 1; i <= getOrder(G); i++) {
      G->color[i] = 'w';
	  G->parent[i] = NIL;
   }
   int time = 0;
   int curr;
   List stack = newList();
   //int j = 1;
   moveTo(S, 0);
   while(getIndex(S) != -1) {
      if(G->color[getElement(S)] == 'w') {
		 curr = getElement(S);
         visit(curr, G, S, stack, &time);
      }
      moveNext(S);
   }
   //This will be our Transpose Stack
   clear(S);
   moveTo(stack, 0);
   while(getIndex(stack) != -1) {
      append(S, getElement(stack));
      moveNext(stack);
   }
   freeList(&stack); 
}
  

// Other Functions ------------------------------------------------------------
// transpose() returns the transpose of the original graph G
// To find the transpose, we switch the directions that the vertices point to
// Therefore, we call addArc but with the vertices switched, to get the opposite direction
Graph transpose(Graph G) {
   if(G == NULL) {
      printf("Graph Error: calling transpose() on a Null Graph\n");
      exit(1);
   }
   Graph Transpose = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(Transpose); i++) {
      moveTo(G->adj[i], 0);
      while(getIndex(G->adj[i]) != -1) {
	     addArc(Transpose, getElement(G->adj[i]), i);
		 moveNext(G->adj[i]);
	  }
   }
   return Transpose;
}
// copyGraph() returns a copy of the original graph G
// We do this by making a new graph and assigning the 
// values graph G had
Graph copyGraph(Graph G) {
   if(G == NULL) {
      printf("Graph Error: calling copyGraph() on a Null Graph\n");
      exit(1);
   }
   Graph copy = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(copy); i++) {
      copy->color[i] = 'w';
	  copy->parent[i] = getParent(G, i);
	  copy->discover[i] = getDiscover(G, i);
	  copy->finish[i] = getFinish(G, i);
	  copy->size = getSize(G);
   
	  moveTo(G->adj[i], 0);
	  while(getIndex(G->adj[i]) != -1) {
	     append(copy->adj[i], getElement(G->adj[i]));
		 moveNext(G->adj[i]);
	  }
   }
   return(copy);
}

// printGraph() prints the adjacency list representation of G to the file pointed to by out. 
// The format of this representation should match the above examples, so all that is
// required by the client is a single call to printGraph().
void printGraph(FILE* out, Graph G) {
   if(G == NULL) {
      printf("Graph Error: calling printGraph() on a Null Graph\n");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); i++ ) {
      fprintf(out, "%d: ", i);
	  if(length(G->adj[i]) != 0) {
	     printList(out, G->adj[i]);
      }
	  fprintf(out, "\n");
   }
}




