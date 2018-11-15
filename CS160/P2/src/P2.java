// P2 Assignment
// Author: Luke Burford
// Date:   Jan 26, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class P2 {

	public static void main(String[] args) {
		byte varByte = 19;
		short varShort = 12345;
		int varInt = 886644;
		Long varLong = 4123456789L;
		float varFloat = 2.579F;
		double varDouble = 67.3434;
		char varChar1 = '%';
		char varChar2 = 'X';
		char varChar3 = '5';
		String varString1 = "Computer";
		String varString2 = "Science";
		String varString3 = "Awesome";
		
	/*-------------------------------------------------------------------------------------------------------------------------*/
		
		//(Line 1) Print the four integer values in the following order (byte,short,int,long) separated by commas (,).
		System.out.println(varByte + "," + varShort + "," + varInt + "," + varLong);
		
		//(Line 2) Print the two floating-point values in the following order (float, double) separated by a semicolons (;).
		System.out.println(varFloat + ";" + varDouble);
		
		//(Line 3) Print the sum of all the integer variables divided by 9999.
		System.out.println(((varByte + varShort + varInt + varLong)/9999));
		
		//(Line 4) Use Math.sqrt() to compute and print the square root of the sum of the float and double. 
		System.out.printf("%.3f\n",Math.sqrt(varFloat + varDouble));		//Uses the "printf to round to 3 sig figs using "%.3f"
			
		//(Line 5) Print the quotient of the byte variable divided by the float variable. 
		System.out.printf("%.5f\n",(varByte/varFloat));		//Same syntax as before, the \n is just for a new line
		
		//(Line 6) Print the three characters, separated by equals signs (=).
		System.out.println(varChar1 + "=" + varChar2 + "=" + varChar3);
		
		//(Line 7) Subtract 3 from all three character values and print them again, separated by tildes (~).
		System.out.printf("%C~",varChar1-3);		// Uses the function "%C~"(format-string)
		System.out.printf("%C~",varChar2-3);		// C converts to uppercase char, a phrase can be printed after the format-string
		System.out.printf("%C\n",varChar3-3);
		
		//(Line 8) Using the three String variables and string constants, print Computer Science is Awesome!. 
		System.out.println(varString1+" "+varString2+" "+"is "+varString3+"!");
		
		//(Line 9) Print the length of all three String variables, separated by commas.
		System.out.println(varString1.length()+","+varString2.length()+","+varString3.length());
		
		//(Line 10) Print the third String variable in uppercase letters.
		System.out.printf("%S\n",varString3);
		
		//(Line 11) Print the fourth through seventh characters of the first String variable.
		System.out.println(varString1.substring(3,7));		// tricky, the "cursor" must encase the chars, so p=4 e=7 the "box" is 3(outside of p) through 7(outside of e)
		
		//(Line 12) Print the index of the character 'i' in the second String variable.
		System.out.println(varString2.indexOf('i'));
		
		//(Line 13) Print the fifth character of the first String variable.
		System.out.println(varString1.charAt(4));		// If printing 5th char "cursor" must be in front, thus the cursor is in 4, so you write 4
	}

}
