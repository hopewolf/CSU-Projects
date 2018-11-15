// Pseudo.java
// Author: Luke Burford
// Date:   Mar 10, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class Pseudo {
	//Instance variables
	private char[] charList = new char[80];
	private int stringLength;

	public static void main(String[] args) {
		// Instantiate class		
		Pseudo pseudo = new Pseudo();
		
		//FIXME Incremental tests only DELETE LATER!
		String input = "Hello";
		pseudo.setString(input);
		System.out.println(pseudo.getString());
	}
	
	//Set chars of String in to the charList array and sets the length of string to stringLength
	public void setString(String in){
		
		for(int i = 0; i<in.length();i++){
			charList[i] = in.charAt(i);
			System.out.print(charList[i] + ",");
		}
		
		stringLength = in.length();
	}
	
	//Builds and returns a String with the contents of charList array
	public String getString() {
		String out = "";
		for(int i = 0; i<stringLength;i++){
			out += charList[i];
		}
	return out;
	}
}
