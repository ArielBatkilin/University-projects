import java.util.Random;

/**
 * the drunk spaceship class that extends the regular SpaceShip class
 */
public class SpaceShipDrunkard extends SpaceShip{

	/** the drunk ship is always accelerate */
	private static final boolean accelerate = true;

	/** round counter */
	private int roundCounter;

	/** random instance that i'll use */
	private Random rndDirection;

	/** the pilots breaking point */
	private static final int breakingPoint = 90;

	/** the pilots time to be silber again */
	private static final int silberTime = 250;
	/**
	 * creates a drunkard spaceship
	 */
	public SpaceShipDrunkard(){
		super();
		roundCounter = 0;
		rndDirection = new Random();
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
		this.roundCounter+=1;
		if (this.roundCounter == silberTime){
			this.roundCounter = 0;
			this.teleport(); /* teleporting */
		}
		if (this.roundCounter < breakingPoint){
			if (angleToClosest > 0){
				turn += SpaceShip.leftTurn;
			}else if (angleToClosest<0){
				turn += SpaceShip.rightTurn;
			}
		}else {
			int rand = rndDirection.nextInt(2);
			if (rand == 0){
				turn += SpaceShip.leftTurn;
			}else {
				turn += SpaceShip.rightTurn;
			}
		}this.myPhysics.move(accelerate, turn); /* accelerate and turn */
		if (Math.abs(angleToClosest)<0.21){ /* firing */
			this.fire(game);
		}this.mp.charge(); /* regeneration of energy */
	}
}
