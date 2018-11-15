
public class Animal {
	
	private String name;
	private int topSpeed;
	
	//create the getters and setters for the instance variables
        //there is a shortcut by hovering over the variable names
	
	// For the setter associated with topSpeed make sure the values are between 0 and 70
    	// Raise an exception if it is not within these values.
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getTopSpeed() {
		return topSpeed;
	}

	public void setTopSpeed(int topSpeed) throws Exception {
		if(topSpeed >= 0 && topSpeed <= 70) {
			this.topSpeed = topSpeed;
		}
		else
			throw new Exception("Out of bounds (0,70)");
	}
	
	//create a constructor that takes in a String for the name and an int for the topSpeed
		//use only the setters initialize the instance variables
	
	public Animal(String inName, int inTopSpeed) {
		setName(inName);
		try {
		setTopSpeed(inTopSpeed);
		} catch(Exception e){
			if(inTopSpeed > 70)
				inTopSpeed = 70;
			if(inTopSpeed < 0)
				inTopSpeed = 0;
		}
	}
	
    //create an equals(Object other) method that returns True if the two Animal objects have 
		//top speeds that are within 2 mph of each other
	
	public boolean equals(Object other) {
		if(other instanceof Animal) {
			Animal myAnimal = (Animal) other;
			int delta = Math.abs(this.getTopSpeed() - myAnimal.getTopSpeed()); 
			if(delta <= 2 && delta >= 0) {
				return true;
			}
			else return false;
		}
		else return false;
	}
	
	// Create a toString method
	// Formatting of the returned String should follow this example:
	// Name: elephant     Top Speed: 25
	
	public String toString() {
		String output = "";
		output += "Name: " + this.getName() + " ";
		output += "Top Speed: " + this.getTopSpeed();
		return output;
	}
	
}
