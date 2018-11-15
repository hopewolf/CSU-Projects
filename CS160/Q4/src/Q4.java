import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

import javax.xml.stream.events.Characters;

// Q4.java
// Author: Luke Burford
// Date:   Apr 26, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class Q4 implements QuizInterface {
	
	// Class variables
	public static int numberLines = 0;
	public static int numberChars = 0;
	public static int numberLower = 0;
	public static int numberUpper = 0;
	public static int numberDigits = 0;
	public static String[] fileContents;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Q4 q4 = new Q4();
	    q4.readFile(args[0]);
	    //q4.computeStatistics(fileContents);
	    //q4.printStatistics();
	    q4.writeFile(args[1], fileContents);
	}

	@Override
	public void readFile(String filename) {
		
		try{
			Scanner reader = new Scanner(new File(filename));
			
			numberLines = reader.nextInt();
			reader.nextLine();
			fileContents = new String[numberLines];
			for(int i = 0; i < fileContents.length; i++) {
				fileContents[i] = reader.nextLine();
			}
			reader.close();
			
		} catch(Exception e) {
			System.err.println("Could not read file!");
			
		}
		//System.out.println(numberLines);
		//System.out.println(fileContents[0]);
	}

	@Override
	public void computeStatistics(String[] strings) {
		
		for(int i = 0; i < strings.length; i++) {
			for(int j = 0; j < strings[i].length(); j++) {
			//Character.isLowerCase(string[i]);
			}
			
		}
		
	}

	@Override
	public void printStatistics() {
		System.out.println("Number of lines: " + numberLines);
		System.out.println("Number of characters: " + numberChars);
		System.out.println("Number of uppercase letters: " + numberUpper);
		System.out.println("Number of lowercase letters: " + numberLower);
		System.out.println("Number of digits: " + numberDigits);	
	}

	@Override
	public void writeFile(String filename, String[] strings) {
		 try {
			 int count = 1;
			 PrintWriter writer = new PrintWriter(new File(filename));
			 for(int i = 0; i < strings.length; i++) {
				 writer.print(count + ": ");
				 writer.println(strings[i]);
				 count++;
			 }
			 writer.close();
		 } catch(Exception e) {
			 
		 }
		
	}

}
