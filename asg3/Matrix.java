//Antony Robbins
//androbbi@ucsc.edu
//Assignment 3
class Matrix {
   private class Entry{
      //Fields
      int col; // Column location (n x n = row x col)
	  double val; // Value stored
      //Constructor
      Entry(int col, double val) {
	     this.col = col;
	     this.val = val;
	  }
      public String toString() {
	     return String.valueOf("(" + this.col + ", " + this.val + ")");   
	  }
	  public boolean equals(Object x){
	     boolean flag = false;
		 Entry entry = (Entry)x;
	     if(this.col == entry.col && this.val == entry.val)
	        flag = true;
	     return flag;
	  }
   
   }
   //Fields
	private int NNZ;
	private int matSize; // This is the value nxn
    private List[] matArray;
   // Constructor
   // Makes a new n x n zero Matrix. pre: n>=1
   // Place Entry's into Matrix through the Sparse class
   Matrix(int n) {
      if(n < 1) throw new RuntimeException("Matrix Error: Matrix() called with n < 1");
      matArray = new List[n];
	  //We place our Lists in matArray[1] to matArray[n-1]
	  for(int i = 1; i < n; i++){
	     List row = new List();
	     matArray[i] = row; 
	  }
	  NNZ = 0;
	  matSize = n;
   }	  
	  
   // Access functions 
   // Returns n, the number of rows and columns of this Matrix
   int getSize() {
      return matSize;
   }
   
   // Returns the number of non-zero entries in this Matrix
   int getNNZ() {
      return NNZ;
   }
   
   // overrides Object's equals() method
   public boolean equals(Object x) {
      boolean flag = false;
	  int i = 0;
	  Matrix matEquals = (Matrix)x;
	  List listA;
	  List listB;
	  if(this.getSize() == matEquals.getSize() && this.getNNZ() == matEquals.getNNZ()) {
	     flag = true;
	  }
	  listA = matArray[i];
	  listB = matEquals.matArray[i];
	  while(listA != null && i < this.getSize()) {
		 flag = listA.equals(listB);
		 i++;
	  }
	  return flag;
   }
   
   // Manipulation procedures
   // sets this Matrix to the zero state
   void makeZero() {
      for(int i = 1; i < matSize; i++) {
	     matArray[i].clear();
	  }
	  NNZ = 0;
   }
   
   // returns a new Matrix having the same entries as this Matrix 
   Matrix copy() {
      Matrix matCopy = new Matrix(matSize);
      double newVal = 0;
	  int newRow = 0;
	  int newCol = 0;
	  matCopy.NNZ = 0;
	  // Go over the rows in a loop of the matrix you want to copy(input matrix)
	  // i is the row position for matArray[i]
	  for(int i = 1; i < matSize; i++) {
	     matArray[i].moveTo(0);
         while((!(matArray[i].getIndex() == -1))) {
            newVal = ((Entry)matArray[i].getElement()).val;
			newCol = ((Entry)matArray[i].getElement()).col;
			newRow = i;
			matCopy.changeEntry(newRow, newCol, newVal);
			matArray[i].moveNext();
		 }
	  }
	  return matCopy;
   }
   
   // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x) {
	  //Preconditions
	  if(j > getSize())
	     throw new RuntimeException("Matrix Error: changeEntry() called with j < getSize()");
	  if(j < 1)
	     throw new RuntimeException("Matrix Error: changeEntry() called with j > 1");
	  if(i > getSize())
	     throw new RuntimeException("Matrix Error: changeEntry() called with i > getSize()");
	  if(i < 1)
	     throw new RuntimeException("Matrix Error: changeEntry() called with i > 1");
	  
