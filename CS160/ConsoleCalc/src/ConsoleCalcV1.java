// ConsoleCalc.java
// Author: Luke Burford
// Date: Jan 27, 2016
// Class: CS160
// Email: lburford@rams.colostate.edu

import java.util.Scanner;
import java.lang.Math;

public class ConsoleCalcV1 {

	private static Scanner keyboard;
	private static int cond = 1;

	public static void main(String[] args) {


		keyboard = new Scanner(System.in);

		do{
			String string1 = "";
			String string2 = "";

			int var1 = 0;
			int var2 = 0;
			int var3 = 0;

			System.out.println("BASIC CALCULATOR V1" + "\nWritten by: Luke Burford\n");
			System.out.println("Please pick an operation\n1. Addition\n2. Subtration\n3. Multiplication\n4. Division\n5. More\n EXIT");
			System.out.print("Choice: ");
			string1 = keyboard.next();
			for (int i = 0; i < 50; ++i) System.out.println();

			if(string1.equals("1")) {
				System.out.print("First Number: ");
				var1 = keyboard.nextInt();
				System.out.print("\nSecond Number: ");
				var2 = keyboard.nextInt();
				System.out.println("Answer: " + (var1 + var2));
				System.out.println("\nDone!");
			}
			if(string1.equals("2")){
				System.out.print("First Number: ");
				var1 = keyboard.nextInt();
				System.out.print("\nSecond Number: ");
				var2 = keyboard.nextInt();
				System.out.println("Answer: " + (var1 - var2));
				System.out.println("\nDone!");
			}
			if(string1.equals("3")){
				System.out.print("First Number: ");
				var1 = keyboard.nextInt();
				System.out.print("\nSecond Number: ");
				var2 = keyboard.nextInt();
				System.out.println("Answer: " + (var1 * var2));
				System.out.println("\nDone!");
			}
			if(string1.equals("4")){
				System.out.print("First Number: ");
				var1 = keyboard.nextInt();
				System.out.print("\nSecond Number: ");
				var2 = keyboard.nextInt();
				System.out.println("Answer: " + (var1 / var2));
				System.out.println("\nDone!");
			}
			if(string1.equals("5")){
				System.out.println("More Operations: \n1. Exponent\n2. Square Root\n3. Volume Equations");
				System.out.print("Choice: ");
				string1 = keyboard.nextLine();

				if(string1.equals("1")){
					System.out.print("Value: ");
					var1 = keyboard.nextInt();
					System.out.print("\nExponent: ");
					var2 = keyboard.nextInt();
					System.out.println("Answer: " + (Math.pow(var1, var2)));
					System.out.println("\nDone!");
				}
				if(string1.equals("2")){
					System.out.print("Value: ");
					var1 = keyboard.nextInt();
					System.out.println("Answer: " + (Math.sqrt(var1)));
					System.out.println("\nDone!");
				}
				if(string1.equals("3")){
					System.out.println("Pick Shape: \n1. Cube\n2. Cylinder");
					System.out.print("Choice: ");
					string1 = keyboard.nextLine();
					if(string1.equals("1")){
						System.out.print("Base: ");
						var1 = keyboard.nextInt();
						System.out.print("Width: ");
						var2 = keyboard.nextInt();
						System.out.print("Height: ");
						var3 = keyboard.nextInt();
						System.out.println("Answer: " + (var1 * var2 * var3));
						System.out.println("\nDone!");
					}
					if(string1.equals("2")) {
						System.out.print("Radius: ");
						var1 = keyboard.nextInt();
						System.out.print("Height: ");
						var2 = keyboard.nextInt();
						System.out.println("Answer: " + (3.14 * (Math.pow(var1,2)) * var2));
						System.out.println("\nDone!"); 
					}
				}
			}
			if(string1.equals("exit")) {
				for (int i = 0; i < 50; ++i) System.out.println();
				System.out.println("Are you sure?" +  " Yes or No");
				System.out.print("Response: ");
				string2 = keyboard.next();
				if(string2.equals("yes")) {
					System.out.println("Goodbye!");
					return;
					//for (int i = 0; i < 50; ++i) System.out.println();
				}
				if(string2.equals("no")) {
					System.out.println("Goodbye!");
					cond = 0; 
				}
				
			}

			System.out.println("\nRun Again?" + " Yes or No");
			System.out.print("Response: ");
			string2 = keyboard.next();		// 'next' pauses loop but for some reason and 'nextLine' does not. Why? 
//			string2 = keyboard.nextLine();   // For some if only 1 Keyboard scanner it skips it, but with 2 it stays?

			System.out.println();

			if(string2.equals("yes")) {

				//	cond = 1;
				for (int i = 0; i < 50; ++i) System.out.println();
			}
			if(string2.equals("no")) {
				System.out.println("Goodbye!");
				cond = 0; 
			}
		}while(cond >= 1);
		return;
	}
}
