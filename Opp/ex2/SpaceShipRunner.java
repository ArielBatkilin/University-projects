import oop.ex2.GameGUI;

import java.awt.*;
import java.lang.Math;

/**
 * the runner spaceship class that extends the regular SpaceShip class
 */
public class SpaceShipRunner extends SpaceShip {

	/** the ruuner is always accelerate */
	private static final boolean accelerate = true;

	/** the distance the runner will start thinking of teleporting */
	private static final double scaryDistance = 0.25;

	/** the angle that if the enemy is faced towards the runner, the runner will start thinking of
	 * teleporting.
	 */
	private static final double scaryEnemyAngle = 0.23;


	/**
	 * creates a runner spaceship
	 */
	public SpaceShipRunner(){
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
		double angleOfEnemyToMe = closestShip.getPhysics().angleTo(this.myPhysics);
		if ((this.myPhysics.distanceFrom(closestShip.getPhysics())<scaryDistance) && (Math.abs
				(angleOfEnemyToMe)<scaryEnemyAngle)){ /* Teleporting */
			this.teleport();
		}closestShip = game.getClosestShipTo(this);
		double angleToClosest = this.myPhysics.angleTo(closestShip.getPhysics());
		if (angleToClosest > 0){
			turn += SpaceShip.rightTurn;
		}else if (angleToClosest<0){
			turn += SpaceShip.leftTurn;
		}this.myPhysics.move(accelerate, turn); /* accelerate and turn */
		this.mp.charge(); /* regeneration of energy */
	}
}
