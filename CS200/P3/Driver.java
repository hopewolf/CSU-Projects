import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Driver {
	public static void main(String[] args) throws FileNotFoundException, ParseException{
		args = Debug.init(args); 
		Scanner scan = new Scanner( new File (args[0]));
        String line;
        System.out.println("Testing ParseTreeExpr");
        // loop through lines in input file
        while ( scan.hasNextLine()){
        	line = scan.nextLine();
        	System.out.println("\nnext line: [" + line +"]");
        	TokenIter tokIt = new TokenIter(line);
    		ParseTreeExpr buildTree = new ParseTreeExpr(tokIt);
    		Tree pTree = buildTree.line();
    		
    		System.out.println("expression tree:"); 
    		pTree.preorderTraverse();
    		
    		System.out.println("result: " + pTree.postorderEval());
        }
	}
}
