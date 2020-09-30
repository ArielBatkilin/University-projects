public class OpenHashSet extends SimpleHashSet{

	private LinkedListWrapper[] hashSet;

	/**
	 * Constructs a new, empty table with the specified load factors, and the default initial capacity (16).
	 * @param upperLoadFactor The upper load factor of the hash table.
	 * @param lowerLoadFactor The lower load factor of the hash table.
	 */
	public OpenHashSet(float upperLoadFactor, float lowerLoadFactor){
		super(upperLoadFactor, lowerLoadFactor);
		this.hashSet = new LinkedListWrapper[this.capacity];
	}

	/**
	 * A default constructor. Constructs a new, empty table with default initial capacity (16), upper load
	 * factor (0.75) and lower load factor (0.25).
	 */
	public OpenHashSet(){
		super();
		this.hashSet = new LinkedListWrapper[this.capacity];
	}

	/**
	 *Data constructor - builds the hash set by adding the elements one by one. Duplicate values should be
	 * ignored. The new table has the default values of initial capacity (16), upper load factor (0.75), and
	 * lower load factor (0.25).
	 * @param data Values to add to the set.
	 */
	public OpenHashSet(java.lang.String[] data){
		super();
		this.hashSet = new LinkedListWrapper[this.capacity];
		for (int i=0; i<data.length; i++){
			this.add(data[i]);
		}
	}


	/**
	 * adds a value to the hash set
	 * @param value - the value to add.
	 * @param myHashSet - the hash set to be added to.
	 */
	private void addValueToMyHash(java.lang.String value, LinkedListWrapper[] myHashSet){
		int myClamp = clamp(value.hashCode());
		if (myHashSet[myClamp] == null){
			myHashSet[myClamp] = new LinkedListWrapper();
		}
		myHashSet[myClamp].add(value);
	}

	/**
	 * making the hash set bigger
	 */
	private void rehashBigger(){
		int newCapacity = this.capacity*2;
		LinkedListWrapper[] newHashSet = new LinkedListWrapper[newCapacity];
		for (int i = 0; i<this.capacity; i++){
			if (this.hashSet[i] != null){
				for (int j = 0; j<this.hashSet[i].size(); j++){
					addValueToMyHash(this.hashSet[i].get(j), newHashSet);
				}
			}
		}
		this.capacity = newCapacity;
		this.hashSet = newHashSet;
	}

	/**
	 *
	 * @param newValue New value to add to the set
	 * @return False iff newValue already exists in the set
	 */
	public boolean add(java.lang.String newValue){
		int myClamp = clamp(newValue.hashCode());
		if (this.contains(newValue)) {
			return false;
		}
		if (resizeBig()){
			this.rehashBigger();
		}
		addValueToMyHash(newValue, this.hashSet);
		this.size+=1;
		return true;
	}

	/**
	 *
	 * @param searchVal Value to search for
	 * @return True iff searchVal is found in the set
	 */
	public boolean contains(java.lang.String searchVal){
		int myClamp = clamp(searchVal.hashCode());
		if (this.hashSet[myClamp] != null && this.hashSet[myClamp].contains(searchVal)){
			return true;
		}
		return false;
	}

	/**
	 * making the hash set smaller
	 */
	private void rehashSmaller(){
		int newCapacity = this.capacity/2;
		LinkedListWrapper[] newHashSet = new LinkedListWrapper[newCapacity];
		for (int i = 0; i<this.capacity; i++){
			if (this.hashSet[i] != null){
				for (int j = 0; j<this.hashSet[i].size(); j++){
					addValueToMyHash(this.hashSet[i].get(j), newHashSet);
				}
			}
		}
		this.capacity = newCapacity;
		this.hashSet = newHashSet;
	}

	/**
	 *
	 * @param toDelete Value to delete
	 * @return True iff toDelete is found and deleted
	 */
	public boolean delete(java.lang.String toDelete){
		int myClamp = clamp(toDelete.hashCode());
		if (!this.contains(toDelete)) {
			return false;
		}
		else {
			this.hashSet[myClamp].delete(toDelete);
			this.size -= 1;
			if (hashSet[myClamp].size() == 0){
				this.hashSet[myClamp] = null;
			}
			if (resizeSmall()){
				this.rehashSmaller();
			}
			return true;
		}

	}

	/**
	 *
	 * @return The number of elements currently in the set
	 */
	public int size(){
		int counter = 0;
		for (int i = 0; i < this.capacity; i++){
			if (this.hashSet[i] != null){
				counter += this.hashSet[i].size();
			}
		}
		return counter;
	}

	/**
	 *
	 * @return The current capacity (number of cells) of the table.
	 */
	public int capacity(){
		return this.capacity;
	}

}
