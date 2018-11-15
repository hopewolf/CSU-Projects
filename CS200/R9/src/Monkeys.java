import java.util.Arrays;


public class Monkeys {

	private long count;
	private int n; 
	private int[] array;
	
	public Monkeys(int n){
		this.n =  n;
		this.count = 0;
		makeArray();
	}
	
	private void swap(int[] array, int i, int j){
		int t = array[i];
		array[i]=array[j];
		array[j]=t;
	}
	
	public void monkeys(int [] array, int i, int j){
		count++;  // count method calls
		if(i<j) {
			// size 2 base case 
			if(j-i==1){
				if (array[i] > array[j]) swap(array,i,j);
			}
			else {
				int third = (j-i+1)/3;
				monkeys(array, i, j-third); // 2/3 n size problem
				monkeys(array, i+third, j); // 2/3 n size problem
				monkeys(array, i, j-third); // 2/3 n size problem
			}
		}
	}

	public void monkeys() {
		monkeys(array, 0, array.length-1);
	} 
	
	public void makeArray(){
		this.array = new int[n];
		for(int i=0; i<n; i++)
			array[i] = n-i;
	}
	
	public String toString(){
		String r = "n: " + n + ", count: " + count ;
		if(n<50)
			r += "\narray: "+Arrays.toString(array);
		return r;
	}
	
	public static void doTheMonkey(int n){
		Monkeys m = new Monkeys(n);
		System.out.println(m);		
		m.monkeys();
		System.out.println(m);		
	}
	
	public static void main(String[] args){
		// Do you see what it does? How it does it?
		// How complex does it get?
        for(int i = 1; i<6; i+=1)
        	doTheMonkey(i);

		// How complex does it get?
        for(int i = 100; i<600; i+=100)
        	doTheMonkey(i);
	}
}
