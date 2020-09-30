package game;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class Node<T> {
	private List<Node<T>> children = new ArrayList<Node<T>>();
	private Node<T> parent = null;
	private T data = null;
	private boolean isRoot=false;
    private boolean rootChose=false;

	public Node(T data) {
	    this.isRoot=true;
	    this.rootChose=true;
		this.data = data;
	}

	public Node(T data, Node<T> parent) {
		this.data = data;
		this.parent = parent;
		parent.setChild(this);

	}

	public void setChild(Node<T> child){
	    this.children.add(child);
    }
    public Node<T> getParent(){
        return this.parent;
    }

    public boolean isInTree(Node<T> node){
	    if(node.isRoot()){
	        return true;
        }
	    Node<T> temp = node.getParent();
	    while(temp!=null){
            if(temp.isRoot()){
                return true;
            }
            temp = temp.getParent();
        }
        return false;
    }

	public List<Node<T>> getChildren() {
		return children;
	}

	public void setParent(Node<T> parent) {
		parent.addChild(this);
		this.parent = parent;
	}

//	public void addChild(T data) {
//		Node<T> child = new Node<T>(data);
//		child.setParent(this);
//		this.children.add(child);
//	}

	public void addChild(Node<T> child) {
		child.setParent(this);
		this.children.add(child);
	}

	public T getData() {
		return this.data;
	}

	public void setData(T data) {
		this.data = data;
	}

	public boolean isRoot() {
		return (this.isRoot);
	}

	public boolean isLeaf() {
		return this.children.size() == 0;
	}

	public void removeParent() {
		this.parent = null;
	}
}