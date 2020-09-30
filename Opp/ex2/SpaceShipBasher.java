import oop.ex2.GameGUI;
/**
 * the basher spaceship class that extends the regular SpaceShip class
 */

public class SpaceShipBasher extends SpaceShip {

	/** the basher is always accelerate */
	private static final boolean accelerate = true;

	/** the distance the basher will activate his shield */
	private static final double shieldDistance = 0.19;

	/**
	 * creates a basher spaceship
	 */
	public SpaceShipBasher(){
		super();
	}

	/**
	 * Does the actions of this ship for this round.
	 * This is called once per round by the SpaceWars game driver.
	 *
	 * @param game the game object to which this ship belongs.
	 */
	public void doAction(SpaceWars game){
		int turn = 0;
		if (this.shotTimer != 0){ /* setting the shot timer */
			this.shotTimer -=1;
		}SpaceShip closestShip = game.getClosestShipTo(this);
		double angleToClosest = this.myPhysics.angleTo(closestShip.getPhysics());
		if (angleToClosest > 0){
			turn += SpaceShip.leftTurn;
		}else if (angleToClosest<0){
			turn += SpaceShip.rightTurn;
		}this.myPhysics.move(accelerate, turn); /* accelerate and turn */
		if (this.myPhysics.distanceFrom(closestShip.getPhysics())<shieldDistance){ /* shield activation */
			this.shieldOn();
		}else {
			this.isShieldUp = false;
		}this.mp.charge(); /* regeneration of energy */
	}
}
