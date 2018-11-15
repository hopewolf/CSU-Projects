public class RegExrTest {

	public static void main(String[] args) {
		String currentID = " not (true or error false) @# $% ";
		String ID = "([^\\w]*)(true|false)([)]*)|[\\s](and|or|not)[\\s]";

		Boolean b = currentID.matches(ID);
		System.out.println(b);
	}
}
