/**
 * @author lburford
 *
 */
public class Recursion {
	
	/* Precondition: n >= 0
           Postcondition:  returns the nth number in a sequence where each element is twice its 
           predecessor, and starts with 1.
	*/
	public int pracSeq1(int n){
		if(n==0) {
			return 1;
		}
		else {
			return 2*pracSeq1(n-1);
		}
	}
	
	/* Precondition: n >= 0
           Postcondition:  returns the nth number in a sequence where each element is the sum of
           the previous 3, and starts with 1,2,3
	*/
	public int pracSeq2(int n){
		if(n < 3)
			return n+1;
		else
			return pracSeq2(n-1)+pracSeq2(n-2)+pracSeq2(n-3);
	}
		
        /* Precondition:  word is an instance of String
           Postcondition:  returns true if word is a palindrome, and false otherwise
        */
	public boolean palindrome(String word){
		return palindrome(0,word.length()-1,word);
	}
	
	public boolean palindrome(int i,int j, String word) {
		if(i >= j) {
				return true;
		}
		else {
			if(word.charAt(i) == word.charAt(j))
				return palindrome(i+1,j-1,word);
			else
				return false;
		}
	}
	
        /* Precondition:  n >= 0
           Postcondition:  returns the nth number in a sequence where each element is 1/2 its predecessor plus 3 times its predecessor.  The value at n=0 is 1.
        */
	public int sequence3(int n){
		if(n==0)
			return 1;
		else {
			return (int)(3*sequence3(n-1) + 0.5*sequence3(n-1));
		}
	}

	/* Precondition: x >= 1
           Postcondition: prints the appropriate star pattern for the value of x
	 */
	public void starPattern(int x){
		if(x==1)
			System.out.println("*");
		else {
			System.out.print(starString(x));
			starPattern(x-1);
		}
	}
	
	public String starString(int x){
		if(x==0){
			return "\n";
		}
		else
			return "*"+starString(x-1);
	}
	
	public static void main(String args[]){

            Recursion rec = new Recursion();

            //Each number being passed to the methods are the indices
            //of the number we are looking for
            // modify the code to use assertions to verify the expected result
		System.out.println("pracSeq1(int x):");
		System.out.println("Answer: " + rec.pracSeq1(5) + "   Expecting: 32");
		System.out.println("Answer: " + rec.pracSeq1(7) + "   Expecting: 128\n");
		
		System.out.println("pracSeq2(int x):");
		System.out.println("Answer: " + rec.pracSeq2(4) + "   Expecting: 11");
		System.out.println("Answer: " + rec.pracSeq2(5) + "   Expecting: 20\n");
		
		System.out.println("\'car\' is a palindrome?: " + rec.palindrome("car"));
		System.out.println("\'racecar\' is a palindrome?: " + rec.palindrome("racecar"));
		System.out.println("\'hannah\' is a palindrome?: " + rec.palindrome("hannah"));
		System.out.println("\'banana\' is a palindrome?: " + rec.palindrome("banana") + "\n");
		
		rec.starPattern(5);
	}
}
