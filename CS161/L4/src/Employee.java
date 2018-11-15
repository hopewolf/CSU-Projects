/**
 * @author lburford
 *
 */
public abstract class Employee {

    private String name;
    private int id;
    
    /**
     * 
     * @return name
     */
    public String getName() {
    	return this.name;
    }
    
    /**
     * 
     * @return id
     */
    public int getId() {
    	return this.id;
    }
    
    /**
     * sets name
     * @param nameIn
     */
    public void setName(String nameIn) {
    	this.name = nameIn;
    }
    
    /**
     * sets id
     * @param idIn
     */
    public void setId(int idIn) {
    	this.id = idIn;
    }
    
    /**
     * 
     * @param nameIn
     * @param idIn
     */
    public Employee(String nameIn, int idIn) {
    	this.setName(nameIn);
    	this.setId(idIn);
    }
    
    public abstract int work();

    public String toString() {
	return name + " ID: " + id;
    } 

    public boolean equals(Object other) {
	if (other instanceof Employee && other != null) {
	    return (name.equals(((Employee)other).name) && id == ((Employee)other).id);
	}
	return false;
    }
}
