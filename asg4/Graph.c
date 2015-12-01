//Antony Robbins
//androbbi@ucsc.edu
//Assignment 4
//-----------------------------------------------------------------------------
// Graph.c
// Main file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// private GraphObj type
typedef struct GraphObj{
   int size;   // Number of edges
   int order;  // Number of vertices
   int source; // Label of the vertex that was most recently used
   List *adj;   // Array of Lists whose ith element contains the neighbors of vertex i
   char *color; // Array of chars whose ith element is the color w/g/b of vertex i
   int *parent; // Array of ints whose ith element is the parent of vertex i
   int *dist;   // Array of ints whose ith element is the distance from the most recent source to vertex i
} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph() returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges.
Graph newGraph(int n) {
   Graph G = malloc(sizeof(GraphObj));
   G->adj = calloc((n+1), sizeof(List));
   G->color = calloc((n+1), sizeof(char));
   G->parent = calloc((n+1), sizeof(int));
   G->dist = calloc((n+1), sizeof(int));
   for(int i = 1; i <= n; i++) {
      G->adj[i] = newList();
	  G->color[i] = 'w';
	  G->parent[i] = NIL;
	  G->dist[i] = INF;
   }
   G->size = 0;
   G->order = n;
   G->source = NIL;
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
   free((*pG)->dist);
   free(*pG);
   *pG = NULL;
}

// Access functions -----------------------------------------------------------
// getOrder() and getSize() return the corresponding field values
int getOrder(Graph G) {
   return G->order;
}
int getSize(Graph G) {
   return G->size;
}

// getSource() returns the source vertex most recently used in function
// BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G) {
   return G->source;
}

// getParent() will return the parent of vertex u in the Breadth-First tree created by BFS()
// or NIL if BFS() has not yet been called.
// Preconditions: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
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

// getDist() returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not 5 yet been called.
// Preconditions: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
   if( u < 1) {
      printf("Graph Error: calling getDist() with a vertex < 1\n");
      exit(1);
   }
   if( getOrder(G) < u) {
      printf("Graph Error: calling getDist() with a vertex > getOrder(G)\n");
      exit(1);
   }
   return G->dist[u];
   
}

// getPath() appends to the List L the vertices of a shortest path in G from
// source to u, or appends to L the value NIL if no such path exists. getPath() has the precondition
// getSource(G)!=NIL, so BFS() must be called before getPath().
// The path starts at Vertex x and goes to Vertex y
// Preconditions: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {
   if( u < 1) {
      printf("Graph Error: calling getDist() with a vertex < 1\n");
      exit(1);
   }
   if( getOrder(G) < u) {
      printf("Graph Error: calling getDist() with a vertex > getOrder(G)\n");
      exit(1);
   }
   if(getSource(G) == NIL) {
      printf("Graph Error: calling getPath() with a vertex == NIL, or BFS() has not been called\n");
      exit(1);
   }
   int x = getSource(G);
   int y;
   if(getParent(G, u) == NIL) append(L, NIL);
   else if(x == u) append(L, u);
   else {
      prepend(L, x);
	  moveTo(L, 0);
      y = getParent(G, u);
	  while( y != x && y != NIL) {
	     insertAfter(L, y);
		 y = getParent(G, y);
	     moveTo(L,0);   
	  }
      append(L, u);
   }
}
// Manipulation procedures ----------------------------------------------------

// makeNull() deletes all edges of G, restoring it to its original (no edge) state.
// (This is called a null graph in graph theory literature). 
void makeNull(Graph G) {
   for(int i = 1; i <= getOrder(G); i++) {
      clear(G->adj[i]);
   }
   G->size = 0;
   G->source = NIL;
}

// addArc() inserts a new directed edge from u to v, i.e. v is added to the
// adjacency List of u (but not u to the adjacency List of v). Both addEdge() and addArc() have the
// precondition that their two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v) {
   //preconditions
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

// BFS() runs the BFS algorithm on the Graph G with source s, setting the color,
// distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s) {
   for(int i = 1; i <= getOrder(G); i++) {
      if( i != s) {
         G->color[i] = 'w';
	     G->parent[i] = NIL;
	     G->dist[i] = INF;
	  } 
   }
   G->color[s] = 'g';
   G->parent[s] = NIL;
   G->dist[s] = 0; 
   G->source = s;
   List Q = newList();
   append(Q, s);
   while(length(Q) != 0) {
      // x = Dequeue(Q)
	  int x = front(Q);
	  deleteFront(Q);
	  // For all y elements in adj[x]
	  moveTo(G->adj[x], 0);
      while(getIndex(G->adj[x]) != -1) {
	     int y = getElement(G->adj[x]);
	     if(G->color[y] == 'w') {
		    G->color[y] = 'g';
			G->dist[y] = G->dist[x] + 1;
			G->parent[y] = x;
			append(Q, y);
         }
         moveNext(G->adj[x]);
      }
      G->color[x] = 'b';	  
   }
   freeList(&Q);
}   

// Other Functions ------------------------------------------------------------

// printGraph() prints the adjacency list representation of G to the file pointed to by out. 
// The format of this representation should match the above examples, so all that is
// required by the client is a single call to printGraph().
void printGraph(FILE* out, Graph G) {
   for(int i = 1; i <= getOrder(G); i++ ) {
      fprintf(out, "%d: ", i);
	  if(length(G->adj[i]) != 0) {
	     printList(out, G->adj[i]);
      }
	  fprintf(out, "\n");
   }
}