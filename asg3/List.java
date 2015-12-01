//Antony Robbins
//androbbi@ucsc.edu
//Assignment 3
class List{
   private class Node{
      // Fields
      Object data;
      Node next;
	  Node prev;
      // Constructor
      Node(Object data) {
	     this.data = data;
	     next = null;
		 prev = null;
	  }
	  
      // toString:  Overides Object's toString method.
      public String toString() { return String.valueOf(data); }
   } 

      // Fields
   private Node front;
   private Node back;
   private Node cursor;
   private int length;
   private int index;
  
   // Constructor
   List() {
      front = back = cursor = null; length = 0; index = -1;
   }
 
// Other methods 
// Access Functions //////////////////////////////////////////////////////////////////

   // Returns front element in this list. Pre: length()>0
   Object front(){
      if(length()>0){
         return front.data; 
      }
	  else
	     throw new RuntimeException("List Error: front() called on empty List");
   }

   // length(): returns length of this queue
   int length() { return length; }
   
  
   // isEmpty(): returns true if this is an empty queue, false otherwise
   //boolean isEmpty() { return length == 0; }
 
   
   // Returns the index of the cursor element in this list, or 
   // returns -1 if the cursor element is undefined.
   int getIndex(){
      if(cursor != null){
	     return index;
	  }
	  else
	     return -1;
   }
   
   // Returns back element in this List. Pre: length()>0
   Object back(){
      if(length()>0){
         return back.data; 
      }
	  else
	     throw new RuntimeException("List Error: back() called on empty List");
   }
   
   // Returns cursor element in this list. 
   // Pre: length()>0, getIndex()>=0
   Object getElement() {
      if(length() > 0 && getIndex() >= 0){
	     return cursor.data;
	  }
	  else
	     throw new RuntimeException("List Error: getElement is called on an empty List, or there is no cursor");
   }
   
   // Returns true if this List and L are the same Object
   // sequence. The cursor is ignored in both lists.
   // equals(): returns true if this List is identical to  L, false otherwise.
   public boolean equals(Object x){
	  if ( !(x instanceof Node) ) return false;
      if (x == this) return true;
      Node N = (Node)x;
      
      Node M = (Node)front;
      return N.data.equals(M.data);
   }


// Manipulation Procedures ///////////////////////////////////////////////////////////

   // Inserts new element after back element in this List.
   void append(Object data){
      Node tmp = new Node(data);
      if( length() <= 0 ) {
	     front = tmp;
		 back = front; 
	  }
      else {
	     tmp.prev = back;
	     back.next = tmp;
		 back = tmp;
	  }
	  length++;
   }
   
   // Inserts new element before front element in this List. Index does increment
   void prepend(Object data) {
      Node tmp = new Node(data);
      if(length() == 0){
         front = tmp;
		 back = front;
      }
      else{
	     tmp.next = front;
         front.prev = tmp;
		 front = tmp;
		 if(cursor!= null) {index++;}
      }
	   length++;
   } 

   // Pre: !this.isEmpty()
   // Deletes the front element in this List. Pre: length()>0
   void deleteFront(){
      if(length() <= 0){
         throw new RuntimeException("List Error: deleteFront() called on empty List");
      }
      if(this.length>1) {
	     Node tmp = front;
	     front = front.next;
		 front.prev = null;
		 tmp = null;
	  }
	  else if (index == 0) {cursor = null; index = -1;}
      else {front = back = null;}
	  if(cursor != null) { index--;}
      length--;
   }
   
   // If 0<=i<=length()-1, moves the cursor to the element 
   // at index i, otherwise the cursor becomes undefined.   
   void moveTo(int i) {
      if (i >= 0 && i <= length()-1) {
         Node tmp = front;
		 for(int j = 0; j < i; j++) {
		    tmp = tmp.next;
		 }
		 cursor = tmp;
		 index = i;
	  }
	  else{
	     cursor = null;
	     index = -1;
      }		 
   }
   
   // If 0<getIndex()<=length()-1, moves the cursor one step toward the
   // front of the list. If getIndex()==0, cursor becomes undefined. 
   // If getIndex()==-1, cursor remains undefined. This operation is
   // equivalent to moveTo(getIndex()-1).
   void movePrev() {
      if(0 < getIndex() && getIndex() <= length() -1) {
	     moveTo(getIndex()-1);
	  }	 
	  else if (getIndex() == 0 || getIndex() == -1){
	     cursor = null;
	     index = -1;
	  }
   }
   
   // If 0<=getIndex()<length()-1, moves the cursor one step toward the
   // back of the list. If getIndex()==length()-1, cursor becomes
   // undefined. If index==-1, cursor remains undefined. This
   // operation is equivalent to moveTo(getIndex()+1).
   void moveNext() {
      if(0 <= getIndex() && getIndex() <= length() -1) {
	     moveTo(getIndex()+1);		 
	  }	 
	  else if (getIndex() == length()-1 || getIndex() == -1){
	     cursor = null;
	     index = -1;
	  }
   }  
   
   // Inserts new element before cursor element in this
   // List. Pre: length()>0, getIndex()>=0
   void insertBefore(Object data) {
      if(length()>0 && getIndex() >= 0) {
	     Node in = new Node(data);
		 Node temp = cursor.prev;
		 temp.next = in;
		 cursor.prev = in;
		 in.prev = temp;
		 in.next = cursor;
		 index++;
		 length++;
		 
	   }
   }
   
   // Inserts new element after cursor element in this 
   // List. Pre: length()>0, getIndex()>=0
   void insertAfter(Object data) {
      if(length()>0 && getIndex() >= 0) {
	     Node in = new Node(data);
		 Node temp = cursor.next;
		 temp.prev = in;
		 cursor.next = in;
		 in.prev = cursor;
		 in.next = temp;
		 length++;
      }
   }
   
   // Re-sets this List to the empty state.
   void clear() {
      for(int i = 0; i < length; i++){
	     Node tmp = front;
		 front = front.next;
		 tmp = null;
	  }
	  front = back = cursor = null;
	  length = 0;
	  index = -1;
   }
   
   // Deletes the back element in this List. Pre: length()>0
   void deleteBack() {
      if(length() > 0){
	     Node tmp = back;
	     back = back.prev;
		 tmp = null;
	     length--;
	     if(index == length() -1) {cursor = null; index = -1;}
      }
	  else
	     throw new RuntimeException("List Error: deleteBack() called on empty List");
   }

   // Deletes cursor element in this List. Cursor is undefined after this 
   // operation. Pre: length()>0, getIndex()>=0
   void delete() {
      if(length() > 0 && getIndex()>=0){
		 Node tmp = cursor;
		 Node left = tmp.prev;
		 Node right = tmp.next;
         left.next = right;
		 right.prev = left;
		 tmp = null;
		 cursor = null;
         index = -1;
	     length--;
      }
      else 
	     throw new RuntimeException("List Error: delete() when cursor is null");
   }

   // Other Functions ///////////////////////////////////////////////////////////////////

   // toString():  overides Object's toString() method.
   // Overides Object's toString method. Creates a string 
   // consisting of a space separated sequence of Objects
   // with front on the left and back on the right. The
   // cursor is ignored.
   public String toString(){
      String str = "";
      for(Node N=front; N!=null; N=N.next){
         str += N.toString() + " ";
      }
      return str;
   }

/*
// copy(): returns a new Queue identical to this one.
// Returns a new list representing the same Object sequence as this
// list. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
   List copy(){
      List L = new List();
      Node N = this.front;

      while( N!=null ){
         L.append(N.data);
         N = N.next;
      }
      return L;
   }
*/
}
