import java.util.Comparator;

/**
 * @author lburford
 *
 */

public class Process {
	//instance vars
	int PID;
	int ArrivalTime;
	int BurstDuration;
	int Priority;
	int Completed;
	int StartBurst;
	
	public static Comparator<Process> PIDCompare = new Comparator<Process>() {
		 public int compare(Process temp1, Process temp2){
				if(temp1.getArrivalTime() == temp2.getArrivalTime()){
					int pid1 = temp1.getPID();
					int pid2 = temp2.getPID();
						return pid1 < pid2 ? -1 : 1;
					}
				return temp1.getArrivalTime() < temp2.getArrivalTime() ? -1 : 1;
	    }
};
	
	public Process(int PIDIn, int ArrivalTimeIn, int BurstDurationIn, int PriorityIn){
		this.PID = PIDIn;
		this.ArrivalTime = ArrivalTimeIn;
		this.BurstDuration = BurstDurationIn;
		this.StartBurst = BurstDurationIn;
		this.Priority = PriorityIn;
		this.Completed = 0;
	}
	
	public Process Copy(){
		Process temp = new Process(this.getPID(), this.getArrivalTime(), this.getBurstDuration(), this.getPriority());
		return temp;
	}
	
	public int getCompleted(){
		return this.Completed;
	}
	public void addAmountCompleted(int amount){
		this.Completed += amount;
	}
	
	public int getPID(){
		return this.PID;
	}
	public int getArrivalTime(){
		return this.ArrivalTime;
	}
	public int getBurstDuration(){
		return this.BurstDuration;
	}
	public int getPriority(){
		return this.Priority;
	}
	public void setRemaining(int new_duration){
		this.BurstDuration = new_duration;
	}
	public int getOriginal(){
		return this.StartBurst;
	}
	
}
	
	
	
	
	

