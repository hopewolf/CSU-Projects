import java.util.Scanner;

// R8.java
// Author: Luke Burford
// Date:   Feb 23, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class R8 {

	public static void main(String[] args) {
		// Declare variables
		String restaurantName;
		String serverName;
		double subtotal;
		double tax;
		double total;
		double taxRate = 0.05;
		double tipRate1 = 0.10;
		double tipRate2 = 0.15;
		double tipRate3 = 0.20;
		Scanner sc = new Scanner(System.in);

		// Ask and receive input from the user
		System.out.print("Enter restraunt name: ");
		restaurantName = sc.nextLine();

		System.out.print("Enter server name: ");
		serverName = sc.nextLine();
		serverName = serverName.substring(0,(serverName.indexOf(" "))); // Get only the first name of the server
		serverName = serverName.toUpperCase();						    // Convert the string to upper case letter.

		System.out.print("Enter cost of bill: ");
		subtotal = sc.nextDouble();

		// Perform calculations
		tax = computeTax(subtotal, taxRate);
		total = subtotal + tax;

		// Print receipt
		System.out.println("=====================================");
		System.out.println(restaurantName);
		System.out.printf("Your server was: %s\n", serverName);
		System.out.printf("Subtotal: $%.2f\n", subtotal);
		System.out.printf("Tax: $%.2f\n", tax);
		System.out.println("=====================================");

		System.out.printf("Total: $%.2f\n", total);

		System.out.println("\nSuggested tips:");

		System.out.print("10%: ");									// Prints off all of the tip rates (%10,%15,%20)
		System.out.printf("$%.2f\n",(computeTip(total, tipRate1)));
		System.out.print("15%: ");
		System.out.printf("$%.2f\n",(computeTip(total, tipRate2)));
		System.out.print("20%: ");
		System.out.printf("$%.2f\n",(computeTip(total, tipRate3)));

		System.out.println("\nThank you!");
		System.out.println("=====================================");

		sc.close(); // Close Scanner

	}

	// Calculates the tax of the sub-total.
	public static double computeTax(double amount, double rate) {
		double out = rate * amount;
		return out;
	}

	// Calculates the tip rate no matter what the specific tip rate is.
	public static double computeTip(double amount, double rate) {
		double out = amount * rate;
		return out;
	}

}
