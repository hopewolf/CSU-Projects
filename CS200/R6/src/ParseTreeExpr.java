/* R6 ParseTreeExpr */
public class ParseTreeExpr {

	private String nextToken;	
	private TokenIter itTokens;

	public ParseTreeExpr(TokenIter iter){
		itTokens = iter;
		nextTok("");
	}

	private void nextTok(String indent){
		if(itTokens.hasNext())
			nextToken = itTokens.next();
		else 
			nextToken = null;
		Debug.printf("\t%s", indent+nextToken);
	}

	private void error(String errMess) throws ParseException{
		throw new ParseException(errMess);
	}

	
	public Tree line() throws ParseException{
		TreeNode root;
		Tree tree = new Tree();
		if(nextToken!=null){
			root = expr("");
			tree = new Tree(root);
		}
		if(nextToken!=null)
			error("end of line expected");
		return tree;
	}

	// expr = number ( "+" number )*
	// expr = term ( "+"|"-" term )*
	// Notice that we only parse sums of terms, 
	// not differences
	private TreeNode expr(String indent) throws ParseException{
		Debug.printf("\t%s", indent+"expr");
		TreeNode left = term(indent+" ");
		while(nextToken != null && (nextToken.equals("+") || nextToken.contentEquals("-"))) {
			String op = nextToken;
			nextTok(indent+" ");
			TreeNode right = term(indent+" ");
			left = new TreeNode(op,left, right);
		}
		return left;
	}
	
	// term = factor ( "*"|"/" factor )*
	private TreeNode term(String indent) throws ParseException {
		Debug.printf("\t%s", indent+"term");
		TreeNode left = factor(indent+" ");
		while(nextToken != null && (nextToken.equals("*") || nextToken.contentEquals("/"))) {
			String op = nextToken;
			nextTok(indent+" ");
			TreeNode right = factor(indent+" ");
			left = new TreeNode(op,left,right);
		}
		return left;
	}
	
	// factor = "-" factor | number | "(" expr ")"
	private TreeNode factor(String indent) throws ParseException {
		if(nextToken != null && nextToken.equals("-")) {
			String neg = nextToken;
			TreeNode left = factor(indent+" ");
			left = new TreeNode(neg,left);
			return left;
		}
		else if(nextToken != null && number(indent+" ") != null) {
			return number(indent+" ");
		}
		else if(nextToken != null && nextToken.equals("(")) {
			String open = nextToken;
			TreeNode mid = expr(indent+" ");
			String close = nextToken;
			//TODO Finish factor
		}
		return null;
	}

	private TreeNode number(String indent) throws ParseException{
		Debug.printf("\t%s", indent+"number");
		if(Character.isDigit(nextToken.charAt(0))){
			String num = nextToken;
			nextTok(indent);
			return new TreeNode(num);
		}
		else {
			error("number expected");
			return null; // for java type checker
		}
	}
}
