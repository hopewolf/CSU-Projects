// Palindrome.java
// Class: cs200

public class Palindrome {

	
	private void generatePalindromeStack(String s,int index)
	{
		Stack stack = new Stack();
		
		System.out.println("Input Word: " + s);
		for(int i = index; i<s.length(); i++)
		{
			stack.push(s.charAt(i));
//			System.out.println("Peek at Stack: " + stack.peek());
		}
		
		System.out.print("Palindrome: ");
		while(!(stack.isEmpty())){
			System.out.print(stack.pop());
		}
		System.out.println();
	}
	
	public void generatePalindrome(String s) {
		generatePalindromeStack(s,0);
		System.out.println();
		
	}
	
	public static void main(String[] args) {
	    Palindrome p = new Palindrome();
		p.generatePalindrome("ab");
		p.generatePalindrome("abcd");
		p.generatePalindrome("door");
		p.generatePalindrome("computer");
		
	}

	

}