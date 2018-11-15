

public class LinkedBookList {

	private BookNode head;
	private int size;

	public LinkedBookList(){
		head = null;
		size = 0;
	}

	public int size(){
		return size;
	}

	//IMPLEMENT -- adds a book to the end of the linked list
	public void add(Book b){
		BookNode current = this.head;
		BookNode toadd = new BookNode(b,null);
		if(this.head == null) {
				current = toadd;
		}
	}

	//IMPLEMENT -- adds a book at the specific index, or at the end if index is greater than size
	public void add(Book b, int index){
		return;
	}

	//IMPLEMENT -- removes a book and returns it, or returns null if it is not present
	public Book remove(Book b){
		return null;
	}

	//IMPLEMENT -- removes a book at a specific indexand returns it, 
	//or returns null if it is not present
	public Book remove(int index){

		return null;
	}

	//IMPLEMENT -- returns the total number of pages in the linked list
	public int totalPages(){
		return 0;
	}

	public String toString() {
		BookNode current = head;
		String res = "";
		while(current.getNext() != null) {
			res += current.getBook().getTitle() + "\n";
			res += current.getBook().getAuthor() + "\n";
			res += current.getBook().getNumPages() + "\n";
		}

		return res;
	}

}
