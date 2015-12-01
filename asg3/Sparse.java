//Antony Robbins
//androbbi@ucsc.edu
//Assignment 3
import java.io.*;
import java.util.Scanner;
import java.lang.*;

class Sparse{
   public static void main(String[] args)throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;
      int i, len, lineNumber = 0;
	  int n = 0;
	  int a = 0;
	  int b = 0;
	  String key;
	  Matrix A = new Matrix(1); Matrix B = new Matrix(1);
	  int count = 1;
	  int row, col = 0;
	  double val = 0;
      
	  //Checks to see if there is less than 2 arguments
	  //If not, exit program
	  if(args.length != 2){
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
         len = token.length;

		 if( lineNumber <= 1) {
		    //Determines Row and Col
		    n = (int)Integer.parseInt(token[0]);
			//Determines number of elements in Matrix A
			a = (int)Integer.parseInt(token[1]);
			//Determines number of elements in Matrix B
			b = (int) Integer.parseInt(token[2]);
		    A = new Matrix(n);
		    B = new Matrix(n);
         }
		 else if (in.hasNext() && count <= a) {
		    row = (int)Integer.parseInt(token[0]);
		    col = (int)Integer.parseInt(token[1]);
			val = (double)Integer.parseInt(token[2]);
			A.changeEntry(row, col, val);
			count ++;
		 }
         // Parse the remaining tokens into B
		 else if(in.hasNext()) {
		    row = (int)Integer.parseInt(token[0]);
			col = (int)Integer.parseInt(token[1]);
			val = (double)Integer.parseInt(token[2]);
			B.changeEntry(row, col, val);
		 }
      }
	  // Now make these calculations
      out.printf("Matrix A has "+ A.getNNZ() +" non-zero entries:%n%s%n",A);
	  out.printf("Matrix B has "+ B.getNNZ() +" non-zero entries:%n%s%n",B);
	  Matrix scalarMult = A.scalarMult(1.5);
	  out.printf("Matrix Scalar has "+ scalarMult.getNNZ() +" non-zero entries:%n%s%n", scalarMult);
	  Matrix AplusB = A.add(B);
	  out.printf("Matrix AplusB has "+ AplusB.getNNZ() + " non-zero entries: %n%s%n", AplusB);
	  Matrix AplusA = A.add(A);
	  out.printf("Matrix AplusA has "+ AplusA.getNNZ() + " non-zero entries: %n%s%n", AplusA);
	  Matrix BminusA = B.sub(A);
	  out.printf("Matrix BminusA has "+ BminusA.getNNZ() + " non-zero entries: %n%s%n", BminusA);
	  Matrix AminusA = A.sub(A);
	  out.printf("Matrix AminusA has "+ AminusA.getNNZ() + " non-zero entries: %n%s%n", AminusA);
	  Matrix transpose = A.transpose();
	  out.printf("Matrix transpose has "+ transpose.getNNZ() +" non-zero entries:%n%s%n", transpose);
	  Matrix AtimesB = A.mult(B);
	  out.printf("Matrix AtimesB has "+ AtimesB.getNNZ() +" non-zero entries:%n%s%n", AtimesB);
	  Matrix Bsquared = B.mult(B);
	  out.printf("Matrix Bsquared has "+ Bsquared.getNNZ() +" non-zero entries:%n%s%n", Bsquared);
	  
	  

      in.close();
      out.close();
     
   }
}