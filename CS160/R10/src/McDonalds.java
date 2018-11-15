// R10 Recitation Solution
// Author: Chris Wilcox
// Date:   2/27/2015
// Class:  CS160
// Email:  wilcox@cs.colostate.edu

public class McDonalds {

    // Enumerations
    public enum SodaFlavor { Nothing, Coke, Pepsi, Sprite };
    public enum SodaSize { Nothing, Small, Medium, Large };
    public enum Sandwich { Nothing, BigMac, QuarterPounder, FiletOfFish };
    public enum SideOrder { Nothing, FrenchFries, OnionRings };
    
    // Instance variables
    private SodaFlavor sodaFlavor;
    private SodaSize sodaSize;
    private Sandwich sandwich;
    private SideOrder side;
    
    // Constructor
    public McDonalds() {
        sodaFlavor = SodaFlavor.Nothing;
        sodaSize = SodaSize.Nothing;
        sandwich = Sandwich.Nothing;
        side = SideOrder.Nothing;
    }

    // Entry point with test code
    public static void main(String[] args) {
        
        McDonalds myMeal = new McDonalds();
        myMeal.chooseDrink(SodaFlavor.Coke, SodaSize.Medium);
        myMeal.chooseMeal(Sandwich.QuarterPounder, SideOrder.OnionRings);
        System.out.println(myMeal.toString());

        McDonalds specialMeal = new McDonalds();
        specialMeal.chooseDrink(SodaFlavor.Coke, SodaSize.Medium);
        specialMeal.chooseMeal(Sandwich.BigMac, SideOrder.FrenchFries);
        System.out.println(specialMeal.toString());

        McDonalds noDrink = new McDonalds();
        noDrink.chooseDrink(SodaFlavor.Nothing, SodaSize.Nothing);
        noDrink.chooseMeal(Sandwich.FiletOfFish, SideOrder.FrenchFries);
        System.out.println(noDrink.toString());
    }

    // Setters
    public void chooseDrink(SodaFlavor flavor, SodaSize size) {
        // Implement this method!!!
    	 sodaFlavor = flavor;
    	 sodaSize = size ;
    }
    public void chooseMeal(Sandwich type, SideOrder order) {
        // Implement this method!!!
    	sandwich = type;
    	side = order;
    }
    
    // Print order
    public String toString() {
        
        // Compute cost
        double cost = calculateCost();
        
        // Create output
        String s;

        // Add code to build string!!!
        s = "Drink Flavor: " + sodaFlavor;
        s += "\n Drink Size: " + sodaSize;
        s += "\n Sandwich: " + sandwich;
        s += "\n Side: " + side;
        s += "\n Cost: " + cost;
        s += "\n";
        return s;
    }
    
    // Calculate cost
    public double calculateCost() {

        double cost = 0.0;

        // Add special meal!!!
        if((sodaSize == sodaSize.Medium) && (sandwich == Sandwich.BigMac) && (side == SideOrder.FrenchFries)){
        	cost += 4.39;
        	return cost;
        }
        // Compute soda cost
        switch (sodaSize) {
        case Small:  cost += 0.79; break;
        case Medium: cost += 0.99; break;
        case Large:  cost += 1.19; break;
        default:
        }
        
        // Compute sandwich cost
        switch (sandwich) {
        case BigMac: cost += 3.79;
        case QuarterPounder: cost += 4.09;
        case FiletOfFish: cost += 2.89;
        default:
        }

        // Compute side cost
        if (side != SideOrder.Nothing) {
            cost += 1.59;
        }
        return cost;
    }
}

