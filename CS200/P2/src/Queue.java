import java.util.ArrayList;


public class Queue implements QueueIF {

	// maintains expression queue
	private ArrayList<String> expQueue;
	
	// constructor
	public Queue(){
		expQueue = new ArrayList<String>();
	}
	
	/* enqueue token at the end of expQueue
	 */
	public void enqueue(String token){
		Debug.printf(": %s", token);
		this.expQueue.add(expQueue.size(), token);
	}
	
	public String dequeue() throws QueueException{
		String token = null;
		if(size() == 0)
			throw new QueueException();
		token = this.expQueue.get(expQueue.size()-1);
		this.expQueue.remove(expQueue.size()-1);
		Debug.printf("Dequeued token: %s", token);
		return token;
	}

	// returns size (#elements) of the queue
	public int size(){
	    return this.expQueue.size();
	}
	
	public String toString(){
		return expQueue.toString();
	}
	
        public static void main(String[] args) throws QueueException{
    	 args = Debug.init(args);
    	 Queue q = new Queue();
    	 q.enqueue("We all live in a");
    	 q.enqueue("yyyyello");
    	 q.enqueue("soup machine");
    	 System.out.println(q.expQueue);
    	 q.dequeue();
    	 System.out.println("q size: " + q.size());
    	 System.out.println(q.expQueue);
    	 q.dequeue();
    	 q.dequeue();
    	 System.out.println("q size: " + q.size());
    	 System.out.println(q.expQueue);
         // exception
    	  q.dequeue();
    }
}
