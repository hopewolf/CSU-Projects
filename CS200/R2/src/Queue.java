
public class Queue implements QueueIF{
	private LinkedList queueLL;
	boolean debug;
	
	public Queue(boolean debug){
		queueLL = new LinkedList();
		this.debug = debug;
	}
	
	@Override
	public void enqueue(Object token) {
		queueLL.add(token);
		
	}

	@Override
	public Object dequeue() throws QueueException {
		Object output = null;
		if(this.size()>0) 
		{
			output = queueLL.get(0);
			queueLL.remove(0);
		}
		else
			throw new QueueException(
					"Can't dequeue, queue is empty!");
		return output;
	}

	@Override
	public int size() {
		return queueLL.size();
	}
	
	public static void main(String[] args) throws QueueException{
		Queue intQueue = new Queue(true);
		System.out.println("create Queue of Integers 12 34 56");
		intQueue.enqueue(new Integer(12));	
		intQueue.enqueue(new Integer(34));
		intQueue.enqueue(new Integer(56));
				
		if(intQueue.debug)
			System.out.println("intQueue: " + intQueue.queueLL.toString());	
		Object o12 = intQueue.dequeue();
		if(intQueue.debug)
			System.out.println("o12: " + o12);		
		Object o34 = intQueue.dequeue();
		if(intQueue.debug){
			System.out.println("o34: " + o34);		
			System.out.println("intQueue: " + intQueue.queueLL.toString() + 
				           ", size: " + intQueue.size());
		}
		intQueue.dequeue();
		// test Exception handling
		intQueue.dequeue();
	}
}