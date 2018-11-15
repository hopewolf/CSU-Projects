import java.util.ArrayList;

public class Stack implements StackIF {

	// Use opStack to push and pop operators
	private ArrayList<String> opStack;
    
	// initialize opStack
        public Stack(){
        	opStack = new ArrayList<String>();
        }


	public void push(String op){
		Debug.printf(": %s", op);
		this.opStack.add(opStack.size(), op);
	}


	public String pop() throws StackException{
	    Debug.HERE();
	    String op = null;
	    if(opStack.isEmpty())
	    	throw new StackException("Popping from empty stack!");
	    op = opStack.get(opStack.size()-1);
	    opStack.remove(opStack.size()-1);
	    Debug.printf("Popped and removed op: %s", op);
	    return op;
	}


	public String peek() throws StackException{
	    Debug.HERE();
	    String op = null;
	    if(opStack.isEmpty())
	    	throw new StackException("Popping from empty stack!");
	    op = opStack.get(opStack.size()-1);
	    Debug.printf(": %s", op);
	    return op;
	}

	public boolean isEmpty() {
	    if(opStack.isEmpty())
	    	return true;
	    else
	    	return false;
	}

        public static void main(String[] args) throws StackException{
	 args = Debug.init(args); 
    	 Stack s = new Stack();
    	 s.push("1");
    	 s.push("2");
    	 System.out.println("s peek: " + s.peek());
    	 s.pop();
    	 System.out.println("s peek: " + s.peek());
    	 s.pop();
    	 System.out.println("s isEmpty: " + s.isEmpty());
    	 System.out.println("Exception test...");
    	 // exception
    	  s.pop();
    }
}
