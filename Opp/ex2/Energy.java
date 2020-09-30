public class Energy {


	/** the starting max energy */
	private final static int startMaxMp = 210;

	/** the starting mp */
	private final static int startMp = 190;

	/** a price for a shot */
	private final static int shotCost = 19;

	/** a price for a teleport */
	private final static int teleportCost = 140;

	/** a price for a shield */
	private final static int shieldCost = 3;

	/** the bashing bonus */
	private final static int bashingBonus = 18;

	/** a collosion dmg */
	private final static int collosionDmg = 10;

	/** a shot dmg */
	private final static int shotDmg = 10;

	/** how much the energy charge per round */
	private final static int chargePerRound = 1;

	/** the number represents the energy */
	private int myMp;

	/** the max mp the player can reach */
	private int myMaxMp;

	/**
	 * set the mp and the max mp to starting values
	 */
	public Energy(){
		this.myMaxMp = startMaxMp;
		this.myMp = startMp;
	}

	/**
	 * if the energy is above the max level it makes the enrgy equal to the max level
	 */
	private void doOrder(){
		if (this.myMp > this.myMaxMp){
			this.myMp = myMaxMp;
		} if (this.myMp < 0){
			myMp = 0;
		}
	}

	/**
	 * in case of collosion if the shild is up the mp and the max level will get the bashing bonus
	 * else get the collosion dmg
	 *
	 * @param isShieldUp - true if shield is up, false otherwise
	 */
	public void collosion(boolean isShieldUp){
		if (isShieldUp){
			this.myMaxMp += bashingBonus;
			this.myMp += bashingBonus;
		} else {
			this.myMaxMp -= collosionDmg;
			this.doOrder();
		}
	}

	/**
	 * in case of being hit by a shot, if there is shield nothing will happend, else the mp will take a
	 * shot dmg
	 *
	 * @param isShieldUp - true if shield is up, false otherwise
	 */
	public void imShot(boolean isShieldUp){
		if (isShieldUp == false){
			this.myMaxMp -= shotDmg;
			this.doOrder();
		}
	}

	/**
	 * raise the mp by the charging per round.
	 */
	public void charge(){
		this.myMp += chargePerRound;
		this.doOrder();
	}

	/**
	 * if there is enough energy a shot is being bought and the method returns true, otherwise the method
	 * just returns false.
	 *
	 * @return true if the shot were bought successfully, false otherwise
	 */
	public boolean fire(){
		if (this.myMp >= shotCost){
			this.myMp -= shotCost;
			return true;
		}else {
			return false;
		}
	}

	/**
	 * if there is enough energy a teleport is being bought and the method returns true, otherwise the
	 * method just returns false.
	 *
	 * @return true if the teleport were bought successfully, false otherwise
	 */
	public boolean teleport(){
		if (this.myMp >= teleportCost){
			this.myMp -= teleportCost;
			return true;
		}else {
			return false;
		}
	}

	/**
	 * if there is enough energy a shield is being bought and the method returns true, otherwise the
	 * method just returns false.
	 *
	 * @return true if the shield were bought successfully, false otherwise
	 */
	public boolean shield(){
		if (this.myMp >= shieldCost){
			this.myMp -= shieldCost;
			return true;
		}else {
			return false;
		}

	}

	/**
	 *
	 * @return the energy
	 */
	public int getMyMp() {
		return myMp;
	}

	/**
	 *
	 * @return the max energy level
	 */
	public int getMyMaxMp() {
		return myMaxMp;
	}

	public static void main(String[] args){
		Energy dod = new Energy();
		System.out.println(dod.getMyMp());
		System.out.println(dod.getMyMaxMp());
		dod.collosion(true);
		System.out.println(dod.getMyMp());
		System.out.println(dod.getMyMaxMp());
		dod.collosion(false);
		System.out.println(dod.getMyMp());
		System.out.println(dod.getMyMaxMp());
		dod.collosion(false);
		System.out.println(dod.getMyMp());
		System.out.println(dod.getMyMaxMp());
		dod.collosion(false);
		System.out.println(dod.getMyMp());
		System.out.println(dod.getMyMaxMp());
		dod.collosion(false);
		System.out.println(dod.getMyMp());
		System.out.println(dod.getMyMaxMp());
		dod.collosion(false);
		System.out.println(dod.getMyMp());
		System.out.println(dod.getMyMaxMp());
		dod.fire();
		System.out.println(dod.getMyMp());
		System.out.println(dod.getMyMaxMp());

	}
}
