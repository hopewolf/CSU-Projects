import java.io.File;
import java.io.IOException;
import java.util.Scanner;

// Q1.java
// Author: Luke Burford
// Date:   Feb 18, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class Q1 {

	public static void main(String[] args) {
		// Declare variables
		int int0=0, int1=0, int2=0;
		double real0=0.0, real1=0.0, real2=0.0;
		String string0="", string1="", string2="";
		boolean p = true, q = true, r = false;

		try {

		    // Open input stream
		    Scanner scan = new Scanner(new File("data.txt"));

		    // Read contents
		    string0 = scan.nextLine();
		    string1 = scan.nextLine();
		    string2 = scan.nextLine();
		    int0 = scan.nextInt();
		    int1 = scan.nextInt();
		    int2 = scan.nextInt();
		    real0 = scan.nextDouble();
		    real1 = scan.nextDouble();
		    real2 = scan.nextDouble();
		    p = scan.nextBoolean();
		    q = scan.nextBoolean();
		    r = scan.nextBoolean();

		    // Close input stream
		    scan.close();

		} catch (IOException e) {
		    System.out.println("Cannot read file: data.txt");
		    System.exit(0);
		}
		// Code here
		System.out.println(((int0 + int2) * 1234));
		System.out.println(((real1 + real2) / 21.5));
		System.out.printf("%.5f\n", Math.pow(real2, 2));
		System.out.printf("Java programing is %c%c%c%c\n", string0.charAt(14), string0.charAt(12), string0.charAt(15), string0.charAt(13));
		System.out.printf("%s,%s,%s\n",(string0.charAt(4)), (string1.charAt(4)), (string2.charAt(4)));
		System.out.println(string0.equals(string2));
		System.out.println((p&&q)||(!q||r));
		if(string2.length() <= 5) {
			System.out.println("5 characters or fewer");
		}
		else {
			System.out.println("6 characters or more");
		}
		
		if(real2 < 10.02) {
			System.out.println(real2*12.34);
		}
		else if((real2 > 25.6) && (real1 <= 72.54)) {
			System.out.println(real2/2.123);
		}
		else {
			System.out.println(real2 * real2 /9.876);
		}
		switch(string1) {
		case "Cozumel":
		case "Fort Collins":
			System.out.println("North America");
			break;
		case "Santiago":
		case "La Paz":
			System.out.println("South America");
			break;
		default:
			System.out.println("Unkown City");
		}

	}

}
