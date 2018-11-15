import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

// Library.java
// Author: Luke Burford
// Date:   Apr 19, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class Library {
	public static Music[] arrayTitles;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		readLibrary(args[0]);
		writeLibrary(args[1]);
	}
	
	public static void readLibrary(String inputFile) {
		try {
			Scanner reader = new Scanner(new File(inputFile));
			int numTitles = reader.nextInt();
			reader.nextLine();
			arrayTitles = new Music[numTitles];
			for(int i = 0; i < numTitles; i++) {
				String song = reader.nextLine();
				String album = reader.nextLine();
				String artist = reader.nextLine();
				int date = reader.nextInt();
				reader.nextLine();
				arrayTitles[i] = new Music(song, album, artist, date);
			}
			reader.close();
		}catch(FileNotFoundException e) {
			System.err.println("Could not read file");
			return;
		}
	}
	
	public static void writeLibrary(String outputFile) {
		try {
			PrintWriter writer = new PrintWriter(outputFile);
			for(int i = 0; i < arrayTitles.length; i++) {
				writer.println(i+1 + ": " + arrayTitles[i]);
			}
			writer.println("Number of Tracks: " + arrayTitles.length);
			double cost = 0.0;

			for(int i = 0; i < arrayTitles.length; i++) {
				cost += arrayTitles[i].getPrice();
			}
			writer.print("Total cost: ");
			writer.printf("%.2f", cost);
			writer.close();
		} catch(Exception e) {
			System.err.println("Could not write file");
		}
	}
	
	public static void searchTitles(String search) {
		for(int i = 0; i < arrayTitles.length; i++) {
			if(search.contains(arrayTitles[i].getTitle())) {
				System.out.println(arrayTitles[i]);
				break;
			}
			
		}
	}
}
