import java.util.Arrays;

// MultStrings.java
// Author: Luke Burford
// Date:   Mar 31, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class MultStrings {
	public static String[] multStrings(String [] s, int[] i) {
		//Solution here
		String [] out = new String[s.length];
		for(int j = 0; j < s.length; j++) {
			out[j] = "";
		}
		for(int j = 0; j < s.length; j++){
			String tempString = s[j];
			int tempInt = i[j];
			for(int k = 0; k < tempInt; k++ ) {
				out[j] += tempString;
			}
		}
		return out;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int [] arr = {2,3,1,0,5};
		String [] s = {"Hey", "Sun", "Puppies", "Bannans", "me"};
		String [] result = multStrings(s,arr);
		
		System.out.println(Arrays.toString(result));
		
		System.out.println(Arrays.toString(s));
	}

}
