public class TreeNode {
	
	private String item;
	private TreeNode left;
	private TreeNode right;
	
	// leaf
	public TreeNode(String item){
		this.item = item;
		left = null;
		right = null;
	}

	// internal 2 children
	public TreeNode(String item, TreeNode left, TreeNode right){
		this.item = item;
		this.left = left;
		this.right = right;
	}
	
	// internal 1 child
	public TreeNode(String item, TreeNode left){
		this.item = item;
		this.left = left;
		this.right = null;
	}

	String getItem(){
		return item;
	}
	
	TreeNode getLeft(){
		return left;
	}
	
	TreeNode getRight(){
		return right;
	}
	
	public String toString(){
		if(left==null && right == null)
			return "leaf: " + item;
		else
			return "internal: " + item;
		
	}
	
	public static void main(String[] args){
		
		TreeNode tn1 = new TreeNode("true");
		TreeNode tn2 = new TreeNode("false");
		TreeNode atree = new TreeNode("and",tn1,tn2);
		
		
		System.out.println("and tree: " + atree);
		System.out.println("  left:  " + atree.getLeft());
		System.out.println("  right: " + atree.getRight());
		
		TreeNode tn3 = new TreeNode("false");
		TreeNode ntree = new TreeNode("not",tn3);
		System.out.println("not tree: " + ntree);
		System.out.println("  left:  " + ntree.getLeft());		
	}
	
}