	  Entry matElement = new Entry(j, x);
	  // If the List at matArray position i is empty, append matElement
	  if(matArray[i].length() == 0) {
	     if(x!= 0){
	        matArray[i].append(matElement);
		    NNZ++;
	     }
      }
      // If the List at matArray position i is not empty
	  // Move cursor to List's front node
	  else {
	     matArray[i].moveTo(0);
		 // While the List index is not -1 and the cursor's col position is < j
		 // move through the list
		 while((!(matArray[i].getIndex() == -1)) && ((Entry)matArray[i].getElement()).col < j) {
		    matArray[i].moveNext();
		 }
		 // If we moved off of the list from previous while loop
		 if(matArray[i].getIndex() == -1) {
		    if(x!=0) {
			   matArray[i].append(matElement);
			   NNZ++;
		    }
         }
		 // When .col is > j
		 else {
		    // If .col == j and is a Non Zero number, replace the value
		    if(((Entry)matArray[i].getElement()).col == j) {
			   if(x != 0) {
			      ((Entry)matArray[i].getElement()).val = x;
               }
			   // If x = 0, delete the element from the List
			   else {
			      matArray[i].delete();
				  NNZ--;
               }
            }
			// If .col > j, place the element before the current cursor
			else if(((Entry)matArray[i].getElement()).col > j) {
			   if(x != 0) {
			      matArray[i].insertBefore(matElement);
				  NNZ++;
			   }
			}
         }
      }		 
   }

   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x) {
      Matrix matScalar = new Matrix(matSize);
      double newVal = 0;
	  int newRow = 0;
	  int newCol = 0;
	  matScalar.NNZ = 0;
	  // Go over the rows in a loop of the matrix you want to multiply by a scalar
	  for(int i = 1; i < matSize; i++) {
	     matArray[i].moveTo(0);
         while((!(matArray[i].getIndex() == -1))) {
            newVal = ((Entry)matArray[i].getElement()).val * x;
			newCol = ((Entry)matArray[i].getElement()).col;
			newRow = i;
			matScalar.changeEntry(newRow, newCol, newVal);
			matArray[i].moveNext();
		 }
	  }
	  return matScalar;
   }
   
   // returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M) {
      if(getSize() != M.getSize())
	     throw new RuntimeException("Matrix Error: add() called with incompatible Row x Col length");
	  Matrix newM = M.copy();
      Matrix sumMat = new Matrix(matSize);
	  int newRow = 0;
	  int newCol = 0;
	  double newVal = 0;
	  Entry oldEntry;
	  Entry newEntry;
	  List A; List B;
	  if( this == M ) {
		 return M.scalarMult(2);
      }
	  
	  for(int i = 1; i < matSize; i++) {
	     // If Matrix B is empty, just append Matrix A's list
	     if(newM.matArray[i].length() == 0 && matArray[i].length() != 0) {
		    matArray[i].moveTo(0);
		 	while(matArray[i].getIndex() != -1) {
			   oldEntry = (Entry)matArray[i].getElement();
			   newEntry = new Entry(oldEntry.col, oldEntry.val);
			   sumMat.matArray[i].append(newEntry);
			   matArray[i].moveNext();
			   sumMat.NNZ++;
		 	}
         }	
		 // If Matrix A is empty, just append Matrix B's list
		 else if(matArray[i].length() == 0 && newM.matArray[i].length() != 0) {
	        newM.matArray[i].moveTo(0);
			while(newM.matArray[i].getIndex() != -1) {
			   oldEntry = (Entry)newM.matArray[i].getElement();
			   newEntry = new Entry(oldEntry.col, oldEntry.val);
			   sumMat.matArray[i].append(newEntry);
			   newM.matArray[i].moveNext();
			   sumMat.NNZ++;
			}
		 }
		 // When neither Matrix A or B are empty
		 A = matArray[i]; B = newM.matArray[i];
		 A.moveTo(0); B.moveTo(0);
		 for (int j = 1; j <getSize(); j++) {
		    // Since we fell off of list A, append from List B
			if(A.getIndex() == -1 && B.getIndex() == -1)
			   break;
			if(A.getIndex() == -1) {
			   newCol = ((Entry)B.getElement()).col;
			   newVal = ((Entry)B.getElement()).val;
			   sumMat.changeEntry(i, newCol,  newVal);
			   B.moveNext();
			}
			// Since we fell off of list B, append from List A
			else if(B.getIndex() == -1) {
			   newCol = ((Entry)A.getElement()).col;
			   newVal = ((Entry)A.getElement()).val;
			   sumMat.changeEntry(i, newCol,  newVal);
			   A.moveNext();
			}
			// We are still on both lists
			else{	   
	           A.moveTo(0); B.moveTo(0);
               if((!(A.getIndex() == -1)) && (!(B.getIndex() == -1))) {
	              //Case 1: If A.col == B.col, newM = A.val + B.val, append in list then increment through both lists
	              if(((Entry)A.getElement()).col == ((Entry)B.getElement()).col) {
		             newCol = ((Entry)A.getElement()).col;
		             newVal = ((Entry)A.getElement()).val + ((Entry)A.getElement()). val;
			         //Entry index = new Entry(newCol, newM);
			         //if (index.val != 0) R.append(index);
			         sumMat.changeEntry(i, j, newVal);
			         A.moveNext(); B.moveNext();
		          }
		          //Case 2: If A.col < B.col, increment A.col
		          else if(((Entry)A.getElement()).col < ((Entry)B.getElement()).col) {
		             newCol = ((Entry)A.getElement()).col;
		             newVal= ((Entry)A.getElement()).val;
			         //Entry index = new Entry(newCol, newM);
		             //R.append(index);
			         sumMat.changeEntry(i, newCol, newVal);
			         A.moveNext();
		          }
		          //Case 3: If A.col > B.col, increment B.col
		          else{
		             newCol = ((Entry)B.getElement()).col;
		             newVal = ((Entry)B.getElement()).val;
			         sumMat.changeEntry(i, newCol, newVal);
			         //Entry index = new Entry(newCol, newM);
		             //R.append(index);		 
		             B.moveNext();
		          } 
	           }
			}
		 }
	  }
	  return sumMat;
   } 

   // returns a new Matrix that is the difference of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix sub(Matrix M) {
      if(getSize() != M.getSize())
	     throw new RuntimeException("Matrix Error: sub() called with incompatible Row x Col length");
      Matrix subMat = new Matrix(matSize);
	  if( this == M ) {
		 return subMat;
      } 
	  Matrix negM = new Matrix(matSize);
	  Matrix newM = M.copy();
	  negM = newM.scalarMult(-1);
	  subMat = this.add(negM);
	  return subMat;
		 
   }
	
   // returns a new Matrix that is the transpose of this Matrix
   // Essentially, take the entries from old Matrix, and place it
   // in new matrix in the format changeEntry(newCol, newRow, newVal)
   // The intial Matrix was made in the format (row, col, val)
   Matrix transpose() {
      Matrix matTranspose = new Matrix(matSize);
      double newVal = 0;
	  int newRow = 0;
	  int newCol = 0;
	  matTranspose.NNZ = 0;
	  // Go over the rows in a loop of the matrix you want to transpose(input matrix)
	  // i is the row position for matArray[i]
	  // i is the col position for matTranspose.matArray[i]
	  for(int i = 1; i < matSize; i++) {
	     matArray[i].moveTo(0);
         while((!(matArray[i].getIndex() == -1))) {
		    // col is the column position for matArray[i]
			// newRow is matArray[i]'s col position
			// changeEntry(row, col, val)
			// we want changeEntry(col, row, val) for transpose
            newVal = ((Entry)matArray[i].getElement()).val;
			newRow = ((Entry)matArray[i].getElement()).col;
			newCol = i;
			matTranspose.changeEntry(newRow, newCol, newVal);
			//matTranspose.NNZ++;
			matArray[i].moveNext();
		 }
	  }
	  return matTranspose;
   }   
   
   // returns a new Matrix that is the product of this Matrix with M
   // Tantalo - "Don't fail to write a helper function called dot"
   // Write Transpose first, first Transpose B, then A * B
   // pre: getSize()==M.getSize()
   Matrix mult(Matrix M) {
      if(getSize() != M.getSize())
	     throw new RuntimeException("Matrix Error: mult() called with incompatible sizes");
	  Matrix newM = M.copy();
      Matrix matTranspose = newM.transpose();
	  Matrix matMult = new Matrix(matSize);
	  matMult.NNZ = 0;
	  double newVal = 0;
	  for(int i = 1; i < matSize; i++) {
	     List A = matArray[i];
		 for(int j = 1; j < matSize; j++) {
		    List B = matTranspose.matArray[j];
            if((!(A.length() == 0)) || (!(B.length() == 0))) {
               newVal = dot(A, B);
			   if(newVal != 0) {
			      matMult.changeEntry(i, j, newVal);
			   }
	        }
         }
      }
      return matMult;	  
   }
   
   // Helper functions
   // Performs the vector dot product of two List entries
   // The dot product of two vectors A = [A1, A2, ..., An] and B = [B1, B2, ..., Bn] is defined as:
   // A*B = Summation of Ai*Bi as (i = 1 to n) = A1B1 + A2B2 +...+AnBn
   private static double dot(List P, List Q) {
      //Move to 0 on both lists
	  double sum = 0;
      P.moveTo(0); Q.moveTo(0);
      while((!(P.getIndex() == -1)) && (!(Q.getIndex() == -1))) {
	     //Case 1: If P.col == Q.col, Sum+= P.col * Q.col, then increment through both lists
	     if(((Entry)P.getElement()).col == ((Entry)Q.getElement()).col) {
		    sum += ((Entry)P.getElement()).val * ((Entry)P.getElement()). val;
			P.moveNext(); Q.moveNext();
		 }
		 //Case 2: If P.col < Q.col, increment P.col
		 else if(((Entry)P.getElement()).col == ((Entry)Q.getElement()).col) {
			P.moveNext();
		 }
		 //Case 3: If P.col > Q.col, increment Q.col
		 else{
		    Q.moveNext();
		 } 
	  }
	  // If one of them falls off, there's nothing but 0's left
      // Just return the sum, as soon as it falls off.
	  return sum;
   }
   
   // Takes in two lists, one from Matrix A and one from B
   // Matrix A[i] = List P, Matrix B[i] = Q
   /*private Matrix addList(List P, List Q, Matrix sumMat, int row){
      if(P.length() == 0 || Q.length() == 0)
	     throw new RuntimeException("Matrix Error: addList() called with at least one empty List");
      List R = new List();
	  double numSum = 0;
	  int newCol = 0;
	  int i = row;
	  P.moveTo(0); Q.moveTo(0);
      if((!(P.getIndex() == -1)) && (!(Q.getIndex() == -1))) {
	     //Case 1: If P.col == Q.col, numSum = P.val + Q.val, append in list then increment through both lists
	     if(((Entry)P.getElement()).col == ((Entry)Q.getElement()).col) {
		    newCol = ((Entry)P.getElement()).col;
		    numSum = ((Entry)P.getElement()).val + ((Entry)P.getElement()). val;
			//Entry index = new Entry(newCol, numSum);
			//if (index.val != 0) R.append(index);
			sumMat.changeEntry(i, newCol, numSum);
			P.moveNext(); Q.moveNext();
		 }
		 //Case 2: If P.col < Q.col, increment P.col
		 else if(((Entry)P.getElement()).col < ((Entry)Q.getElement()).col) {
		    newCol = ((Entry)P.getElement()).col;
		    numSum = ((Entry)P.getElement()).val;
			//Entry index = new Entry(newCol, numSum);
		    //R.append(index);
			sumMat.changeEntry(i, newCol, numSum);
			P.moveNext();
		 }
		 //Case 3: If P.col > Q.col, increment Q.col
		 else{
		    newCol = ((Entry)Q.getElement()).col;
		    numSum = ((Entry)Q.getElement()).val;
			sumMat.changeEntry(i, newCol, numSum);
			//Entry index = new Entry(newCol, numSum);
		    //R.append(index);		 
		    Q.moveNext();
		 } 
	  }
	  // That list would be inserted as a row of the sum matrix
	  // In that case, walk through, but you're not accumulating a sum
	  // you're inserting things into a new list which will be a row
	  // It will be a row of the sum matrix
	  return sumMat;
   }*/

   // Other functions 
   // overrides Object's toString() method
   public String toString() {
      String str = "";
	  for(int i = 1; i < matSize; i++) {
	     if(matArray[i].length() != 0) {
		    matArray[i].moveTo(0);
			str += i + ": ";
	        while(!(matArray[i].getIndex() == -1)) {
		       str += matArray[i].getElement() + " ";
			   matArray[i].moveNext();
		    }
			str += "\n";
	     }		
	  }
	  return str;
   }
}
