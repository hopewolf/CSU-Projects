// R9.java
// Author: Luke Burford
// Date:   Feb 25, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu
import java.util.Scanner;

public class R9 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner keyboard = new Scanner(System.in);
		String in = "Hello World!";
		reverseString(in);
		printAscii('a','z');
		computeFactorial(10);
		areWeThereYet(keyboard);
		
	}
	public static void reverseString(String s) {
		for(int i = s.length()-1; i >= 0; i--) {
			System.out.print(s.charAt(i));
		}
		System.out.println();
	}

	public static void printAscii(char start, char end) {
		for(; start <= end;start++) {
			System.out.print(start);
		}
		System.out.println();
	}

	public static int computeFactorial(int num) {
	    int i = 1;
	    int factorial = 1;
	    while(i <= num) {
	    	factorial *= i;
	    	i++;
	    }
		return factorial;
	}

	public static void areWeThereYet(Scanner keyboard) {
		String in;
		do{
	    System.out.print("Are we there yet? ");
	    in = keyboard.next();
		}while(!(in.equalsIgnoreCase("yes")));
		System.out.println("Finally!");
		return;
	}

}
