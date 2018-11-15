
public class ParseTreeExpr {

	private String nextToken;	

        // constructor puts iter in itTokens
        private TokenIter itTokens;

        // constructor   
	public ParseTreeExpr(TokenIter iter){
		itTokens = iter;
		nextTok("");
	}

        // if there is a next Token put it in nextToken, else put null in nextToken
        private void nextTok(String indent){
    		if(itTokens.hasNext())
    			nextToken = itTokens.next();
    		else 
    			nextToken = null;
//    		Debug.printf("\t%s", indent+nextToken);
	}


	public Tree line() throws ParseException{
		TreeNode root;
		Tree tree = new Tree();
		if(nextToken!=null){
			root = expr("");
			tree = new Tree(root);
		}
		if(nextToken!=null)
			throw new ParseException("End of line expected");
		return tree;
	}

	// expr = term ( "or" term )*
	private TreeNode expr(String indent) throws ParseException{
		TreeNode left = term(indent+" ");
		while(nextToken != null && nextToken.equals("or")) {
			String op = nextToken;
			nextTok(indent+" ");
			TreeNode right = term(indent+" ");
			left = new TreeNode(op,left,right);
		}
		return left;
	}


	// term = factor ( "and" factor )*
	private TreeNode term(String indent) throws ParseException{
		TreeNode left = factor(indent+" ");
		while(nextToken != null && nextToken.equals("and")) {
			String op = nextToken;
			nextTok(indent+" ");
			TreeNode right = factor(indent+" ");
			left = new TreeNode(op,left,right);
		}
		return left;
	}

	// factor = "not" factor | "(" expr ")" | "true"| "false"
	private TreeNode factor(String indent) throws ParseException{
		TreeNode left;
		String op;
		if(nextToken != null) {
			if(nextToken.equals("not")) {
				op = nextToken;
				nextTok(indent+" ");
				left = factor(indent+" ");
				return new TreeNode(op,left);
			}
			if(nextToken.equals("(")) {
//				String open = nextToken;
				nextTok(indent+" ");
				TreeNode mid = expr(indent+" ");
//				String close = nextToken;
				nextTok(indent+" ");
				return mid;
			}
			if(nextToken.equals("true") || nextToken.equals("false")) {
				String val = nextToken;
				nextTok(indent+" ");
				return new TreeNode(val);
			}
		}
		return null;
	}

}
