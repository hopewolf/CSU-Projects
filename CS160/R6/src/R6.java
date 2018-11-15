// R6.java
// Author: Luke Burford
// Date:   Feb 11, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

import java.util.Scanner;
import java.lang.Math;

public class R6 {

	public static void main(String[] args) {
	    Scanner keyboard = new Scanner(System.in);

	    //Prints a welcome message
	    System.out.println("Welcome to a simple calculator program!");
	    System.out.println("---------------------------------------");
	    System.out.println("All we know how to do is add, subtract, multiply, divide, compute modulo, and exponents.");
	    System.out.println();

	    //Get input from the user
	    System.out.print("Please enter a the first number of your calculation: ");
	    double lhs = keyboard.nextDouble();
	    
	    //Get input for operator from the user.
	    System.out.print("Please enter the operator (+|-|*|/|%): ");
	    String symbol = keyboard.next();

	    //Get input for the right hand side of the operator from the user 
	    System.out.print("Please enter a the second number of your calculation: ");
	    double rhs = keyboard.nextDouble();

	    // Here we will calculate the result:
	    double result = 0.0;

	    // Checks the operator and executes the appropriate operation
	    switch(symbol) {
	    case "+":
	    	result = lhs + rhs;
	    	break;
	    case "-":
	    	result = lhs - rhs;
	    	break;
	    case "*":
	    	result = lhs * rhs;
	    	break;
	    case "/":
	    	if(rhs == 0) {
	    	    System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	    		System.out.println("ERROR: Unable to divide by zero.");
	    	    System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	    		break;
	    	}
	    	else {
	    	result = lhs / rhs;
	    	break;
	    	}
	    case "%":
	    	result = lhs % rhs;
	    	break;
	    case "^":
	    	result = Math.pow(lhs, rhs);
	    	break;
	    default:
		    System.out.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	    	System.out.println("ERROR: Thats not a math operaion this calculator can do.");
		    System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	    	System.out.println("End of program.");
	    	keyboard.close();
	    	return;
	    }

	    // Print the result
	    System.out.println("---------------------------------------");
	    System.out.println("Result:");
	    // Print the formated 
	    System.out.printf("%.2f\n", result);

	    System.out.println("---------------------------------------");

	    keyboard.close();
	    System.out.println("End of program.");

	}

}
