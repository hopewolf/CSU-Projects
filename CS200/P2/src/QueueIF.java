
public interface QueueIF {

	//enqueue String token at the end of the Queue
	public void enqueue(String token);
	
	/* dequeue token from the front of the Queue
	 * If Queue empty, throw QueueException
	 */ 
	public String dequeue() throws QueueException;
	
	// returns size (#elements) of the queue
	public int size();	
}
