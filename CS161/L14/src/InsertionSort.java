public class InsertionSort {
	
	public static Student[] sort(Student[] list){
		//copy all elements into a new list
		Student[] sortedList = new Student[list.length];
		for(int i=0; i<list.length; i++){
			sortedList[i] = list[i];
		}
		//now sort the list
		for(int i = 1; i < sortedList.length; i++){
			int j = i;
			Student insert = sortedList[i];
			while(j > 0 && insert.compareTo(sortedList[j-1]) < 0){
				sortedList[j] = sortedList[j-1];
				j--;
			}
			sortedList[j] = insert;
		}
		return sortedList;
	}
}
