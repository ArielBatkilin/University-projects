import oop.ex2.GameGUI;
import java.awt.*;

/**
 * the human spaceship class that extends the regular SpaceShip class
 */
public class SpaceShipHuman extends SpaceShip {

	/**
	 * creates a humen spaceship
	 */
	public SpaceShipHuman(){
		super();

	}

	/**
	 * Does the actions of this ship for this round.
	 * This is called once per round by the SpaceWars game driver.
	 *
	 * @param game the game object to which this ship belongs.
	 */
	public void doAction(SpaceWars game) {

		GameGUI myChecker = game.getGUI();
		boolean accelerate = myChecker.isUpPressed();
		int turn = 0;
		if (this.shotTimer != 0){ /* setting the shot timer */
			this.shotTimer -=1;
		}if (myChecker.isTeleportPressed()){ /* Teleporting */
			this.teleport();
		}if (myChecker.isLeftPressed()){
			turn += SpaceShip.leftTurn;
		}if (myChecker.isRightPressed()){
			turn += SpaceShip.rightTurn;
		}this.myPhysics.move(accelerate, turn); /* accelerate and turn */
		if (myChecker.isShieldsPressed()){ /* shield activision */
			this.shieldOn();
		}else {
			this.isShieldUp = false;
		}if (myChecker.isShotPressed()){ /* firing */
			this.fire(game);
		}this.mp.charge(); /* regeneration of energy */
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
			return GameGUI.SPACESHIP_IMAGE_SHIELD;
		} return GameGUI.SPACESHIP_IMAGE;
	}
}
