//Antony Robbins
//androbbi@ucsc.edu
//Assignment 3
import java.io.*;
import java.util.Scanner;

class MatrixTest {
  public static void main (String args[]) {
      int matSize = 4;
	  int num = 2;
	  int odd = 1;
	  double scalar = 5;
	  Matrix M = new Matrix(matSize);
	  
	  for(int i = 1; i < matSize; i++) {
	     for (int j = 1; j < matSize; j++) {
		    M.changeEntry(i, j, num);
			num++;
		 }
	  }
	  System.out.printf("Matrix M has "+ M.getNNZ() +" non-zero entries:%n%s%n",M);
	  // Output
	  /*Matrix M has 9 non-zero entries:
        1: (1, 2.0) (2, 3.0) (3, 4.0)
        2: (1, 5.0) (2, 6.0) (3, 7.0)
        3: (1, 8.0) (2, 9.0) (3, 10.0)
      */
	  
	  Matrix A = new Matrix(matSize);
	  for(int i = 1; i < matSize; i++) {
	     for (int j = 1; j < matSize; j++) {
		    A.changeEntry(i, j, odd);
			odd+=2;
		 }
	  }
	  System.out.printf("Matrix A has "+ A.getNNZ() +" non-zero entries:%n%s%n",A);
      // Output
	  /*Matrix A has 9 non-zero entries:
	    1: (1, 1.0) (2, 3.0) (3, 5.0)
        2: (1, 7.0) (2, 9.0) (3, 11.0)
        3: (1, 13.0) (2, 15.0) (3, 17.0)
      */
	  Matrix copy = M.copy();
	  System.out.printf("Matrix Copy has "+ copy.getNNZ() +" non-zero entries:%n%s%n", copy);
	  Matrix add = M.add(A);
	  System.out.printf("Matrix Add has "+ add.getNNZ() +" non-zero entries:%n%s%n", add);
	  Matrix sub = M.sub(A);
	  System.out.printf("Matrix Sub has "+ sub.getNNZ() +" non-zero entries:%n%s%n", sub);
		
      Matrix mult = M.mult(A);
	  System.out.printf("Matrix Mult has "+ mult.getNNZ() +" non-zero entries:%n%s%n", mult);
		
	  Matrix scalarMult = A.scalarMult(scalar);
	  System.out.printf("Matrix Scalar has "+ scalarMult.getNNZ() +" non-zero entries:%n%s%n", scalarMult);
	  
	  Matrix transpose = M.transpose();
	  System.out.printf("Matrix transpose has "+ transpose.getNNZ() +" non-zero entries:%n%s%n", transpose);
  }
  
}