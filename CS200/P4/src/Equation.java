
public class Equation {

	private String nextToken;	

	// constructor puts iter in itTokens
	private TokenIter itTokens;

	// constructor   
	public Equation(TokenIter iter){
		itTokens = iter;
		nextTok();
	}

	// if there is a next Token put it in nextToken, else put null in nextToken
	private void nextTok(){
		if(itTokens.hasNext())
			nextToken = itTokens.next();
		else 
			nextToken = null;
	}

	public IdVal line(BST symboTable) throws BSTException, ParseException{
		if (nextToken == null){
			return null;
		}
		String Id = "";
		if (nextToken != null){
			Id = nextToken;
		}
		nextTok();
		nextTok();

		TreeNode root;
		Tree tree = new Tree();
		if(nextToken != null){
			root = expr(symboTable);
			tree = new Tree(root);
		}
		if(nextToken != null)
			throw new ParseException();
		boolean result = tree.postorderEval(symboTable);
		// needs to return result of identifier = (ie IDVAL pair)

		if (Id != "" && (result == true | result == false)){
			IdVal IdRes = new IdVal(Id, result);
			symboTable.insertItem(IdRes);
			return IdRes;
		}

		else{
			return null;		// empty string as equation input
		}

	}

	private TreeNode expr(BST symboTable) throws ParseException{
		TreeNode left = term(symboTable);
		while(nextToken != null && nextToken.equals("or")){
			String op = nextToken;
			nextTok();
			TreeNode right = term(symboTable);
			left = new TreeNode(op, left, right);
		}

		return left;
	}


	// term = factor ( "and" factor )*
	private TreeNode term(BST symboTable) throws ParseException{
		TreeNode left = factor(symboTable);
		while(nextToken != null && nextToken.contentEquals("and")){
			String temp = nextToken;
			nextTok();
			TreeNode right = factor(symboTable);
			left = new TreeNode(temp, left, right);
		}
		return left;


	}

	// factor = "not" factor | "(" expr ")" | "true"| "false"
	private TreeNode factor(BST symboTable) throws ParseException{
		if (nextToken != null){
			if (nextToken.contentEquals("not")){
				String op = "not";			// first factor
				nextTok();
				TreeNode left = factor(symboTable);			// this checks for remaining factors
				return new TreeNode(op, left);				// this recursively builds tree from bottom up
			}
			else if(nextToken.contentEquals("(")){
				//String op = nextToken;
				nextTok();
				TreeNode left = expr(symboTable);
				//String closeBracket = nextToken; 		
				nextTok();
				return left;
			}
			else if(nextToken.contentEquals("true") | nextToken.contentEquals("false")){
				String op = nextToken;
				nextTok();
				return new TreeNode(op);
			}

			else{									// we know it is an identifier, one we need to lookup
				IdVal temp = symboTable.retrieveItem(nextToken);
				boolean tempValue = temp.getVal();
				String op = "true";
				if (tempValue == false)
					op = "false";
				nextTok();
				return new TreeNode(op);
			}
		}

		else
			return null;
	}


}
