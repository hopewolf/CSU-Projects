/**
 * @author lburford
 *
 */
public class Tester extends Employee{
	protected int linesOfCodeTestedPerDay;
	public Tester(String nameIn, int idIn, int linesTested) {
		super(nameIn, idIn);
		this.linesOfCodeTestedPerDay = linesTested;
		// TODO Auto-generated constructor stub
	}

	@Override
	public int work() {
		double efficency = Math.random() * 100 + 75;
		int linesWritten = this.linesOfCodeTestedPerDay;
		efficency = efficency / 100;
		linesWritten = (int) (linesWritten * efficency);
		return linesWritten;
	}
	
    public String toString() {
	return this.getName() + " ID: " + this.getId() + " Code Tested: " + this.linesOfCodeTestedPerDay;
    }
	
	public static void main(String args[]) {
		Tester test = new Tester("luke", 1234, 50);
		System.out.println(test.work());
	}

}
