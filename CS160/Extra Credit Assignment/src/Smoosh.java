import java.util.Arrays;

// Smoosh.java
// Author: Luke Burford
// Date:   Mar 29, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class Smoosh {
	public static int[] array = {0,0,0,0,1,1,0,0,0,3,3,3,1,1,0};
	//		 reads 0,1,0,3,1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1 after smoosh
	public static void smoosh(int[] ints) {
		// Fill in your solution here.  (Ours is twelve lines long, not counting
		// blank lines or lines already present in this file.)
		int[] arrayOut = new int[array.length];
		int[] arrayTest = new int[array.length];

		for(int i = 0; i < array.length; i++) {
			
			if(!(array[i] < array.length)) {
				if(array[i] != array[i+1]) {
					arrayOut[i] += array[i];
				}
			}

		}
		System.out.println(Arrays.toString(arrayOut));
	}

	/**
	 *  stringInts() converts an array of ints to a String.
	 *  @return a String representation of the array.
	 **/


	public static void main(String[] args) {
		smoosh(array);
		System.out.println(Arrays.toString(array));
	}

}
