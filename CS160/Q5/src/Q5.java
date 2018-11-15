import java.io.File;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

// Q5.java
// Author: Luke Burford
// Date:   May 3, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class Q5 implements QuizInterface {

	public static void main(String[] args) {

		Q5 Q5 = new Q5();

		double[] myDoubles = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
		Q5.initializeArray(myDoubles);
		System.out.println("Array: " + Arrays.toString(myDoubles));
		double sum = Q5.sumRange(myDoubles, 3, 6);
		System.out.printf("Sum: %.1f\n", sum); 

		String lines[] = Q5.readFile(args[0]);
		System.out.println("Number of Lines: " + lines.length);
		int frequency = Q5.substringFrequency(lines, "from");
		System.out.println("Found " + frequency + " occurrences of 'from'."); 
		frequency = Q5.substringFrequency(lines, "the");
		System.out.println("Found " + frequency + " occurrences of 'the'.");
		Q5.writeFile(args[1]);
	}

	@Override
	public void initializeArray(double[] values) {
		for(int i = 0; i < values.length; i++) {
			values[i] = i * 11111.11;
		}
	}

	@Override
	public double sumRange(double[] values, int low, int high) {
		return values[low] + values[high];
	}

	@Override
	public String[] readFile(String filename) {
		String[] strings = null;
		try{
			Scanner reader = new Scanner(new File(filename));
			strings = new String[reader.nextInt()];
			reader.nextLine();
			for(int i = 0; i < strings.length; i++) {
				strings[i] = reader.nextLine();
			}
			reader.close();
		}catch(Exception e){
			//Null
		}
		return strings;
	}

	@Override
	public int substringFrequency(String[] strings, String search) {
		int count = 0;
		for(int i = 0; i < strings.length; i++) {
			Scanner reader = new Scanner(strings[i]);
			while(reader.hasNext()) {
				String tempString = reader.next();
				if(tempString.contains(search)) {
					count++;
				}
			}
			reader.close();
		}
		return count;
	}

	@Override
	public void writeFile(String filename) {
		try{
			PrintWriter writer = new PrintWriter(new File(filename));
			for(int i = 0; i < 100; i++) {
				writer.print("I'm pretty good at this Java programming thing!");
				if(i < 99) writer.println();
			}
			writer.close();
		}catch(Exception e) {

		}

	}

}
