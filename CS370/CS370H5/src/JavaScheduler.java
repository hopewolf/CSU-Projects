import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
/**
 * @author lburford
 *
 */
public class JavaScheduler {
	// Instance variables
	private static ArrayList<Process> proc = new ArrayList<Process>();
	private static int Quantum;
	private static int WaitingTime;
	private static int TurnaroundTime;
	private static int Throughput;
	
	/**
	 * @param args
	 * @throws FileNotFoundException 
	 */
	public static void main(String[] args) throws FileNotFoundException {
		Scanner scan = new Scanner(new File(args[0]));
		Quantum = Integer.valueOf(args[1]);
		String line = "";
		Process current;
		// get list of processes
        while(scan.hasNextLine()) {
        	line = scan.nextLine();
        	line = line.replace(',', ' ');
        	current = new Process(line);
        	proc.add(current);
        }
        //FCFS
        System.out.println("FCFS:\n");
        System.out.println("Pid   Start   End");
        FCFS();
        System.out.println("\nAverage Waiting Time: " + WaitingTime);
        System.out.println("Average TurnAround Time: " + TurnaroundTime);
        System.out.println("Throughput: " + Throughput + "\n");
        WaitingTime = 0; TurnaroundTime = 0; Throughput = 0;
        //Priority
        System.out.println("Priority:\n");
        System.out.println("Pid   Start   End");
        Priority();
        System.out.println("\nAverage Waiting Time: " + WaitingTime);
        System.out.println("Average TurnAround Time: " + TurnaroundTime);
        System.out.println("Throughput: " + Throughput + "\n");
        WaitingTime = 0; TurnaroundTime = 0; Throughput = 0;
       //RR
        System.out.println("RR: Quantum = " + Quantum + "\n");
        System.out.println("Pid   Start   End");
        RR();
        System.out.println("\nAverage Waiting Time: " + WaitingTime);
        System.out.println("Average TurnAround Time: " + TurnaroundTime);
        System.out.println("Throughput: " + Throughput);
        WaitingTime = 0; TurnaroundTime = 0; Throughput = 0;
        scan.close();
	}
	
	public static void FCFS() {
		// arraylist that i can remove elements that are executing or done
		ArrayList<Process> curr = new ArrayList<Process>();
		curr.addAll(proc);
		// loop for all jobs
		for(int i = 0; i < proc.size(); ++i) {
			// finds first arrival time
			int arrived = proc.get(i).getArrivalTime();
			Process currP = proc.get(i);
			for(int j = 0; j < curr.size(); ++j) {
				if(curr.get(j).getArrivalTime() < currP.getArrivalTime()) {
					System.out.println("currP: " + currP.getPID());
					arrived = proc.get(j).getArrivalTime();
					currP = proc.get(j);
				}
			}
			curr.remove(currP); // remove the proc were about to exec
			currP.setWaitTime(WaitingTime); // set how long it took to get to it
			System.out.print(currP.getPID() + "   " + WaitingTime + "   ");
			WaitingTime += currP.getBurstTime(); // add burst to wait time
			System.out.println(WaitingTime);
		}
	}
	
	
	public static void Priority() {
		
	}
	
	public static void RR() {
		
	}

}
