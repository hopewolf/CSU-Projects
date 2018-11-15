// R3.java Assignment
// Author: Luke Burford
// Date:   Feb 4, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

import java.util.Scanner;

public class R3{

	public static void main(String[] args) {

		String myString0 = "Java";
		String myString1 = "Programming";
		String myString2 = "Language";
		Scanner keyboard = new Scanner(System.in);
		int myInteger = 0;
		double myDouble = 0.0;

		System.out.println(myString0+" is a "+myString1+" "+myString2+".");
		System.out.println(myString1.length() + myString2.length());
		System.out.println(myString1.charAt(1)+","+myString1.charAt(3)+","+myString1.charAt(6));
		System.out.println(myString0.indexOf("a"));
		System.out.println(myString2.toUpperCase());
		System.out.println(myString1.substring(2,8));

		System.out.print("Enter an integer: ");
		myInteger = keyboard.nextInt();
		System.out.println("myInteger = "+myInteger);
		System.out.print("Enter a double: ");
		myDouble = keyboard.nextDouble();
		System.out.printf("myDouble = %.5f\n",myDouble);
		keyboard.close();
	}

}