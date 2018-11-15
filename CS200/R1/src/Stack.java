import java.util.ArrayList;
//Stack.java
//Class: cs200


public class Stack {
    private ArrayList<Character> list;
    
    //constructor
    public Stack()
    {
    	list=new ArrayList<Character>();
    }
	
    // returns true if the stack is empty otherwise it returns false.
	public boolean isEmpty()
	{
		return list.isEmpty();
	}
	
	public void push(char toPush)
	{
		list.add(0, toPush);
	}
	
	public char pop()
	{
		char toPop = list.get(0);
		list.remove(0);
		return (Character) toPop;
	}
	
	public char peek()
	{
		char toPop = list.get(0);
		return (Character) toPop;
	}
	
	public static void main(String[] args) {
		Stack s = new Stack();
		System.out.println("Pushing characters: a, b, and c onto the stack.");
		s.push('a');
		s.push('b');
		s.push('c');
		
		System.out.println("Peeking at the to character of the stack (Should be c).");
		System.out.println(s.peek());
		System.out.println("Popping all characters off the stack.");
		while(!s.isEmpty())
		{
			System.out.println(s.pop());
		}
		
		
		

	}

}