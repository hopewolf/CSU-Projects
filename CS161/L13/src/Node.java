
public class Node {
    private Object item;
    private Node next;

    public Node(Object item) {
        this.item = item;
        this.next = null;
    }
    public Node(Object item, Node next) {
        this.item = item;
        this.next = next;
    }
    public void setNext(Node nextNode) {
		next = nextNode;
    }
    public Node getNext() {
    	return next;
    }
    public Object getItem() {
    	return item;
    }
    public void setItem(Object item){
    	this.item = item;
    }
    public String toString(){
    	return item.toString();
    }
    
    public static void main(String[] args) {
    	
    }
}