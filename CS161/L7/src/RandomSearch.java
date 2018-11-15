import java.util.ArrayList;
import java.util.Random;

/**
 * 
 */

/**
 * Tries five times to locate the number by trying indices randomly.
 * If it doesn't find it in these five attempts, it gives up and says the number is not there.
 * 
 * @author lburford
 */
public class RandomSearch implements Searching{

	@Override
	public int search(int[] numbersToSearch, int numberToSearchFor) {
		Random r = new Random();
		ArrayList<Integer> randoms = new ArrayList<>();
		int index = -1;
		int sLength = numbersToSearch.length-1;
		
		System.out.println("What we're looking for: " + numberToSearchFor);
		for(int i=0;i<5;i++) {
			int tempR = r.nextInt(sLength);
			System.out.println("Current random at " + i +": " + tempR);
			if(randoms.contains(tempR)) {
				System.out.println("Current random was already guessed");
				i--;
			}
			else {
				randoms.add(tempR);
				if(numbersToSearch[tempR] == numberToSearchFor) {
					System.out.println("It found it!");
					index = tempR;
					break;
				}
			}
		}
		return index;
	}
}
