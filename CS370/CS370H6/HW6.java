/* @author Luke Burford
 * @date 11/17/17
 * @email lburford@rams.colostate.edu
 */


public class HW6  {

	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		if(args.length != 4){
			System.out.println("Incorrect number of args");
			return;
		}
		int numCons = Integer.parseInt(args[0]);
		if((numCons < 1) || (numCons > 2)){
			System.out.println("Number of consumers can only be 1 or 2");
			return;
		}
		int buffSize = Integer.parseInt(args[1]);
		int ItemsNeedToProduce = Integer.parseInt(args[2]);
		long maxWaitTime = Long.parseLong(args[3]);			

		CirBuffer cirBuff = new CirBuffer(buffSize);
		Thread prodThread = new Thread(new Prod(buffSize, maxWaitTime, ItemsNeedToProduce, cirBuff));
		prodThread.start();
		Thread consThread1 = new Thread(new Cons(1, buffSize, maxWaitTime, cirBuff));
		consThread1.start();
		
		if(numCons == 2){
			Thread consThread2 = new Thread(new Cons(2, buffSize, maxWaitTime, cirBuff));
			consThread2.start();
			try {
				consThread2.join();
			} 
			catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		try {
			prodThread.join();
		} 
		catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			consThread1.join();
		} 
		catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
