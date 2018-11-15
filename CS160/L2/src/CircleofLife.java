// CircleofLife.java
// Author: Luke Burford
// Date:   Sep 2, 2016
// Class:  CS161
// Email:  lburford@rams.colostate.edu

public class CircleofLife {

    public static void main(String args[]) {

        // Create a new Species object here, passing in the appropriate arguments
		Species r = new Species("rabbit",100,10);
        // Print out the species' growth rate
		System.out.println("growth of rabbit: "+r.growth);
        // Use the species' toString here
		System.out.println(r);
        // Call populationInXYears here
		System.out.println("In 2 years the pop will be: "+r.populationInXYears(2));
        // Create a new Species object here, passing in the appropriate arguments
        // using a very large number for the population (e.g. 100000000)
		Species c = new Species("cat",40000,10);
        // Print out the species' population to make sure it is set to 1500
		System.out.println("cat pop is: "+c.pop);
        // Call populationInXYears here, feel free to hardcode in the int to be passed to the method
		System.out.println("cat pop in 2 years is: "+c.populationInXYears(2));
        // Call mergeSpecies here. Test that mergeSpecies is doing what you expected it to
		c.mergeSpecies(r);
		System.out.println(c);
    }
}