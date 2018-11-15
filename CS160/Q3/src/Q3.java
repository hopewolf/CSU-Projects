import java.util.Arrays;

// Q3.java
// Author: Luke Burford
// Date:   Apr 5, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class Q3 {
	public static int[] numbers = new int[]{11,321,6,14,981};
	public static double[] decimals = new double[]{1.11,2.22,3.33,2.22,4.44};
	public static String[] names = new String[]{"0123456789","Computer","Science","!@#abcd54321XYZ"};

	public static void main(String[] args) {
		arrayStuff(numbers);
		System.out.println(frequency(decimals, 2.22));
		System.out.println(Arrays.toString(squareRoot(numbers)));
		System.out.println(countDigits(names));

	}
	public static void arrayStuff(int[] integers) {
		System.out.println(integers.length);
		System.out.println(integers[1]);
		System.out.println(Arrays.toString(integers));
		integers[2] = 3355;
		System.out.println(Arrays.toString(integers));
		integers[integers.length-1] = 12345;
		System.out.println(Arrays.toString(integers));
		integers[integers.length-2] = 42;
		System.out.println(Arrays.toString(integers));
	}
	public static int frequency(double[] dArray, double dValue) {
		int count = 0;
		for(int i = 0; i < dArray.length; i++) {
			if(dArray[i] == dValue) {
				count++;
			}
		}
		return count;
	}
	public static double[] squareRoot(int[] iArray) {
		double[] oArray = new double[iArray.length];
		for(int i = 0; i < iArray.length; i++) {
			oArray[i] = Math.sqrt(iArray[i]);
		}
		return oArray;
	}
	public static int countDigits(String[] sArray) {
		int count = 0;
		for(int i = 0; i < sArray.length;i++) {
			for(int j = 0; j < sArray[i].length(); j++) {
				if((sArray[i].charAt(j) == '0') ||
						(sArray[i].charAt(j) == '1') ||
						(sArray[i].charAt(j) == '2') ||
						(sArray[i].charAt(j) == '3') ||
						(sArray[i].charAt(j) == '4') ||
						(sArray[i].charAt(j) == '5') ||
						(sArray[i].charAt(j) == '6') ||
						(sArray[i].charAt(j) == '7') ||
						(sArray[i].charAt(j) == '8') ||
						(sArray[i].charAt(j) == '9')) {
					count++;
				}
			}
		}
		return count;
	}

}
