

public class DoublyLinkedList {
    // Local class 
	private class DLLNode{
		private DLLNode prev;
		private DLLNode next;
		private String  item;

		// constructor with prev and next
		private DLLNode(DLLNode p, DLLNode n, String s){
			prev = p; next = n;	item = s; 
		}
		// constructor for circularly linked single item list
		private DLLNode(String s){
			item = s; this.next= this; this.prev = this;
		}
		private void setNext(DLLNode n){ next = n; }
		private DLLNode getNext() {return next;}
		private void setPrev(DLLNode p){ prev = p; }
		private DLLNode getPrev() { return prev;}
		private String getItem(){return item;}
	} 
	//  end of DLLNode declaration
    //  notice that everything is private in DLLNode
	

	private DLLNode header;
	private int size;
	
	public DoublyLinkedList(){
		header = new DLLNode("");
        size = 0;
	}
	
	public boolean isEmpty(){
		return size == 0;
	}
	
	public void add(String s){
		// create DLLNode, 
		// with prev=tail and next=header
		DLLNode newOne = new DLLNode(header.getPrev(),header,s);
		newOne.getPrev().setNext(newOne);
	
		//update header
		header.setPrev(newOne);
		size++;
	}

	public DLLNode remove(String s){
    	// find first node with s
    	DLLNode curr = header.getNext();
    	while(curr!=header && !curr.item.equals(s)){
    	    //System.out.println("looking at " + curr.item);
    		curr = curr.getNext();
    	}
    	// either not found
    	if (curr==header){
    		System.out.println("Item \"" + s + "\" not in Doubly Linked List" );
    		return null;
    	}
    	// or found
    	else {
    		// the next of the previous is set to the next
    		// the previous of the next is set to the previous
    		// thereby unhooking curr from the DLL
    		curr.getPrev().setNext(curr.getNext()); // pure
    		curr.getNext().setPrev(curr.getPrev()); // poetry
    		size--;
    		// notice: curr still refers to next and previous
    		return curr;
    	}
    		
    }
    
    public void reInsert (DLLNode x){
    	// using the fact that removed x still refers to its next and prev...
    	// put next of previous back
    	x.getPrev().setNext(x);             //  more
    	// put previous of next back
    	x.getNext().setPrev(x);             //  poetry
    	size++;
    }
    
	public String rev(){
		// go around the DLL in reverse (prev) order
		DLLNode curr = header.prev;
		String res ="Reverse [";
		while(curr != header){
			res+= " " + curr.item;
			curr=curr.getPrev();
		}		
		return res+" ]";
	}
   
	public String toString(){
		// go around the DLL in normal (next) order
		DLLNode curr = header.next;
		String res ="[";
		while(curr != header){
			res+= " " + curr.item;
			curr=curr.getNext();
		}		
		return res+" ]";

	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		DoublyLinkedList DLL = new DoublyLinkedList();
		if(DLL.isEmpty()) System.out.println("DLL empty");
		System.out.println(DLL);
		DLL.add("0");
		System.out.println(DLL);
		for(int i = 2; i<10; i+=2){
			DLL.add(""+i);
			System.out.println(DLL);
		}
		DLL.remove("1");
		System.out.println(DLL);
		System.out.println("removing 0");
		DLLNode it0 = DLL.remove("0");
		System.out.println(DLL);
		System.out.println(DLL.rev());
		
		System.out.println("\nremoving 8");
		DLLNode it8 = DLL.remove("8");
		System.out.println(DLL);
		System.out.println(DLL.rev());
		
		System.out.println("\nremoving 4");
		DLLNode it4 = DLL.remove("4");
		System.out.println(DLL);
		System.out.println(DLL.rev());
		
		System.out.println("\nremoving 2");
		DLLNode it2 = DLL.remove("2");
		System.out.println(DLL);
		System.out.println(DLL.rev());
		
		System.out.println("\nremoving 6");
		DLLNode it6 = DLL.remove("6");
		System.out.println(DLL);
		System.out.println(DLL.rev());
		
		// check empty list
		System.out.println("\nChecking for empty...");
		if(!DLL.isEmpty())System.out.println("DLL SHOULD BE EMPTY!!)");
		else System.out.println("DLL empty");
		
		
		System.out.println("\nreinsertinging 6");
		DLL.reInsert(it6);
		System.out.println(DLL);
		
		
		System.out.println("\nreinsertinging 2");
		DLL.reInsert(it2);
		System.out.println(DLL);
		
		
		System.out.println("\nreinsertinging 4");
		DLL.reInsert(it4);
		System.out.println(DLL);
		
		
		System.out.println("\nreinsertinging 8");
		DLL.reInsert(it8);
		System.out.println(DLL);
		
		
		System.out.println("\nreinsertinging 0");
		DLL.reInsert(it0);
		System.out.println(DLL);
		
		
	}

}