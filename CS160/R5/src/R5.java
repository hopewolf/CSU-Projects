import java.util.Scanner;

// R5.java Assignment
// Author: Luke Burford
// Date:   Feb 9, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class R5 {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		System.out.print("Please print your fist name: ");
		String firstName = sc.nextLine();
		firstName.toLowerCase();
		switch(firstName) {
		case "chihiro":
			System.out.println("You must help your parents!");
			break;
		case "haku":
			System.out.println("You are the river spirit!");
			break;
		case "zeniba":
			System.out.println("You are a powerful witch!");
			break;
		case "kemaji":
			System.out.println("You toil in the boiler room!");
			break;
		default:
			System.out.println("Are you a character in Spirited Away?");
			break;
		}	
		sc.close();
		System.out.println("End of program.");
	}

}
