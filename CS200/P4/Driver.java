import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Driver {
	public static void main(String[] args) throws FileNotFoundException, BSTException, ParseException{
		Scanner scan = new Scanner( new File (args[0]));
        String line;
        boolean dump = false;
        if(args.length > 1)
        	dump = true;
        // initialize symTab
        BST symbolTable = new BST();
        // loop through lines in input file
    	System.out.println("EQUATION DRIVER");
    	while ( scan.hasNextLine()){
        	line = scan.nextLine();
        	System.out.println("\nnext line: " + line);
        	try{
        	TokenIter tokIt = new TokenIter(line);
        	Equation nextEq = new Equation(tokIt);
    		IdVal res = nextEq.line(symbolTable);
    	    System.out.println("result: " + res);
        	} catch (ParseException PE) {
        		System.out.println("Parse exception: " + PE.getMessage());
        	} catch (BSTException PE) {
    		System.out.println("BST exception: " + PE.getMessage());
    	    } 
	
    	    if(dump){
    	     System.out.println("BST");
    		 symbolTable.preorderTraverse();
    	    }
        }
	}
}
