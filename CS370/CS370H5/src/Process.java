import java.util.Scanner;

public class Process {

	private int PID;
	private int ArrivalTime;
	private int BurstTime;
	private int Priority;
	private int Complete;
	private int FirstBurst;
	
	//constructor
	public Process(String in) {
		Scanner scan = new Scanner(in);
		setPID(scan.nextInt());
		setArrivalTime(scan.nextInt());
		setBurstTime(scan.nextInt());
		setPriority(scan.nextInt());
		scan.close();
	}

	public int getPID() {
		return PID;
	}

	public void setPID(int pID) {
		PID = pID;
	}

	public int getArrivalTime() {
		return ArrivalTime;
	}

	public void setArrivalTime(int arrivalTime) {
		ArrivalTime = arrivalTime;
	}

	public int getBurstTime() {
		return BurstTime;
	}

	public void setBurstTime(int burstTime) {
		BurstTime = burstTime;
	}

	public int getPriority() {
		return Priority;
	}

	public void setPriority(int priority) {
		Priority = priority;
	}

	public int getFirstBurst() {
		return FirstBurst;
	}

	public void setFirstBurst(int firstBurst) {
		FirstBurst = firstBurst;
	}

	public int getComplete() {
		return Complete;
	}

	public void setComplete(int complete) {
		Complete = complete;
	}

}
