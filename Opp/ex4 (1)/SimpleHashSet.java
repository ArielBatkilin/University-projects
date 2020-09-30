public abstract class SimpleHashSet implements SimpleSet{

	protected static final float DEFAULT_HIGHER_CAPACITY = 0.75f;
	protected static final float DEFAULT_LOWER_CAPACITY = 0.25f;
	protected static final int INITIAL_CAPACITY = 16;
	protected int capacity;
	protected int size;
	protected float highLoadFac;
	protected float lowerLoadFac;

	/**
	 * Constructs a new hash set with the default capacities given in DEFAULT_LOWER_CAPACITY and DEFAULT_HIGHER_CAPACITY
	 */
	protected SimpleHashSet(){
		this.capacity = INITIAL_CAPACITY;
		this.size = 0;
		this.lowerLoadFac = DEFAULT_LOWER_CAPACITY;
		this.highLoadFac = DEFAULT_HIGHER_CAPACITY;
	}

	/**
	 * Constructs a new hash set with capacity INITIAL_CAPACITY
	 * @param upperLoadFactor the upper load factor before rehashing
	 * @param lowerLoadFactor the lower load factor before rehashing
	 */

	protected SimpleHashSet(float upperLoadFactor, float lowerLoadFactor){
		this.capacity = INITIAL_CAPACITY;
		this.size = 0;
		this.lowerLoadFac = lowerLoadFactor;
		this.highLoadFac = upperLoadFactor;
	}

	/**
	 *
	 * @return The current capacity (number of cells) of the table.
	 */
	public abstract int capacity();

	/**
	 *
	 * @param index the index before clamping
	 * @return an index properly clamped
	 */
	protected int clamp(int index){
		return index&(this.capacity - 1);
	}

	/**
	 *
	 * @return The lower load factor of the table.
	 */
	protected float getLowerLoadFactor(){
		return this.lowerLoadFac;
	}

	/**
	 *
	 * @return The higher load factor of the table.
	 */
	protected float getUpperLoadFactor(){
		return this.highLoadFac;
	}

	/**
	 *
	 * @return true if the hash set needs to be resized, false otherwise.
	 */
	protected boolean resizeBig(){
		float newSize = this.size + 1;
		float myCapacity = this.capacity;
		if (newSize/myCapacity > this.highLoadFac){
			return true;
		}
		return false;
	}

	/**
	 *
	 * @return true if the hash set needs to be resized, false otherwise.
	 */
	protected boolean resizeSmall(){
		float newSize = this.size;
		float myCapacity = this.capacity;
		if (newSize/myCapacity < this.lowerLoadFac && this.capacity>1){
			return true;
		}
		return false;
	}



}
