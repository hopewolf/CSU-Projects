// P4.java Assignment
// Author: Luke Burford
// Date:   Feb 9, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

import java.util.Scanner;

public class P4 {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Salary: ");
		float floatSal = sc.nextFloat();
		System.out.print("Exemptions: ");
		int intExemp = sc.nextInt();
		System.out.print("Inrest: ");
		float floatInter = sc.nextFloat();
		System.out.print("Gains: ");
		float floatGain = sc.nextFloat();
		
		float totIncome = (float) (floatSal + floatInter + floatGain - 5000.00);
		if(intExemp > 6) intExemp = 6;
		float adjIncome = (float) (totIncome -(intExemp * 1500.00));
		
	}

}
