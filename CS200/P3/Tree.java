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
	public Boolean postorderEval(){
		Boolean res = null;
		if(!isEmpty()){
			res = postorderEval(root);
		}
		return res;
	}

	
	// evaluate left tree
	// evaluate right tree (if not null)
	// evaluate node and return Boolean result
	public Boolean postorderEval(TreeNode node){
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
			else
				leftB = postorderEval(left); // recurse, evaluating left as node
		}
		// evaluate right tree
		if(right != null) {
			// check if right node's item is a simple value
			if(right.getItem().equals("true") || right.getItem().equals("false"))
				rightB = Boolean.valueOf(right.getItem()); // set rightB to boolean value of right node
			// if not it has to be an expression, thus evaluate and get value right tree
			else
				rightB = postorderEval(right); // recurse, evaluating right as node
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
		// item must be a "or" operation
		else
			return (leftB || rightB); // return OR of leftB and rightB
	}	

	public static void main(String[] args){
		args = Debug.init(args); 
		System.out.println("Testing Tree and TreeNode");
		System.out.println("Stepwise build infix expression:\n not not (true or false) and true");
		
		Tree t = new Tree();
		System.out.println("\ntree: "); t.preorderTraverse();	
		System.out.println("result: " + t.postorderEval());
		
		TreeNode a = new TreeNode("true");
		t = new Tree(a);
		System.out.println("\ntree: "); t.preorderTraverse();	
		System.out.println("result: " + t.postorderEval());
				
		TreeNode b = new TreeNode("false");
		TreeNode or = new TreeNode("or", a, b);
		t = new Tree(or);
		System.out.println("\ntree: "); t.preorderTraverse();	
		System.out.println("result: " + t.postorderEval());
		
		TreeNode not2 = new TreeNode("not", or);
		t = new Tree(not2);
		System.out.println("\ntree: "); t.preorderTraverse();	
		System.out.println("result: " + t.postorderEval());
		
		TreeNode not = new TreeNode("not", not2);
		TreeNode and = new TreeNode("and", not, new TreeNode("true"));
		t = new Tree(and);
		System.out.println("\ntree: "); t.preorderTraverse();	
		System.out.println("result: " + t.postorderEval());
	}
	
}
