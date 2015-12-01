//Antony Robbins
//androbbi@ucsc.edu
//Assignment 4
//-----------------------------------------------------------------------------
// FindPath.c
// A client to the class Graph.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
   int count=0;
   //int check = 0;
   int u, v;
   FILE *in, *out;
   char line[MAX_LEN];
   char* token;
   Graph G;
   List path = newList();

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
		       addEdge(G, u, v);
	     }		   
         else if (u == 0 && v == 0) {
		       //check = 1;
         }			   
      } 
   }
   printGraph(out, G);
   

   while( fgets(line, MAX_LEN, in) != NULL)  {
	  token = strtok(line, " \n");
      u = atoi(token);
      token = strtok(NULL, " \n");
	  v = atoi(token);
	  if( u != NIL) {
		 BFS(G, u);
	     clear(path);
		 getPath(path, G, v);
		 if(u != NIL ) {
		    fprintf(out, "The distance from %d to %d is %d\n", getSource(G), v, getDist(G, v));
			fprintf(out, "A shortest %d-%d path is: ", getSource(G), v);
			printList(out, path);
			fprintf(out, "\n");
		 }
	     else {
			fprintf(out, "There is no %d-%d path", getSource(G), v);
			fprintf(out, "\n");
	     }
      }
   }
	  
   freeGraph(&G);	
   freeList(&path);

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}