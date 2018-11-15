/* @author Luke Burford
 * @date 11/17/17
 * @email lburford@rams.colostate.edu
 */

import java.util.Date;
import java.text.SimpleDateFormat;
import java.util.Random;

public class Prod implements Runnable {
	
	/*--- Instance Variables ---*/
	int buffSize;
	long maxWaitTime;
	int toBeProduced;
	CirBuffer cirBuff;
	int sumProduced;
	int count = 0;
	Random rand = new Random();

	/* Constructor */
	public Prod(int buffSize, long maxWaitTime, int toBeProduced, CirBuffer cirBuff)
	{
		this.buffSize = buffSize;
		this.maxWaitTime = maxWaitTime;
		this.toBeProduced = toBeProduced;
		this.cirBuff = cirBuff;
		this.sumProduced = 0;
	}

	/* overriding the Runnable run method */
	@Override
	public void run() 
	{
		// TODO Auto-generated method stub
		while(count != toBeProduced){
			synchronized(cirBuff){
				try {
					long randGenWait = -1;
					while (randGenWait < 0){
						randGenWait = (rand.nextLong() % maxWaitTime);
					}
					int newRand = rand.nextInt(100);
					int pos = cirBuff.pushItem(newRand);
					if(pos != -1){					
						count++;
						sumProduced += newRand;
						System.out.println("Producer: Inserted integer " + newRand + " at Location " + pos 
								+ " at instant: " +  (new SimpleDateFormat("yyyy/MM/dd HH:mm:ss:SSSSS").format(new Date())));
					}
					else
						System.out.println("Producer: Unable to insert, buffer full, at instant: " 
								+ (new SimpleDateFormat("yyyy/MM/dd HH:mm:ss:SSSSS").format(new Date())));
					cirBuff.wait(randGenWait);
				}
				catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		//finished consuming
		System.out.println("Producer: Done producing " + count + " items. Sum of numbers generated: " + sumProduced);
	}
}
