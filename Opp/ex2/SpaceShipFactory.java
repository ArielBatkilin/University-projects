import oop.ex2.*;

/**
 * the class that constract the ships
 */
public class SpaceShipFactory {

	/** The human-controlled spaceship type*/
	public static final String HUMAN_CONTROLLED_SHIP = "h";

	/** The drunk spaceship type*/
	public static final String DRUNK_SHIP = "d";

	/** The runner spaceship type*/
	public static final String RUNNER_SHIP = "r";

	/** The aggressive spaceship type*/
	public static final String AGGRESSIVE_SHIP = "a";

	/** The basher spaceship type*/
	public static final String BASHER_SHIP = "b";

	/** The special ship you designed yourself*/
	public static final String SPECIAL_SHIP = "s";

	/**
	 * this func constract the asked ships and return it in an array
	 *
	 * @param args - an array with Strings that represent the ships i need to create
	 * @return - an array of Spaceships
	 */
    public static SpaceShip[] createSpaceShips(String[] args) {
    	int shipAmount = args.length;
		SpaceShip[] spaceShipsArray = new SpaceShip[shipAmount];
		for (int i=0; i<shipAmount; i++){
			if (args[i].equals(DRUNK_SHIP)){
				SpaceShipDrunkard foo1 = new SpaceShipDrunkard();
				spaceShipsArray[i] = foo1;
			}else if (args[i].equals(HUMAN_CONTROLLED_SHIP)){
				SpaceShipHuman foo2 = new SpaceShipHuman();
				spaceShipsArray[i] = foo2;
			}else if (args[i].equals(RUNNER_SHIP)){
				SpaceShipRunner foo3 = new SpaceShipRunner();
				spaceShipsArray[i] = foo3;
			}else if (args[i].equals(AGGRESSIVE_SHIP)){
				SpaceShipAggressive foo4 = new SpaceShipAggressive();
				spaceShipsArray[i] = foo4;
			}else if (args[i].equals(BASHER_SHIP)){
				SpaceShipBasher foo5 = new SpaceShipBasher();
				spaceShipsArray[i] = foo5;
			}else if (args[i].equals(SPECIAL_SHIP)){
				SpaceShipSpaciel foo6 = new SpaceShipSpaciel();
				spaceShipsArray[i] = foo6;
			}
		}
		return spaceShipsArray;
    }
}
