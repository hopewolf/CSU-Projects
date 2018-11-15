// CalcLogicTest.java
// Author: Luke Burford
// Date:   Feb 4, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

import java.util.Scanner;

public class CalcLogicTest {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int total = 0;
		boolean test = true;
	      while (test == true) {
	          int aInt = sc.nextInt();
	          System.out.print(aInt);
	          String aString = sc.next();
	          if(aString.equals("+"))
	        	  total += aInt;
	          if(aString.equals("-"))
	        	  total -= aInt;
	          if(aString.equals("="))
	        	  break;
	          System.out.print(aString);
	      }
	      System.out.println("=" + total);
		sc.close();
		return;
	}

}
