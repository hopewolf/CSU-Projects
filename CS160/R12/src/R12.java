// R12.java
// Author: Luke Burford
// Date:   Mar 10, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class R12 {

	// Instance variables
	private double pi = 3.14159;
	private String state = "Colorado State";
	
	public static void main(String[] args) {
		
		// create an instance of the R12 object
		R12 r12 = new R12();
		
		//Prints getState
		System.out.println(r12.getState());

		//Prints calculateQuadratic
		System.out.println(r12.calculateQuadratic(5, 7, 4, 2.0));
		
		//Prints calculateAverage
		System.out.println(r12.calculateAverage(1234, 2345, 3456));
		
		//Prints volumeOfSphere
		System.out.println(r12.volumeOfSphere(5.67));
	}
	
	//returns the state instance variable (other classes can call this method instead of the private variable)
	public String getState() {
		return state;
	}
	
	//Calculates a quadratic of 4 integers and a double squared
	public double calculateQuadratic(int a, int b, int c, double x) {
		return a * (x * x) + b * x + c;
		
	}
	
	// Finds the average of 3 integers
	public double calculateAverage(int value0, int value1, int value2) {
		return (value0 + value1 + value2) / 3.0;
	}
	
	// Calculates the volume of a sphere
	public double volumeOfSphere(double d) {
		return (4.0/3.0) * pi * Math.pow((d/2.0), 3);
	}

}
