
public class IdVal extends Key<String> {
	private Boolean val;
	public IdVal(String id, Boolean val){
		super(id);
		this.val = val;
	}
	public Boolean getVal(){
		return val;
	}
	public String toString(){
		return "[" + getKey() + ": " + val+ "]"; 
	}	
}
