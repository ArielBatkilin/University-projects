/**
 * this class represent the health attribute.
 */

public class Health {


	/** the starting health */
	private final static int startHp = 22;

	/** shot damage */
	private final static int shotDamage = 1;

	/** collision damage */
	private final static int collisionDamage = 1;

	/** the number represnts the health */
	private int hp;


	/**
	 * set the starting hp, and the shield status;
	 *
	 */
	public Health(){
		this.hp = startHp;
	}

	/**
	 * takes of the hp, the collision damage
	 *
	 * @param isShildUp - true if shield is up, false otherwise
	 */
	public void collision(boolean isShildUp){
		if (isShildUp == false){
			this.hp -= collisionDamage;
		}
	}


	/**
	 * takes of the hp, the shot damage
	 *
	 * @param isShildUp - true if shield is up, false otherwise
	 */
	public void imShot(boolean isShildUp) {
		if (isShildUp == false){
			this.hp -= shotDamage;
		}
	}


	/**
	 * @return the health
	 */
	public int getHp() {
		return hp;
	}
}
