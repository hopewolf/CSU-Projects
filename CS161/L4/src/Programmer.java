/**
 * @author lburford
 *
 */
public class Programmer extends Employee {
	protected int linesOfCodePerDay;
	
	public Programmer(String nameIn, int idIn, int linesOfCode) {
		super(nameIn, idIn);
		this.linesOfCodePerDay = linesOfCode;
	}
	
	/**
	 * 
	 * @return number of lines of code written on a given day,
	 * which is a random number between 50% and 150%
	 */
	@Override
	public int work() {
		double efficency = Math.random() * 100 + 50;
		int linesWritten = this.linesOfCodePerDay;
		efficency = efficency / 100;
		linesWritten = (int) (linesWritten * efficency);
		return linesWritten;
	}
	
    public String toString() {
	return this.getName() + " ID: " + this.getId() + " Code Written: " + this.linesOfCodePerDay;
    } 
	
	public static void main(String args[]) {
		Programmer test = new Programmer("luke", 1234, 50);
		System.out.println(test.work());
		System.out.println(test.toString());
	}

}
