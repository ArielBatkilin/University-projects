import java.util.LinkedList;

public class LinkedListWrapper{

    private LinkedList<String> linkedList;

	/**
	 * constructor for wrraper to linked list
	 */
	public LinkedListWrapper(){
		this.linkedList = new LinkedList<String>();
    }

	/**
	 *
	 * @param myString adding a string to the linked list
	 * @return true in success, false otherwise
	 */
    public boolean add(String myString){
        if(this.linkedList.add(myString)) {
            return true;
        }
        return false;
    }


	/**
	 *
	 * @param myString - string to chech if in the list
	 * @return true in success, false otherwise
	 */
	public boolean contains(String myString){
        return(this.linkedList.contains(myString));
    }


	/**
	 *
	 * @param myString - string to delete fro the list
	 * @return true in success, false otherwise
	 */
	public boolean delete(String myString){
        return(this.linkedList.remove(myString));
    }

	/**
	 *
	 * @return the size of the list
	 */
	public int size(){
        return linkedList.size();
    }

	/**
	 *
	 * @param index - the index we want to check
	 * @return the value in that index
	 */
	public String get(int index){
    	return this.linkedList.get(index);
	}


}
