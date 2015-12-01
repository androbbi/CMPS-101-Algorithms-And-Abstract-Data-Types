//Antony Robbins
//androbbi@ucsc.edu
//Assignment 1
import java.io.*;
import java.util.Scanner;

class Lex{
   public static void main(String[] args)throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;
      int i, n, lineNumber = 0;
	  String key;
      
	  //Checks to see if there is less than 2 arguments
	  //If not, exit program
	  if(args.length < 2){
         System.out.println("Usage: FileIO infile outfile");
		 System.err.println("Use 2 arguments");
         System.exit(1);
      }
	  
	  in = new Scanner(new File(args[0])); //Read in the file
	  out = new PrintWriter(new FileWriter(args[1])); //Output the file
	  
	  while( in.hasNextLine() ){
         lineNumber++;
         line = in.nextLine()+" ";    // add extra space so split works right
         token = line.split("\\s+");  // split line around white space
         n = token.length;
         /*out.println("Line "+lineNumber+" contains "+n+" token"+(n==1?"":"s")+":");
         for(i=0; i<n; i++){
            out.println(token[i]);
         }
         out.println();*/
      }
	  List input = new List();
	  for( i = 1; i < n; i++) {
	     key = token[i];
		 int j = i - 1;
		 while(j >= 0 && token[j].compareTo(key) > 0) {
		    token[j + 1] = token[j];
			j--;
		 }
		 token[j + 1] = key;
      }

      in.close();
      out.close();
     
   }
}