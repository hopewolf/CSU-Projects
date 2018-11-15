import java.util.Arrays;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * MyArrayList:  A stripped-down version of ArrayList aimed at demonstrating
 * iterators; for simplicity, type parameters are not used, and the class stores
 * instances of Object
 * @author Asa Ben-Hur
 *
 */

public class MyArrayList implements Iterable {
	
	private Object [] array;
	
	// create an empty list
	public MyArrayList() {
		array = new Object[0];
	}

	// add an object at the end of the list
	public void add(Object element){
		array = Arrays.copyOf(array, array.length + 1);
		array[array.length-1] = element;
	}
	
	// iterator method returns an Iterator, as specified by the Iterable interface
	// Note that the actual object returned is an ArrayIterator, which implements
	// the interface, but that's ok!
	public Iterator iterator() {
		Iterator itr = new ArrayIterator();
		return itr;
	}
	
	// ArrayIterator is an implementation of the Iterator interface
	// It is implemented as an inner class, which allows it access to the 
	// instance variables of the class containing it
	private class ArrayIterator implements Iterator {
		int current = 0;
		public ArrayIterator (){
		      this.current = 0;
		}
		public boolean hasNext(){
		      return (current < array.length);
		}
		public Object next() {
			if (!hasNext())
				throw new NoSuchElementException();
			current++;
			return array[current - 1]; 
		}
		public void remove() throws UnsupportedOperationException{
			throw new UnsupportedOperationException();
		}
		
	}

	
	public static void main(String[] args) {
		MyArrayList a = new MyArrayList();
		a.add(3);
		a.add(5);
		for (Object element: a){
			System.out.println("element: " + element);
		}
	}

}