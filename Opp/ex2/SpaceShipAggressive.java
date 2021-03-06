import java.lang.Math;

/**
 * the aggressive spaceship class that extends the regular SpaceShip class
 */
public class SpaceShipAggressive extends SpaceShip {

	/** the basher is always accelerate */
	private static final boolean accelerate = true;

	/** the angle the aggressive ship will try to fire */
	private static final double angleToFire = 0.21;

	/**
	 * creates a aggressive spaceship
	 */
	public SpaceShipAggressive(){
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
		if (Math.abs(angleToClosest)<angleToFire){ /* firing */
			this.fire(game);
		}this.mp.charge(); /* regeneration of energy */
	}
}
