import java.util.Arrays;

// R11.java
// Author: Luke Burford
// Date:   Mar 8, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class R11 {

	public static void main(String[] args) {
		//Initialize arrays
		double[] grades = {81.2,92.5,48.9,78.8};
		int[] numbers = {12,42,33,67,92,58};
		String[] arguments = new String[9];
		
		//Print array lengths
		System.out.println(grades.length);
		System.out.println(numbers.length);
		System.out.println(arguments.length);
		
		//Printing individual elements
		System.out.println(grades[3]);
		System.out.println(grades[1]);
		System.out.println(numbers[2]);
		
		//Modifying arrays
		numbers[0] = 99;
		grades[3] = 90.5;
		arguments[6] = "HelloThere";
		
		//Loop to print all elements in a array on one line
		for(int i = 0; i < grades.length; i++){
			System.out.print(grades[i]+",");
		}
		System.out.println();
		for(int i = 0; i < numbers.length; i++){
			System.out.print(numbers[i]+" ");
		}
		System.out.println();
		for(int i = 0; i < arguments.length; i++){
			System.out.print(arguments[i]+"_");
		}
		System.out.println();
		
		//Printing all elements using toString
		System.out.println(Arrays.toString(grades));
		System.out.println(Arrays.toString(numbers));
		System.out.println(Arrays.toString(arguments));
		
		//Print arrayAverage method
		System.out.println(arrayAverage(grades));
		System.out.println(Arrays.toString(reverseArray(grades)));
	}

	// Method that iterates through array, sums it together and divides by length
	public static double arrayAverage(double[] average) {
		double total = 0.0;
		for(int i = 0; i < average.length; i++) {
			total += average[i];
		}
		
		total /= average.length;
		return total;
	}
	
	//Prints off the array backwards
	
	public static double[] reverseArray(double[] in) {
		double[] reverse = new double[in.length];
		int j = 0;
		for(int i = in.length-1; i >= 0; i--) {
			reverse[j] = in[i];
			j++;
		}
		return reverse;
		
	}
}
