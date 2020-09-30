import java.awt.Image;
import oop.ex2.*;

/**
 * this class is the base class for all the ships. the only two methods that the ships may override is the
 * "doAction" method, and the "getImage" method.
 *
 * @author batkiller
 */
public class SpaceShip{

	/** the right turn value */
	public static final int rightTurn = -1;

	/** the left turn value */
	public static final int leftTurn = 1;

	/** the shot waitting time */
	private static final int shotWaitTime = 7;

	/** the physics instance of the ship */
	protected SpaceShipPhysics myPhysics;

	/** the energy instance of the ship */
	protected Energy mp;

	/** the health instance of the ship */
	protected Health hp;

	/** true if shield is up, false othewise */
	protected boolean isShieldUp;

	/** the shot timer of the ship */
	protected int shotTimer;


	/**
	 * creates a new spaceship
	 */
	public SpaceShip(){
		this.hp = new Health();
		this.mp = new Energy();
		this.isShieldUp = false;
		this.myPhysics = new SpaceShipPhysics();
		this.shotTimer = 0;
	}
    /**
     * Does the actions of this ship for this round. 
     * This is called once per round by the SpaceWars game driver.
     * 
     * @param game the game object to which this ship belongs.
     */
    public void doAction(SpaceWars game) {
    	this.myPhysics.move(true, 0);
    }

    /**
     * This method is called every time a collision with this ship occurs 
     */
    public void collidedWithAnotherShip(){
    	this.hp.collision(this.isShieldUp);
    	this.mp.collosion(this.isShieldUp);
    }

    /** 
     * This method is called whenever a ship has died. It resets the ship's 
     * attributes, and starts it at a new random position.
     */
    public void reset(){
		this.hp = new Health();
		this.mp = new Energy();
		this.isShieldUp = false;
		this.myPhysics = new SpaceShipPhysics();
    }

    /**
     * Checks if this ship is dead.
     * 
     * @return true if the ship is dead. false otherwise.
     */
    public boolean isDead() {
        if (hp.getHp()<=0){
        	return true;
		}
		return false;
    }

    /**
     * Gets the physics object that controls this ship.
     * 
     * @return the physics object that controls the ship.
     */
    public SpaceShipPhysics getPhysics() {
        return this.myPhysics;
    }

    /**
     * This method is called by the SpaceWars game object when ever this ship
     * gets hit by a shot.
     */
    public void gotHit() {
    	this.hp.imShot(this.isShieldUp);
    	this.mp.imShot(this.isShieldUp);
    }

    /**
     * Gets the image of this ship. This method should return the image of the
     * ship with or without the shield. This will be displayed on the GUI at
     * the end of the round.
     * 
     * @return the image of this ship.
     */
    public Image getImage(){
        if (this.isShieldUp){
        	return GameGUI.ENEMY_SPACESHIP_IMAGE_SHIELD;
		} return GameGUI.ENEMY_SPACESHIP_IMAGE;
    }

    /**
     * Attempts to fire a shot.
     * 
     * @param game the game object.
     */
    public void fire(SpaceWars game) {
       if (this.shotTimer == 0){
		   if (this.mp.fire()){
			   game.addShot(myPhysics);
			   this.shotTimer = shotWaitTime;
		   }
	   }
    }

    /**
     * Attempts to turn on the shield.
     */
    public void shieldOn() {
        if (this.mp.shield()){
        	this.isShieldUp = true;
		}else {
        	this.isShieldUp = false;
		}
    }

    /**
     * Attempts to teleport.
     */
    public void teleport() {
		if (this.mp.teleport()){
			this.myPhysics = new SpaceShipPhysics();
		}
    }
    
}
