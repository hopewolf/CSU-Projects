import java.util.ArrayList;

/**
 * @author lburford
 *
 */
public class Project {
	private int linesOfCode; // lines of code required to do project
	private int linesOfCodeWritten; // lines of code written
	private int linesOfCodeTested; // lines of code tested
	private int duration; // number of days to do project
	ArrayList<Employee> employees = new ArrayList<Employee>();

	public int getLinesOfCode() {
		return linesOfCode;
	}

	public void setLinesOfCode(int linesOfCode) {
		this.linesOfCode = linesOfCode;
	}

	public int getLinesOfCodeTested() {
		return linesOfCodeTested;
	}

	public void setLinesOfCodeTested(int linesOfCodeTested) {
		this.linesOfCodeTested = linesOfCodeTested;
	}

	public int getLinesOfCodeWritten() {
		return linesOfCodeWritten;
	}

	public void setLinesOfCodeWritten(int linesOfCodeWritten) {
		this.linesOfCodeWritten = linesOfCodeWritten;
	}

	public int getDuration() {
		return duration;
	}

	public void setDuration(int duration) {
		this.duration = duration;
	}

	/**
	 * 
	 * @param codeNeeded
	 * @param duration
	 */
	public Project(int codeNeeded, int duration) {
		this.setLinesOfCode(codeNeeded);
		this.setDuration(duration);
	}

	/**
	 * 
	 * @param other
	 */
	public void addEmployee(Employee other) {
		this.employees.add(other);
	}

	public int doProject() {
		int duration = this.getDuration();
		int timeTaken = 0;
		int projectSize = this.getLinesOfCode();
		int codeWritten = this.getLinesOfCodeWritten();
		int codeTested = this.getLinesOfCodeTested();

		// 1 loop = 1 day, everyone writes some code a day
		// if all code needed has been written AND tested, break and return days over time
		for(int i=0; i<=duration;i++) {
			if(!(codeWritten > projectSize && codeTested > projectSize)) {
				for(int j=0; j<this.employees.size();j++) {
					if(this.employees.get(j) instanceof Programmer)
						codeWritten += this.employees.get(j).work();
					else if(this.employees.get(j) instanceof Tester)
						codeTested += this.employees.get(j).work();
				}
				if(i == duration)
					i--;
			}
			else
				break;
			timeTaken++;
		}
		return timeTaken - duration; //number of days project took beyond alloted time
	}
	
	public String toString() {
		String out = "";
		
		out += "Project length: " + this.getLinesOfCode() + "\n";
		out += "Project duration: " + this.getDuration() + "\n";
		
		for(int i =0; i < this.employees.size();i++) {
				out += this.employees.get(i).toString() +"\n";
		}
		
		return out;
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Project P1 = new Project(500, 15);
		Programmer ep1 = new Programmer("luke", 1, 50);
		P1.employees.add(ep1);
		Tester ep2 = new Tester("dan", 2, 50);
		P1.employees.add(ep2);
		Programmer ep3 = new Programmer("steve", 3, 50);
		P1.employees.add(ep3);
		Tester ep4 = new Tester("john", 4, 50);
		P1.employees.add(ep4);
		Programmer ep5 = new Programmer("jake", 5, 50);
		P1.employees.add(ep5);
		Tester ep6 = new Tester("jane", 6, 50);
		P1.employees.add(ep6);
		Programmer ep7 = new Programmer("lizz", 7, 50);
		P1.employees.add(ep7);
		Tester ep8 = new Tester("kathi", 8, 50);
		P1.employees.add(ep8);
		System.out.println("Days taken: " + P1.doProject() +"\n");
		System.out.println("Project info:");
		System.out.println(P1.toString());

	}

}
