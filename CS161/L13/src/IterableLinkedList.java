import java.util.Arrays;
import java.util.Iterator;
import java.util.NoSuchElementException;


public class IterableLinkedList implements Iterable {
	private Node head;
	private int size;
	
	public IterableLinkedList() {
		head = null;
	}

	public void add(Object item) {
		add(size, item);
	}

	public void add(int index, Object item) {
		if (index < 0 || index > size)
			throw new IndexOutOfBoundsException(
					"List index out of bounds on add");
		if (index == 0) {
			head = new Node(item, head);
		} else { // find predecessor
			Node curr = head;
			for (int i = 0; i < index - 1; i++) {
				curr = curr.getNext();
			}
			// append after predecessor
			curr.setNext(new Node(item, curr.getNext()));
		}
		size++;
	}


	public Iterator iterator() {
            // complete this method
            return null;
	}
	
	private class LinkedListIterator implements Iterator {
		
		public LinkedListIterator (){
                    // complete this method
		}
		
		public boolean hasNext(){
                    // complete this method
                    return false;
		}
		
		public Object next() {
                    // complete this method
                    return null;
		}
		
		public void remove() throws UnsupportedOperationException{
			throw new UnsupportedOperationException();
		}
		
	}

	
	public static void main(String[] args) {
		IterableLinkedList a = new IterableLinkedList();
		a.add(3);
		a.add(5);
		for (Object element: a){
			System.out.println("element: " + element);
		}
	}
	
}