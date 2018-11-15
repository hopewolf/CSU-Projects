/* @author Luke Burford
 * @date 11/17/17
 * @email lburford@rams.colostate.edu
 */

public class CirBuffer {
	public int[] cirBuff;
	public int size;
	public int prodPos;
	public int consPos;


	public CirBuffer(int size)
	{
		cirBuff = new int[size +1];
		this.size = size;	
		this.prodPos = 0;
		this.consPos = 0;

	}

	public synchronized int pushItem(int newItem)
	{
		if(((this.prodPos + 1) % this.size) == this.consPos){		
			this.notifyAll();
			return -1;
		}
		this.cirBuff[this.prodPos] = newItem;
		int out = prodPos;
		this.prodPos = (++this.prodPos) % size;
		this.notifyAll();
		return out;
	}

	public synchronized int[] popItem()
	{
		int[] out = new int[2];
		if(this.consPos == this.prodPos){
			out[0] = -1;
			out[1] = -1;
			this.notifyAll();
			return out;
		}
		out[0] = this.cirBuff[this.consPos];
		out[1] = this.consPos;
		this.consPos = (++this.consPos) % size;
		this.notifyAll();
		return out;
	}
}
