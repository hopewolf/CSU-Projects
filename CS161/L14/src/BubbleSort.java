public class BubbleSort {
	
	public static Student[] sort(Student[] list){
		//copy all elements into a new list
		Student[] sortedList = new Student[list.length];
		for(int i=0; i<list.length; i++){
			sortedList[i] = list[i];
		}
		//now sort the list
		int i, j;
		for(i = 0; i < sortedList.length; i++){
			for(j = 1; j < sortedList.length - i; j++){
				if(sortedList[j-1].compareTo(sortedList[j]) > 0){
					Student sw = sortedList[j-1];
					sortedList[j-1] = sortedList[j];
					sortedList[j] = sw;
				}
			}
		}
		return sortedList;
	}

}
