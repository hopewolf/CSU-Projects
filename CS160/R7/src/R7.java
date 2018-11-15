// R7.java
// Author: Luke Burford
// Date:   Feb 16, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class R7 {

	public static boolean and(boolean b0, boolean b1) {
	    return b0 && b1;
	}

	public static boolean or(boolean b0, boolean b1) {
		return b0 || b1;
	}

	public static boolean xor(boolean b0, boolean b1) {
		return b0 ^ b1;
	}

	public static boolean nand(boolean b0, boolean b1) {
		return !(b0 && b1);
	}

	public static boolean nor(boolean b0, boolean b1) {
		return !(b0 || b1);
	}

	public static boolean special(boolean b0, boolean b1) {
		return (b0 ^ b1) && (!b0 || b1);
	}

	public static void printHeader(String logicalOperatorName) {
		System.out.println("b0	" + "b1	" + "b0 " + logicalOperatorName + " b1");
		//System.out.printf("b0\tb1\t ");
	}

	public static void printRow(boolean b0, boolean b1, boolean result) {
	    System.out.println(b0 + "	" + b1 + "	" + result);
	}

	public static void main(String[] args) {

	    // Print truth table (AND)
	    printHeader("AND");
	    printRow(true, true, and(true,true));
	    printRow(true, false, and(true,false));
	    printRow(false, true, and(false,true));
	    printRow(false, false, and(false,false));
	    System.out.println();
		
	    // Print truth table (OR)
	    printHeader("OR");
	    printRow(true, true, or(true,true));
	    printRow(true, false, or(true,false));
	    printRow(false, true, or(false,true));
	    printRow(false, false, or(false,false));
	    System.out.println();

	    // Print truth table (XOR)
	    printHeader("XOR");
	    printRow(true, true, xor(true,true));
	    printRow(true, false, xor(true,false));
	    printRow(false, true, xor(false,true));
	    printRow(false, false, xor(false,false));
	    System.out.println();
	    
	    // Print truth table (NAND)
	    printHeader("NAND");
	    printRow(true, true, nand(true,true));
	    printRow(true, false, nand(true,false));
	    printRow(false, true, nand(false,true));
	    printRow(false, false, nand(false,false));
	    System.out.println();
	    
	    // Print truth table (NOR)
	    printHeader("NOR");
	    printRow(true, true, nor(true,true));
	    printRow(true, false, nor(true,false));
	    printRow(false, true, nor(false,true));
	    printRow(false, false, nor(false,false));
	    System.out.println();
	    // Print truth table (SPECIAL)
	    printHeader("SPECIAL");
	    printRow(true, true, nor(true,true));
	    printRow(true, false, nor(true,false));
	    printRow(false, true, nor(false,true));
	    printRow(false, false, nor(false,false));
	    System.out.println();
	}
}
