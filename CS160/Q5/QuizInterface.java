// Final Programming Quiz (Interface File)
// Author: Chris Wilcox
// Date:   4/29/2016
// Class:  CS160
// Email:  wilcox@cs.colostate.edu

public interface QuizInterface {

	// Initializes an array of values
	public void initializeArray(double values[]);
	
	// Sum values within a range of indices in an array
	public double sumRange(double values[], int low, int high);

	// Reads contents of file into an array of strings
	public String[] readFile(String filename);

	// Counts frequency of string in array of strings
	public int substringFrequency(String []strings, String search);

	// Write specific content to a file
	public void writeFile(String filename);
}

