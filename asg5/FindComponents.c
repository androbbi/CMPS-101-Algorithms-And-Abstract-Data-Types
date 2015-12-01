//Antony Robbins
//androbbi@ucsc.edu
//Assignment 5
//-----------------------------------------------------------------------------
// FindComponents.c
// A client to the class Graph.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 160
// Since our scc was being printed backwards, we 
// needed a work around
void printReverse(FILE* out, Graph G, List R){
   fprintf(out, " ");
   printList(out, R);
   clear(R);
}

int main(int argc, char * argv[]){
   int count=0;
   int u, v, index, sccNum;
   FILE *in, *out;
   char line[MAX_LEN];
   char* token;
   Graph G = NULL;
   Graph T = NULL;
   List S = newList(); // This list is our stack that determins the order of the vertices
   List R = newList();
   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   /* read each line of input file, then count and print tokens */
   // Assemble a graph object G using newGraph() and addArc()
   while(fgets(line, MAX_LEN, in) != NULL)  {
      count++;
	  // char *strtok(char *str, const char *delim) breaks string str into
	  // a series of tokens using the delimitrer delim. This function returns a pointer to the
	  // last token found in string. A null pointer is returned if there are no tokens left to retrieve.
      token = strtok(line, " \n");
	  
	  // int atoi(const char *str), This function returns the converted integral number as an int value.
	  // If no valid conversion could be performed, it returns zero.
	  // It converts char to int.
	  if(count == 1) {
	     // Takes in the first number as a token, sets a graph of that size
	     G = newGraph(atoi(token));
	  }
	  else {
	     // Here we want to read in both numbers
		 u = atoi(token);
		 token = strtok(NULL, " \n");
		 v = atoi(token);
		 if( u != 0 || v != 0) {
		       addArc(G, u, v);
	     }		   
         else if (u == 0 && v == 0) {
		       break;
         }			   
      } 
   }
   // Print the adjacency list representation of G to the output file
   printGraph(out, G);
   fprintf(out, "\n");
   
   // creating our Stack
   for(int i = 1; i <= getOrder(G); i++) {
      append(S, i);
   }
   
   // Run DFS on G and G-Transpose, processing the vertices in the second call
   // by decreasing finish times from the first call
   DFS(G, S);
   T = transpose(G);
   DFS(T, S);
   
   // Determine the strong components of G
   // Print the strong components of G to the output file in topologically sorted order.
   // Everytime a vertex has a NIL parent in the transpose of G, we have a SCC
   sccNum = 0;
   for(int i = 1; i <= getOrder(G); i++) {
      if(getParent(T, i) == NIL) sccNum++;
   }
   
   
   fprintf(out, "G contains %d strongly connected components:\n", sccNum);
   index = 1;
   moveTo(S, length(S) - 1 );
   while(getIndex(S) != -1 && index <= sccNum) {  
	  fprintf(out, "Component %d:", index);
	  while(getParent(T, getElement(S)) != NIL) {
		 prepend(R, getElement(S));
		 movePrev(S);
	  }
	  prepend(R, getElement(S));
	  printReverse(out, T, R);
	  movePrev(S);
	  index++;   
	  fprintf(out, "\n");
   }

   
   freeList(&S);
   freeList(&R);   
   freeGraph(&G);
   freeGraph(&T);   

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}
