// QuizInterface.java
// Author: Luke Burford
// Date:   Apr 26, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public interface QuizInterface {

    // Interface Methods
    
    // Reads file contents into an array of strings
    public void readFile(String filename);

    // Compute statistics for the array
    public void computeStatistics(String []strings);

    // Print statistics for the array
    public void printStatistics();
    
    // Writes the contents of the array to a file
    public void writeFile(String filename, String []strings);
}
