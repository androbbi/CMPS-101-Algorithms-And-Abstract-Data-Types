class List{
   private class Node{
      // Fields
      int data;
      Node next;
	  Node prev;
      // Constructor
      Node(int data) {
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
   int front(){
      if(length()>0){
         return front.data; 
      }
	  else
	     throw new RuntimeException("Queue Error: front() called on empty Queue");
   }

   // length(): returns length of this queue
   int length() { return length; }
   
  
   // isEmpty(): returns true if this is an empty queue, false otherwise
   boolean isEmpty() { return length == 0; }
 
   
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
   int back(){
      if(length()>0){
         return back.data; 
      }
	  else
	     throw new RuntimeException("Queue Error: back() called on empty Queue");
   }
   
   // Returns cursor element in this list. 
   // Pre: length()>0, getIndex()>=0
   int getElement() {
      if(length() > 0 && getIndex() >= 0){
	     return cursor.data;
	  }
	  else
	     throw new RuntimeException("Queue Error: getElement is called on an empty List, or there is no cursor");
   }
   
   // Returns true if this List and L are the same integer
   // sequence. The cursor is ignored in both lists.
   // equals(): returns true if this Queue is identical to  Q, false otherwise.
   boolean equals(List L){
      boolean flag  = true;
      Node N = this.front;
      Node M = L.front;

      if( this.length==L.length ){
         while( flag && N!=null){
            flag = (N.data==M.data);
            N = N.next;
            M = M.next;
         }
         return flag;
      }else{
         return false;
      }
   }


// Manipulation Procedures ///////////////////////////////////////////////////////////

   // Inserts new element after back element in this List.
   void append(int data){
      Node tmp = new Node(data);
      if(this.isEmpty()){
         front = back = tmp; back.next = null; front.prev = null; length++;
      }
      else{
         tmp.next = null; back.next = tmp; back = tmp;
		 if(index != -1) {index++;}
      }
   }
   
   // Inserts new element before front element in this List. Index does increment
   void prepend(int data) {
      Node tmp = new Node(data);
      if(this.isEmpty()){
         front = back = tmp; back.next = null; front.prev = null; length++;
      }
      else{
         tmp.next = null; back.next = tmp; back = tmp;
		 if(index != -1) {index++;}
      }
   } 

   // Pre: !this.isEmpty()
   // Deletes the front element in this List. Pre: length()>0
   void deleteFront(){
      if(this.isEmpty()){
         throw new RuntimeException("List Error: deleteFront() called on empty List");
      }
      if(this.length>1) {front = front.next;}
      else {front = back = null;}
      length--;
   }
   
   // Re-sets this List to the empty state.
   void clear() {
      for(int i = 0; i < length; i++){
         front = null;
		 front = front.next;
	  }
	  length = 0;
	  index = -1;
   }
   
   // If 0<=i<=length()-1, moves the cursor to the element 
   // at index i, otherwise the cursor becomes undefined.   
   void moveTo(int i) {
      if (0 <= i && i <= length()-1) {
	     if(i > index) { // if i is greater than current index, move right
		    for(int j = 0; j <= i; j++) {
			   if( cursor == null) {cursor = front;}
			   else {cursor = cursor.next;}
               index++;			   
            }
		 }
		 if(i < index) { // if i is less than current index, move left
		    for(int j = 0; j <= i; j++) {
			   cursor = cursor.prev;
               index++;   
            }
		 }
	  }
	  else
	     index = -1;
   }
   
   // If 0<getIndex()<=length()-1, moves the cursor one step toward the
   // front of the list. If getIndex()==0, cursor becomes undefined. 
   // If getIndex()==-1, cursor remains undefined. This operation is
   // equivalent to moveTo(getIndex()-1).
   void movePrev() {
      if(0 <getIndex() && getIndex() <= length() -1) {
	     moveTo(getIndex() - 1);   
	  }	 
	  else if (getIndex() == 0 || getIndex() == -1){
	     index = -1;
	  }
   }
   
   // If 0<=getIndex()<length()-1, moves the cursor one step toward the
   // back of the list. If getIndex()==length()-1, cursor becomes
   // undefined. If index==-1, cursor remains undefined. This
   // operation is equivalent to moveTo(getIndex()+1).
   void moveNext() {
      if(0 <getIndex() && getIndex() <= length() -1) {
	     moveTo(getIndex() + 1);   
	  }	 
   }  
   
   // Inserts new element before cursor element in this
   // List. Pre: length()>0, getIndex()>=0
   void insertBefore(int data) {
      if(length()>0 && getIndex() >= 0) {
	     Node tmp = new Node(data);
		 tmp.next = cursor;
		 cursor.prev = tmp;
		 index++;
	   }
   }
   
   // Inserts new element after cursor element in this 
   // List. Pre: length()>0, getIndex()>=0
   void insertAfter(int data) {
      if(length()>0 && getIndex() >= 0) {
	     Node tmp = new Node(data);
		 tmp.prev = cursor;
		 cursor.next = tmp;
      }
   }
   
   // Deletes the back element in this List. Pre: length()>0
   void deleteBack() {
      back = null;
	  back = back.prev;
	  length--;
   }

   // Deletes cursor element in this List. Cursor is undefined after this 
   // operation. Pre: length()>0, getIndex()>=0
   void delete() {
      if(length() > 0 && getIndex()>=0){
	     cursor.prev = cursor.next;
		 cursor.next = cursor.prev;
		 cursor = null;
         index = -1;
	     length--;
		 }
   }

   // Other Functions ///////////////////////////////////////////////////////////////////

   // toString():  overides Object's toString() method.
   // Overides Object's toString method. Creates a string 
   // consisting of a space separated sequence of integers
   // with front on the left and back on the right. The
   // cursor is ignored.
   public String toString(){
      String str = "";
      for(Node N=front; N!=null; N=N.next){
         str += N.toString() + " ";
      }
      return str;
   }


   // copy(): returns a new Queue identical to this one.
   // Returns a new list representing the same integer sequence as this
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

}
