// Species.java
// Author: Luke Burford
// Date:   Sep 2, 2016
// Class:  CS161
// Email:  lburford@rams.colostate.edu

public class Species {	

    // Put the instance variable here.

    String name;
    int pop;
    int growth;

    // Create a Species constructor that takes in a String for its name, an int for
    // its population, and an int for its growth rate per year as a percent.
    /**
     * @param pop can't be greater than 1500 or less than 1
     * if pop is set bellow 1 set it to 1, and if above 1500 set to 1500
     * @param growth rate must be between 1 & 20 percent
     * if growth is below 1 set it to 1 & if growth is above 20 set to 20
     */

    public Species(String specName, int specPop, int specGrowth) {
    	name = specName;
    	if(specPop <= 1)
    		pop = 1;
    	else if(specPop >= 1500)
    		pop = 1500;
    	else
    		pop= specPop;
    	if(specGrowth <= 1)
    		growth = 1;
    	else if(specGrowth >= 20)
    		growth = 20;
    	else
    		growth = specGrowth;
    }
    
    // mergeSpecies adds the populations of the two species, changes the name
    // of the species to the concatenation of the two names, and the growth
    // rate to the maximum of the two growth rates.

    public void mergeSpecies(Species other) {
        this.name = this.name.concat(other.name);
        this.pop += other.pop;
        this.growth += other.growth;
    }

    public String toString(){
        		String output = "";
        		output += "Name of species: " + this.name + "\n";
        		output += "Population: " + this.pop + "\n";
        		output += "Growth Rate: " + this.growth + "\n";
        		
        		return output;
    }

    // Increases the population according to the growth rate of the species, i.e.
    // updates the population instance variable by adding to it the growth rate/100 times the current population.

    public void grow() {
       double growPercent = (double)this.growth/100;
       this.pop += growPercent * this.pop;
    }

    // Returns the population of the species in x years according to its growth rate.

    public int populationInXYears(int x){
    	int pop = this.pop;
    	double growth = (double)this.growth/100.0;
    	for(int i=1;i<=x;i++) {
    		pop = (int)(pop+(pop*(growth)));
    	}
        return pop;
    }

    public static void main(String[] args) {

        // Put simple code here to test the Species class.  It is always a good idea to include
        // a main method in any class you define.

        Species a = new Species("Frog", 100, 10);
        System.out.println(a);

        a.grow();
        System.out.println(a);

        System.out.println("a.populationInXYears(2) returns " + a.populationInXYears(2));

        Species b = new Species("Rabbit", 10, 23);
        a.mergeSpecies(b);
        System.out.println("a.mergeSpecies(b) is " + a);
        
    }
}