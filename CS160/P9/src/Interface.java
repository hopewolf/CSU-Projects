// Interface.java
// Author: Luke Burford
// Date:   Apr 7, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

// Java interface definition
public interface Interface {

    // Enumeration of chart types
    public enum eType {
        PIECHART, BARCHART, LINEGRAPH
    }

    // Method to read chart file
    public boolean readFile(String filename);
    
    // Method to get chart title
    public String getTitle (eType type);
    
    // Method to get chart labels
    public String[] getLabels(eType type);
    
    // Method to get chart data
    public double[] getData(eType type, int series);
}
