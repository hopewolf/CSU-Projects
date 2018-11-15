import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ParseTreeDriver {
	public static void main(String[] args) throws FileNotFoundException, ParseException{
		args = Debug.init(args);
		Scanner scan = new Scanner( new File (args[0]));
        String line;
        // loop through lines in input file
        while ( scan.hasNextLine()){
        	line = scan.nextLine();
        	System.out.println("\nnext line: " + line);
        	TokenIter tokIt = new TokenIter(line);
    		ParseTreeExpr buildTree = new ParseTreeExpr(tokIt);
    		Tree expTree = buildTree.line();
    		
    		System.out.println("Expression Tree:"); 
    		expTree.preorderTraverse();
    		
        }
	}
}
