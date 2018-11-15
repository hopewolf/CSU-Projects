import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

// R16.java
// Author: Luke Burford
// Date:   Apr 7, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class R16 {
	public static double area;
	public static void main(String[] args) {
		//READ
		try {

			Scanner fileReader = new Scanner(new File(args[0]));

			fileReader.next();
			double width = fileReader.nextDouble();
			double height = fileReader.nextDouble();
			area = width * height;

			fileReader.close();
		}
		catch (FileNotFoundException e) {
			System.out.println("ERROR!");
			System.exit(0);
		}
		
		//WRITE
		try {
			
			PrintWriter fileOutput = new PrintWriter(new File(args[1]));
			
			fileOutput.print("Rectangle area: ");
			fileOutput.print(area);
			
			// Important! Save the file
		    fileOutput.close();
			
		}
		catch (FileNotFoundException e) {
			System.out.println("ERROR!");
			System.exit(0);
		}
	}
}
