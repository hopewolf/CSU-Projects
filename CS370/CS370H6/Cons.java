/* @author Luke Burford
 * @date 11/17/17
 * @email lburford@rams.colostate.edu
 */

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;

public class Cons implements Runnable {
	
	/*--- Instance Variables ---*/
	int consTotal;
	int buffSize;
	long maxWaitTime;
	CirBuffer cirBuff;
	int sumConsumed;
	int emptyBuffCyc;
	Random rand = new Random();

	/* Constructor */
	public Cons(int consTotal, int buffSize, long maxWaitTime, CirBuffer cirBuff)
	{
		this.consTotal = consTotal;
		this.buffSize = buffSize;
		this.maxWaitTime = maxWaitTime;
		this.cirBuff = cirBuff;
		this.sumConsumed = 0;
		this.emptyBuffCyc = 0;
	}

	/* overriding the Runnable run method */
	@Override
	public void run() 
	{
		// TODO Auto-generated method stub
		while(emptyBuffCyc != 15){ // 15 times the max wait
			// use runnable synchronized function
			synchronized (cirBuff){
				try {
					long randGenWait = -1;
					while (randGenWait < 0){
						randGenWait = (rand.nextLong() % maxWaitTime);
					}
					cirBuff.wait(randGenWait);
					int[] consumed = cirBuff.popItem();
					if(consumed[0] != -1){
						emptyBuffCyc = 0;
						sumConsumed += consumed[0];
						if(consumed[1] ==11)
							System.out.println("------------------------------------------------------------------------------------------------------------------------");
						System.out.println("Consumer " + consTotal + ": Removed " + consumed[0] + " from location: " + consumed[1] + " at Time: " 
								+ (new SimpleDateFormat("yyyy/MM/dd HH:mm:ss:SSSSS").format(new Date())));
					}
					else
						++emptyBuffCyc;
				}
				catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		System.out.println("Consumer " + consTotal + " Unable to consume, buffer empty, at Time: " 
				+  (new SimpleDateFormat("yyyy/MM/dd HH:mm:ss:SSSSS").format(new Date())));
		//finished consuming
		System.out.println("Consumer " + consTotal + ": exiting after waiting for " + emptyBuffCyc + " Sum of numbers consumed: " + sumConsumed);		
	}
}
