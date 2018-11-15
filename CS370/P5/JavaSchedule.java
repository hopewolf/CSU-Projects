import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

/**
 * @author lburford
 *
 */

public class JavaSchedule  {

	public static void main(String[] args) throws Exception{
		ArrayList<Process> ProcessList = new ArrayList<Process>();
		if(args.length < 2)
			throw new Exception("Missing file input or Quantum input");
		Scanner scan = new Scanner(new File(args[0]));
		while(scan.hasNext()){
			String line = scan.next();
			String[] formated = line.split("[,]");
			if(formated.length != 4){
				scan.close();
				throw new Exception("Format Incorrect");
			}
			Process temp = new Process(Integer.parseInt(formated[0]), Integer.parseInt(formated[1]), Integer.parseInt(formated[2]),  Integer.parseInt(formated[3]));
			ProcessList.add(temp);
		}
		scan.close();
		PrintFCFS(ProcessList);
		Priority(ProcessList);
		int Quantum = Integer.parseInt(args[1]);
		RR(ProcessList, Quantum);
	}

	// prints and calculates FCFS
	public static void PrintFCFS(ArrayList<Process> ProcessList){
		System.out.println("FCFS:\n");
		System.out.println("PID\t\t\tStart\t\t\tEnd");

		Collections.sort(ProcessList, Process.PIDCompare);
		int Time = 0;
		// values to be summed
		double TotalWaitTime = 0.0;
		double TotalTurnaround = 0.0;
		for(int i = 0; i < ProcessList.size(); i++){
			Process temp = ProcessList.get(i);
			while(Time < temp.getArrivalTime()){
				Time++;
			}
			TotalWaitTime += Time - temp.getArrivalTime();
			TotalTurnaround += (Time - temp.getArrivalTime() + temp.getBurstDuration());
			int TempStart = Time;
			int TempFinished = temp.getBurstDuration() + Time;
			InfoPrint(temp, TempStart, TempFinished);
			Time = TempFinished;
		}
		double Throughput = (double)(ProcessList.size()) / (double)Time;
		TotalWaitTime /= ProcessList.size();
		TotalTurnaround /= ProcessList.size();
		SummaryPrint(TotalWaitTime, TotalTurnaround, Throughput);
	}

	//prints and calculates priority
	public static void Priority(ArrayList<Process> ProcessList){
		System.out.println("Priority:");
		System.out.println();
		System.out.println("PID\t\t\tStart\t\t\tEnd");

		double AvgWaitTime = 0;
		double AvgTurnaround = 0;
		double Throughput = 0;
		int Time = 0;
		ArrayList<Process> TempList = new ArrayList<Process>();
		for(int i = 0; i < ProcessList.size(); i++){
			Process temp = ProcessList.get(i).Copy();
			TempList.add(i, temp);
		}
		Process temp = TempList.get(0);
		while(!(TempList.isEmpty())){			
			while(Time < temp.ArrivalTime)
				Time++;				
			Boolean flag = false;
			int TempStart = Time;
			int TempFinished;
			for(int j = 0; j < TempList.size(); j++){		
				Process next = TempList.get(j);
				if(temp == next){
					continue;
				}
				if((next.getArrivalTime() <= Time) && (next.getPriority() < temp.getPriority())){
					temp = next;
					flag = true;
					break;
				}
				if((Time + temp.getBurstDuration()) >= next.getArrivalTime()){	
					int start_difference = next.getArrivalTime() - Time;	
					if(temp.BurstDuration > start_difference){	
						if(temp.getPriority() > next.getPriority()){
							temp.addAmountCompleted(start_difference);
							Time += start_difference;
							TempFinished = Time;
							int remaining_burst = temp.getBurstDuration() - start_difference;
							temp.setRemaining(remaining_burst);
							InfoPrint(temp, TempStart, TempFinished);
							temp = next;
							flag = true;
							break;
						}
					}
				}
			}
			if(flag == false){
				AvgWaitTime += (Time - (temp.getCompleted() + temp.getArrivalTime()));
				TempList.remove(temp);
				Time += temp.getBurstDuration();
				AvgTurnaround += (Time - temp.getArrivalTime());
				TempFinished = Time;
				InfoPrint(temp, TempStart, TempFinished);
				if(TempList.isEmpty())
					break;
				temp = TempList.get(0);
			}
		}
		AvgWaitTime /= ProcessList.size();
		AvgTurnaround /= ProcessList.size();
		Throughput = ProcessList.size() / ((double)Time);
		SummaryPrint(AvgWaitTime, AvgTurnaround, Throughput);
	}

	// prints and calculates RR
	public static void RR(ArrayList<Process> ProcessList, int quantum){
		System.out.println("RR: Quantum = " + quantum);
		System.out.println();
		System.out.println("PID\t\t\tStart\t\t\tEnd");

		double AvgWaitTime = 0;
		double AvgTurnaround = 0;
		double Throughput = 0;
		int Time = 0;
		ArrayList<Process> TempList = new ArrayList<Process>();
		ArrayList<Process> FinalQueue = new ArrayList<Process>();
		for(int i = 0; i < ProcessList.size(); i++){
			Process temp = ProcessList.get(i).Copy();
			TempList.add(i, temp);
		}
		FinalQueue.add(0, TempList.get(0));
		Process temp;
		while(!(TempList.isEmpty())){
			if(FinalQueue.isEmpty()){
				temp = TempList.get(0);
			}
			else{
				temp = FinalQueue.get(0);
			}
			int TempStart = Time;
			while(Time < temp.getArrivalTime()){
				Time++;
			}
			int TempBurst = temp.getBurstDuration();
			if(TempBurst > quantum){
				TempBurst = quantum;
				int TempTimeRemaining = temp.getBurstDuration() - TempBurst;
				temp.setRemaining(TempTimeRemaining);
			}
			else{
				AvgWaitTime += (Time + TempBurst) -  (temp.getArrivalTime() + temp.getOriginal());
				AvgTurnaround += ((Time + TempBurst) - temp.getArrivalTime());
				TempList.remove(temp);
				FinalQueue.remove(temp);
			}
			int TempFinished = Time + TempBurst;
			Time = TempFinished;
			orderFinalQueue(TempList, FinalQueue, Time);
			if(TempList.contains(temp)){
				FinalQueue.remove(temp);
				FinalQueue.add(temp);
			}
			InfoPrint(temp, TempStart, TempFinished);
			if(TempList.isEmpty()){
				break;
			}
		}
		Throughput = ProcessList.size() / (double)Time;
		AvgWaitTime /= ProcessList.size();
		AvgTurnaround /= ProcessList.size();
		SummaryPrint(AvgWaitTime, AvgTurnaround, Throughput);
		return;
	}

	public static void orderFinalQueue(ArrayList<Process> TempList, ArrayList<Process> FinalQueue, int Time){
		for(int i = 0; i < TempList.size(); i++){
			Process temp = TempList.get(i);
			if(FinalQueue.contains(temp))
				continue;
			int temp_arrival = temp.getArrivalTime();
			if(temp_arrival <= Time){
				FinalQueue.add(temp);
			}
		}
	}

	public static void InfoPrint(Process temp, int TempStart, int TempFinished){
		System.out.println(temp.getPID() + "\t\t\t" +  TempStart + "\t\t\t" + TempFinished);
	}

	public static void SummaryPrint(double wait, double turn, double through){
		System.out.printf("\nAverage Waiting Time: %.15f\n", wait);
		System.out.printf("Average TurnAround Time: %.15f\n", turn);
		System.out.printf("Throughput: %.5f\n\n", through);
	}
}
