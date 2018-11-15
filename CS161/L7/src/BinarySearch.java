/**
 * 
 */

/**
 * assumes the array is sorted; it uses a helper function which receives a range of indices as input, one for the beginning of
 * the range where you are searching for the number, one for the end; it then computes the middle of the range. 
 * If the number in the middle of the range is the number you are looking for, great!
 * 
 * @author lburford
 *
 */
public class BinarySearch implements Searching {

	@Override
	public int search(int[] numbersToSearch, int numberToSearchFor) {
		return binarySearch(numbersToSearch,numberToSearchFor,0,numbersToSearch.length-1);
	}
	
	private  int binarySearch(int[] a, int target, int first, int last) {
		if (first > last) {
			return -1;
		} 
		int mid = (first + last) / 2;
		if (a[mid] == target) {
			return mid;
		} 
		else{
			if (a[mid] < target) {
				return binarySearch(a, target, mid+1, last);
			}
			else {
				return binarySearch(a, target, first, mid-1);
			}
		}
	}

}
