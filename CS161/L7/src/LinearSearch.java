/**
 * 
 */

/**
 * @author lburford
 * goes through the array from the start and returns the index
 * of the first occurrence of the number that you are searching 
 * for if it exists in the array, otherwise returns -1.
 */
public class LinearSearch implements Searching{

	/**
	 * @param numbersToSearch, numberToSearchFor
	 * @return index of numberToSearchFor
	 */
	@Override
	public int search(int[] numbersToSearch, int numberToSearchFor) {
		int index = -1;
		for(int i=0; i<numbersToSearch.length;i++) {
			if(numbersToSearch[i] == numberToSearchFor) {
				index = i;
				break;
			}
		}
		return index;
	}
}
