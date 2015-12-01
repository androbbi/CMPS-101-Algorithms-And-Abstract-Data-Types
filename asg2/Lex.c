//Antony Robbins
//androbbi@ucsc.edu
//Assignment 2
//-----------------------------------------------------------------------------
// FileIO.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
   int n, count=0;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;
   freeList(&A);

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
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
      n = 0;
      token = strtok(line, " \n");
      tokenlist[0] = '\0';
      while( token!=NULL ){
         strcat(tokenlist, "   ");
         strcat(tokenlist, token);
         strcat(tokenlist, "\n");
         n++;
         token = strtok(NULL, " \n");
      }
      //fprintf(out, "line %d contains %d token%s: \n", count, n, n==1?"":"s");
      //fprintf(out, "%s\n", tokenlist);
   }
   List A = newList();
   //Insert Data into list through Insertion Sort
	Node tmp = L->first;
	key = token[i];
	while(tmp!=NULL){
		if(data < tmp->data){
			insertBefore(L, data);
			return;
		}
		tmp=tmp->next;
	}
	append(L, data);
	

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}