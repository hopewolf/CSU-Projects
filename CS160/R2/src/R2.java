// R2.java Assignment
// Author: Luke Burford
// Date:   Jan 28, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class R2 {

	public static void main(String[] args) {
		char c0 = '$';
		char c1 = 'W';
		byte b0 = 15;
		byte b1 = 4;
		short s0 = 5577;
		short s1 = 1234;
		int i0 = 12345;
		long l0 = 8000000000l;
		long l1 = -7000000000l;
		float f0 = 1.2345f;
		float f1 = 66.7788f;
		double d0 = 0.00001;
		double d1 = 83475.29837;

		System.out.println(b0 + b1);
		System.out.println((b0 + b1) / 4);    			  // All numbers are intergers (whole numbers) so the result will say such
		System.out.println((b0 + b1) / 4.0); 			  // When divided by 4.0 it allows for a floating variable and since 19 / 4 isnt a whole number its now able to be expressed
		System.out.println(s0 / 1000);       			  // The same results as before, whole ints, whole out.
		System.out.println(s0 / 1000.0);	  			  // Adds a floating value allowing the out to be a float as well, 
		System.out.println(s1 % 100);			  		  // The % operator divides but the output is the remainder of the operation.
		System.out.println((i0 - 2345) * 10); 			  // The parenthesis make the sub operation a priority over the multiplication operation.
		System.out.println(i0 -2345 * 10);    			  // Follows the standard Java order of operations
		System.out.println(l0 + l1);
		System.out.println((f0 + f1) / (d0 * d1));
		System.out.println(0.1 + 0.2 - 0.3);  			  // Binary is unable to operate a floating/decimal 0.0 
		System.out.println(6 % 4 + 12 - 3 * (8 + 3) / 2); // Yes?
		
		c0++; // increment c0 by 1 every iteration (only iterates once)
		c1++; // increment c1 by 1 every iteration (only iterates once)
		
		System.out.println(c0 + "," + c1); 				  // Adds the values up by one, ex after the $ is the % key, & in the alphabet after W is X.
		System.out.println("5577 + 1234 = " + s0 + s1);
		System.out.printf("5577 + 1234 = %d\n", s0 + s1);
		System.out.printf("0.00001 + 83475.29837 = %.2f\n", d0 + d1);
		System.out.printf("0.00001 + 83475.29837 = %.5f\n", d0 + d1);
	}

}
