
public class BST{
	// this Binary Search Tree is used for the implementation of the 
	// Symbol Table containing IdVals: (id,value) pairs
	// An IdVal is a Comparable containing a String Identifier Key  
	// and a Boolean Value 
	
	private BSTNode<IdVal> root;

	//empty tree
	public BST(){
		this.root = null;
	}

	public boolean isEmpty(){
		return root==null;
	}

	public void insertItem(IdVal item) throws BSTException{
		root = insertItem(root, item);
	}

	private BSTNode<IdVal> insertItem(BSTNode<IdVal> node, IdVal item) throws BSTException{
		BSTNode<IdVal> newSubTree;
		if(node==null) {
			node = new BSTNode<IdVal>(item);
			return node;
		}
		IdVal tok = node.getItem();
		// check if the item is different from tok (node item)
		if(item.getKey().compareTo(tok.getKey())<0) {
			newSubTree = insertItem(node.getLeft(),item);
			node.setLeft(newSubTree);
			return node;
		}
		if(item.getKey().compareTo(tok.getKey())>0) {
			newSubTree = insertItem(node.getRight(),item);
			node.setRight(newSubTree);
			return node;
		}
		// if they're the same then were adding something that already exists thus, error
		else
			throw new BSTException("Inserting existing item!");
	}

	public IdVal retrieveItem(String key){
		return retrieveItem(root,key);
	}
	
	private IdVal retrieveItem(BSTNode<IdVal> node, String key){
		IdVal treeItem;
		if(node==null)
			treeItem = null;
		else{
			IdVal nodeItem = node.getItem();
			if(key.compareTo(nodeItem.getKey()) == 0)
				//found
				treeItem = (IdVal) nodeItem;
			else if(key.compareTo(nodeItem.getKey()) < 0)
				//search left
				treeItem = retrieveItem(node.getLeft(), key);
			else
				// search right
				treeItem = retrieveItem(node.getRight(), key);
		}
		return treeItem;
	}

	public void preorderTraverse(){
		if (!isEmpty())
			preorderTraverse(root,"");
		else
			System.out.println("root is null");
	}

	public void preorderTraverse(BSTNode<IdVal> node, String indent){
		System.out.println(indent+node.getItem());		
		if(node.getLeft()!=null) {
			System.out.println(indent+"left");
			preorderTraverse(node.getLeft(),indent+" ");
		}

		if(node.getRight()!=null) {
			System.out.println(indent+"right");
			preorderTraverse(node.getRight(),indent+" ");
		}
	}

}
