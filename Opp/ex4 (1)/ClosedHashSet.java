public class ClosedHashSet extends SimpleHashSet{


	private String[] hashSet;
	private static final String MYFLAG= new String("");

	/**
	 * Constructs a new, empty table with the specified load factors, and the default initial capacity (16).
	 * @param upperLoadFactor The upper load factor of the hash table.
	 * @param lowerLoadFactor The lower load factor of the hash table.
	 */
	public ClosedHashSet(float upperLoadFactor, float lowerLoadFactor){
		super(upperLoadFactor, lowerLoadFactor);
		this.hashSet = new String[this.capacity];
	}

	/**
	 * A default constructor. Constructs a new, empty table with default initial capacity (16),
	 * upper load factor (0.75) and lower load factor (0.25).
	 */
	public ClosedHashSet(){
		super();
		this.hashSet = new String[this.capacity];
	}

	/**
	 *Data constructor - builds the hash set by adding the elements one by one. Duplicate values should be
	 *  ignored. The new table has the default values of initial capacity (16), upper load factor (0.75),
	 *  and lower load factor (0.25).
	 * @param data Values to add to the set.
	 */
	public ClosedHashSet(java.lang.String[] data){
		super();
		this.hashSet = new String[this.capacity];
		for (int i = 0; i<data.length; i++){
			this.add(data[i]);
		}
	}

	/**
	 * adds a value to the hash set
	 * @param value - the value to add.
	 * @param myHashSet - the hash set to be added to.
	 */
	private void addValueToMyHash(java.lang.String value, String[] myHashSet){
		if (value != null){
			if (value != MYFLAG){
				for (int i = 0; i < this.capacity; i++) {
					int myClamp = clamp(value.hashCode() + ((i + i * i) / 2));
					if (myHashSet[myClamp] == null || myHashSet[myClamp] == MYFLAG) {
						myHashSet[myClamp] = value;
						break;
					}
				}
			}
		}
	}

	/**
	 * making the hash set bigger
	 */
	private void rehashBigger(){
		int oldCapacity = this.capacity;
		this.capacity = oldCapacity*2;
		String[] newHashSet = new String[this.capacity];
		for (int i = 0; i<oldCapacity; i++){
			addValueToMyHash(this.hashSet[i], newHashSet);
		}
		this.hashSet = newHashSet;
	}

	/**
	 *
	 * @param newValue New value to add to the set
	 * @return False iff newValue already exists in the set
	 */
	public boolean add(java.lang.String newValue){
		if (this.contains(newValue)){
			return false;
		}
		for (int i = 0; i < this.capacity; i++){
			int myClamp = clamp(newValue.hashCode() + ((i + i*i)/2));
			if (this.hashSet[myClamp] == null || this.hashSet[myClamp] == MYFLAG){
				if (resizeBig()){
					this.rehashBigger();
				}
				addValueToMyHash(newValue, this.hashSet);
				this.size +=1;
				return true;
			}
		}
		if (resizeBig()){ // if the table is already full
			this.rehashBigger();
		}
		return add(newValue);
	}

	/**
	 *
	 * @param searchVal Value to search for
	 * @return True iff searchVal is found in the set
	 */
	public boolean contains(java.lang.String searchVal){
		for (int i = 0; i < this.capacity; i++) {
			int myClamp = clamp(searchVal.hashCode() + ((i + i * i) / 2));
			if (this.hashSet[myClamp] == null) {
				return false;
			}
			if (searchVal.equals(hashSet[myClamp]) && !searchVal.equals(MYFLAG)) {
				return true;
			} else if (searchVal.equals(MYFLAG) && this.hashSet[myClamp].equals(searchVal) && this
					.hashSet[myClamp] !=
					MYFLAG) {
				return true;
			}
		}
		return false;
	}

	/**
	 * making the hash set smaller
	 */
	private void rehashSmaller(){
		int oldCapacity = this.capacity;
		this.capacity = oldCapacity/2;
		String[] newHashSet = new String[this.capacity];
		for (int i = 0; i<oldCapacity; i++){
			addValueToMyHash(this.hashSet[i], newHashSet);
		}
		this.hashSet = newHashSet;
	}

	/**
	 * Remove the input element from the set.
	 * @param toDelete Value to delete
	 * @return True iff toDelete is found and deleted
	 */
	public boolean delete(java.lang.String toDelete){
		if (!this.contains(toDelete)){
			return false;
		}
		for (int i = 0; i < this.capacity; i++) {
			int myClamp = clamp(toDelete.hashCode() + ((i + i * i) / 2));
			if (this.hashSet[myClamp].equals(toDelete)) {
				this.hashSet[myClamp] = MYFLAG;
				this.size -= 1;
				if (resizeSmall()){
					this.rehashSmaller();
				}
				return true;
			}
		}
		return false;
	}

	/**
	 *
	 * @return The number of elements currently in the set
	 */
	public int size(){
		return this.size;
	}

	/**
	 *
	 * @return The current capacity (number of cells) of the table.
	 */
	public int capacity(){
		return this.capacity;
	}
}
