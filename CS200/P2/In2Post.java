import java.util.ArrayList;
import java.util.Scanner;

public class In2Post {
	// Use expQueue to create the postfix expression
	private Queue expQueue;

	// opStack maintains operators while building expQueue
	private Stack opStack;
	
	// evalStack is used for evaluation of the postfix expression in expQueue
	private Stack evalStack;
	
	// when scanning a next Token, put it in nextToken (see convertIn2Post())
	private String nextToken;

	// Iterator tokIt gets the input line in the constructor and produces tokens 
	private TokenIter tokIt;
	
	// provided, used in TestServer Codes, don't change
	public Queue getExpQueue(){
		return expQueue;
	}
    
	
	// constructor
	// initialize tokIt, opStack, expQueue and evalStack 
	public In2Post(String line){
		// show line with white space
	        System.out.println("input line: [" + line + "]");
	}

	// convert infix to postfix using the algorithm discussed in 
	// lecture L3: queues
	public void convertIn2Post() throws StackException, QueueException{
		Debug.HERE();
		//while(tokIt.hasNext()){
		//  nextToken = tokIt.next();
		//  if operator ...
		//  else  operand
		//  end if operator
		//} end while tokIt.hasnext()
		// empty opStack into ExpQueue
	}

	/* evaluate the postfix expression in expQueue
	 * using evalStack and returning the final result value
	 * when encountering an operand, push it on evalStack
	 * when encountering an n-ary operator, 
	 *    pop n values off the evalStack (n=2: right, then left)
	 *    perform the operation, and push the result on the evalStack
	 * at the end of the expression,
	 *    pop the result off the stack and return it 
	 *    
	 * expQueue is either empty, or contains a valid postfix expression     
	 */
	public String evalPost() throws QueueException, StackException{
		Debug.HERE();
		// while(expQueue.size()>0){
		//}
                //if(evalStack.isEmpty()) return "";
                //else return evalStack.pop();
                return "";
	}

	public static void main(String[] args) throws StackException, QueueException{
		// exercise expressions
    	        args = Debug.init(args);
    	
		String line = "";
		In2Post ex0 = new In2Post(line);
		ex0.convertIn2Post();
		System.out.println("postfix: " + ex0.expQueue);
                System.out.println("result: " + ex0.evalPost());
        
		line = "true";
		In2Post ex1 = new In2Post(line);
		ex1.convertIn2Post();
		System.out.println("postfix: " + ex1.expQueue);
                System.out.println("result: " + ex1.evalPost());
        
		line = " (true or  (false))  ";
		In2Post ex2 = new In2Post(line);
		ex2.convertIn2Post();
		System.out.println("postfix: " + ex2.expQueue);
                System.out.println("result: " + ex2.evalPost());
        
		line = " true and false  ";
		In2Post ex3 = new In2Post(line);
		ex3.convertIn2Post();
		System.out.println("postfix: " + ex3.expQueue);
                System.out.println("result: " + ex3.evalPost());
        
		line = "not not true";
		In2Post ex4 = new In2Post(line);
		ex4.convertIn2Post();
		System.out.println("postfix: " + ex4.expQueue);
                System.out.println("result: " + ex4.evalPost());
         
		line = "true and (true or false)";	
		In2Post ex5 = new In2Post(line);
		ex5.convertIn2Post();
		System.out.println("postfix: " + ex5.expQueue);
                System.out.println("result: " + ex5.evalPost());

	}
}
