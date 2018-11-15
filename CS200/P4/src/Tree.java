public class Tree {
	// the root of the tree
	private TreeNode root;

	//empty tree
	public Tree(){
		this.root = null;
	}

	// rootItem, empty children
	public Tree(TreeNode root){
		this.root = root;
	}

	public boolean isEmpty(){
		return root == null;
	}

	public void preorderTraverse(){
		if (!isEmpty())
			preorderTraverse(root,"");
		else
			System.out.println("null");
	}

	// print root item
	// print left tree
	// print right tree
	public void preorderTraverse(TreeNode node, String indent){
		System.out.println(indent+node.getItem());
		if(node.getLeft()!=null)
			preorderTraverse(node.getLeft(),indent+" ");
		if(node.getRight()!=null)
			preorderTraverse(node.getRight(),indent+" ");
	}

	// if tree empty return null
	// else evaluate the tree by postorder traversal 
	// and return its value
	public Boolean postorderEval(BST symTab) throws BSTException{
		Boolean res = null;
		if(!isEmpty()){
			res = postorderEval(root,symTab);
		}
		return res;
	}


	// evaluate left tree
	// evaluate right tree (if not null)
	// evaluate node and return Boolean result
	public Boolean postorderEval(TreeNode node, BST symTab) throws BSTException {
		String item = node.getItem();	// get node item
		TreeNode left = node.getLeft(); // get left node
		TreeNode right = node.getRight(); // get right node
		Boolean leftB = false; // temporary value
		Boolean rightB = false; // temporary value
		// evaluate left tree
		if(left != null) {
			// check if left node's item is a simple value
			if(left.getItem().equals("true") || left.getItem().equals("false"))
				leftB = Boolean.valueOf(left.getItem()); // set leftB to boolean value of left node
			// if not it has to be an expression, thus evaluate and get value left tree
			else if(left.getItem().equals("not") || left.getItem().equals("or") || left.equals("and"))
				leftB = postorderEval(left,symTab); // recurse, evaluating left as node
			// if its neither a expression or a simple value then it is a identifier
			else
				leftB = symTab.retrieveItem(left.getItem()).getVal();
		}
		// evaluate right tree
		if(right != null) {
			// check if right node's item is a simple value
			if(right.getItem().equals("true") || right.getItem().equals("false"))
				rightB = Boolean.valueOf(right.getItem()); // set rightB to boolean value of right node
			// if not it has to be an expression, thus evaluate and get value right tree
			else if(right.getItem().equals("not") || right.getItem().equals("or") || right.equals("and"))
				rightB = postorderEval(right,symTab); // recurse, evaluating right as node
			// if its neither a expression or a simple value then it is a identifier
			else
				rightB = symTab.retrieveItem(right.getItem()).getVal();
		}
		// check if item is value
		if(item.equals("true") || item.equals("false"))
			return Boolean.valueOf(item);
		// check if item is "not" operation
		else if(item.equals("not"))
			return !leftB; // return negation of leftB
		// check if item is a "and" operation
		else if(item.equals("and"))
			return (leftB && rightB); // return AND of leftB and rightB 
		// check if item is a "or" operation
		else if(item.equals("or"))
			return (leftB || rightB); // return OR of leftB and rightB
		// else it must be a identifier, use the symTab to check the value
		else
			return symTab.retrieveItem(item).getVal(); // get IdVal from symTab and then the boolean from IdVal
	}	
}
