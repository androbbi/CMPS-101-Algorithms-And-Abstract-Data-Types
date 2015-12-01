// Graph.c
// Implementation file for Graph ADT
// Taylor Stratton
// tjstratt

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj{
  List* vertex;
  int* color;
  int* parent;
  int* dist;
  int order;
  int size;
  int source;
} GraphObj;

Graph newGraph(int n){
  Graph G;
  G = malloc(sizeof(GraphObj));
  G->color = (int*)malloc(sizeof(int) * n+1);
  G->parent = (int*)malloc(sizeof(int) * n+1);
  G->dist = (int*)malloc(sizeof(int) * n+1);
  G->vertex = (List*)malloc(sizeof(List) * n+1);
  G->order = n;
  G->size = 0;
  G->source = NIL;
  for(int i=1; i<=n; i++){
    G->color[i] = 0;
  }
  for(int i=1; i<=n; i++){
    G->parent[i] = NIL;
  }
  for(int i=1; i<=n; i++){
    G->dist[i] = INF;
  } 
  for(int i=1; i<=n; i++){
    G->vertex[i] = newList();
  }
  return(G);
}
void freeGraph(Graph* pG){
  if(pG!=NULL && *pG!=NULL){
    free((*pG)->color);
    (*pG)->color = NULL;
    free((*pG)->parent);
    (*pG)->parent = NULL;
    free((*pG)->dist);
    (*pG)->dist = NULL;
    for(int i=1; i<=getOrder(*pG); i++){
      freeList(&(*pG)->vertex[i]);
    }
    free((*pG)->vertex);
    (*pG)->vertex = NULL;
    free(*pG);
    *pG = NULL;
  }
}

int getOrder(Graph G){
  if(G==NULL){
    printf("Graph Error: calling getOrder() on NULL Graph reference\n");
    exit(1);
  }
  return(G->order);
}
int getSize(Graph G){
  if(G==NULL){
    printf("Graph Error: calling getSize() on NULL Graph reference\n");
    exit(1);
  }
  return(G->size);
}
int getSource(Graph G){
  if(G==NULL){
    printf("Graph Error: calling getSource() on NULL Graph reference\n");
    exit(1);
  }
  return(G->source);
}
int getParent(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: calling getParent() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getParent() with vertex out-of-bounds\n");
    exit(1);
  }
  return(G->parent[u]);
}
int getDist(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: calling getDist() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getDist() with vertex out-of-bounds\n");
    exit(1);
  }
  return(G->dist[u]);
}
void getPath(List L, Graph G, int u){
  if(G==NULL){
    printf("Graph Error: calling getPath() on NULL Graph reference\n");
    exit(1);
  }
  if(1>u || u>getOrder(G)){
    printf("Graph Error: calling getPath() with vertex out-of-bounds\n");
    exit(1);
  }
  if(getSource(G)==NIL){
    printf("Graph Error: calling getPath() on Graph before BFS()\n");
    exit(1);
  }
  if(G->color[u] == 0){
    append(L, NIL);
    return;
  }
  append(L, u);
  int parent = G->parent[u];
  while(parent != NIL){
    prepend(L, parent);
    parent = G->parent[parent];
  }
}

void makeNull(Graph G){
  if(G==NULL){
    printf("Graph Error: calling makeNull() on NULL Graph reference\n");
    exit(1);
  }
  for(int i=1; i<=getOrder(G); i++){
    clear(G->vertex[i]);
    G->color[i] = 0;
    G->parent[i] = NIL;
    G->dist[i] = INF;
  }
  G->size = 0;
}
void addEdge(Graph G, int u, int v){
  if(G==NULL){
    printf("Graph Error: calling addEdge() on NULL Graph reference\n");
    exit(1);
  }
  moveTo(G->vertex[u], 0);
  moveTo(G->vertex[v], 0);
  while(getIndex(G->vertex[u]) != -1){
    if(v > getElement(G->vertex[u])){
      moveNext(G->vertex[u]);
      continue;
    }else if(v < getElement(G->vertex[u])){
      insertBefore(G->vertex[u], v);
	  moveNext(G->vertex[u]);
      break;
    }else{
      break;
    }
  }
  if(getIndex(G->vertex[u]) == -1){
    append(G->vertex[u], v);
  }
  while(getIndex(G->vertex[v]) != -1){
    if(u > getElement(G->vertex[v])){
      moveNext(G->vertex[v]);
      continue;
    }else if(u < getElement(G->vertex[v])){
      insertBefore(G->vertex[v], u);
      break;
    }else{
      break;
    }
  }
  if(getIndex(G->vertex[v]) == -1){
    append(G->vertex[v], u);
  }
}
void addArc(Graph G, int u, int v){
  if(G==NULL){
    printf("Graph Error: calling addArc() on NULL Graph reference\n");
    exit(1);
  }
  moveTo(G->vertex[u], 0);
  while(getIndex(G->vertex[u]) != -1){
    if(v > getElement(G->vertex[u])){
      moveNext(G->vertex[u]);
      continue;
    }else if(v < getElement(G->vertex[u])){
      insertBefore(G->vertex[u], v);
      break;
    }else{
      break;
    }
  }
  if(getIndex(G->vertex[u]) == -1){
    append(G->vertex[u], v);
  }
}
void BFS(Graph G, int s){
  if(G==NULL){
    printf("Graph Error: calling BFS() on NULL Graph reference\n");
    exit(1);
  }
  if(1>s || s>G->order){
    printf("Graph Error: calling BFS() with source vertex out-of-bounds\n");
    exit(1);
  }
  for(int i=1; i<=getOrder(G); i++){
    if(i == s){
      continue;
    }
    G->color[i] = 0;
    G->dist[i] = INF;
    G->parent[i] = NIL;
  }
  G->color[s] = 1;
  G->dist[s] = 0;
  G->parent[s] = NIL;
  List Q = newList();
  append(Q, s);
  while(length(Q) != 0){
    int x = front(Q);
    deleteFront(Q);
    moveTo(G->vertex[x], 0);
    while(getIndex(G->vertex[x]) != -1){
      int y = getElement(G->vertex[x]);
      if(G->color[y] == 0){
	G->color[y] = 1;
	G->dist[y] = G->dist[x]+1;
	G->parent[y] = x;
	append(Q, y);
      }
    }
    G->color[x] = 2;
  }
  G->source = s;
}
void printGraph(FILE* out, Graph G){
	if ( G == NULL ) {
		printf("Graph Error: calling printGraph() on NULL GraphRef\n");
		exit(1);
	}
	
	int i, temp;
	for ( i = 1; i <= getOrder(G); ++i ) {
		fprintf(out, "%d:", i);
		if ( length(G->vertex[i]) != 0 ) {
			moveTo(G->vertex[i], 0);
			while ( getIndex(G->vertex[i]) != -1 ) {
				temp = getElement(G->vertex[i]);
				moveNext(G->vertex[i]);
				fprintf(out, " %d", temp);
			}
		}
		fprintf(out, "\n");
	}
}
