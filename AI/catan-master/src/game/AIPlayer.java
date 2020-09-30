package game;

import board.Board;
import board.EdgeLocation;
import board.Tile;
import board.VertexLocation;
import gui.GameWindow;

import javax.swing.Timer;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.Array;
import java.util.*;
import java.util.List;

import static game.GameRunner.*;
import static javafx.application.Platform.exit;

public class AIPlayer extends Player {
    private static GameWindow tmpy;
    private static Player winner;
	private static int moveCount;
	private static ArrayList<String> fourBricks;
	private static ArrayList<String> fourWool;
	private static ArrayList<String> fourOre;
	private static ArrayList<String> fourGrain;
	private static ArrayList<String> fourLumber;

	private static ArrayList<String> threeBricks;
	private static ArrayList<String> threeWool;
	private static ArrayList<String> threeOre;
	private static ArrayList<String> threeGrain;
	private static ArrayList<String> threeLumber;

	private static ArrayList<String> twoBricks;
	private static ArrayList<String> twoWool;
	private static ArrayList<String> twoOre;
	private static ArrayList<String> twoGrain;
	private static ArrayList<String> twoLumber;
	public AIPlayer(String name,Color color){
		super(name,	color , 4,2,0,2,4,2,"AI");
		moveCount =0;

		fourBricks = new ArrayList<String>();
		fourBricks.add("BRICK");
		fourBricks.add("BRICK");
		fourBricks.add("BRICK");
		fourBricks.add("BRICK");

		threeBricks = new ArrayList<String>();
		threeBricks.add("BRICK");
		threeBricks.add("BRICK");
		threeBricks.add("BRICK");

		twoBricks = new ArrayList<String>();
		twoBricks.add("BRICK");
		twoBricks.add("BRICK");

		fourWool=new ArrayList<String>();
		fourWool.add("WOOL");
		fourWool.add("WOOL");
		fourWool.add("WOOL");
		fourWool.add("WOOL");

		threeWool = new ArrayList<String>();
		threeWool.add("WOOL");
		threeWool.add("WOOL");
		threeWool.add("WOOL");

		twoWool = new ArrayList<String>();
		twoWool.add("WOOL");
		twoWool.add("WOOL");

		fourOre = new ArrayList<String>();
		fourOre.add("ORE");
		fourOre.add("ORE");
		fourOre.add("ORE");
		fourOre.add("ORE");

		threeOre = new ArrayList<String>();
		threeOre.add("ORE");
		threeOre.add("ORE");
		threeOre.add("ORE");

		twoOre = new ArrayList<String>();
		twoOre.add("ORE");
		twoOre.add("ORE");

		fourGrain = new ArrayList<String>();
		fourGrain.add("GRAIN");
		fourGrain.add("GRAIN");
		fourGrain.add("GRAIN");
		fourGrain.add("GRAIN");

		threeGrain = new ArrayList<String>();
		threeGrain.add("GRAIN");
		threeGrain.add("GRAIN");
		threeGrain.add("GRAIN");

		twoGrain = new ArrayList<String>();
		twoGrain.add("GRAIN");
		twoGrain.add("GRAIN");

		fourLumber = new ArrayList<String>();
		fourLumber.add("LUMBER");
		fourLumber.add("LUMBER");
		fourLumber.add("LUMBER");
		fourLumber.add("LUMBER");

		threeLumber = new ArrayList<String>();
		threeLumber.add("LUMBER");
		threeLumber.add("LUMBER");
		threeLumber.add("LUMBER");

		twoLumber = new ArrayList<String>();
		twoLumber.add("LUMBER");
		twoLumber.add("LUMBER");
	}

	public AIPlayer(Player other) {
        super(other);
    }

    public static void doTurn(Player p, Game game) {
        if (game.over()) {
            GameRunner.setWinner(game.winningPlayer());
            gameWinning();
            return;
        }
        int roll = game.roll(GameRunner.getCurrentPlayer());
        if (roll != 7) {
            //mainPanel();
        } else {
            rolledSeven();
        }
    }
    public static void rolledSeven() {
        if(GameRunner.getNumbPlayers()==3) {

        }
        else {

        }
    }


	public boolean addSettlementNoRoad(Game g, VertexLocation loc) {
		int bought = g.buySettlement(this);
		if (bought == 0 &&(loc != null)&&(g.getBoard().placeStructureNoRoad(loc, this))) {
			return true;
		}
		return false;
	}

	public boolean addSettlement(Game g, VertexLocation loc) {
		int bought = g.buySettlement(this);
		if (bought == 0 &&(g.getBoard().placeStructure(loc, this))) {
			return true;
		}
		return false;
	}

	public boolean addCity(Game g, VertexLocation loc){
		int bought = g.buyCity(this);
		if (bought == 0 &&(g.getBoard().placeCity(loc, this))) {
			return true;
		}
		return false;
	}

	public boolean addRoad(Game g, EdgeLocation loc){
		int bought = g.buyRoad(this);
		if(bought==0 &&(g.getBoard().placeRoad(loc, this))) {
			return true;
		}
		return false;
	}

    public static void buyDevCard(){
        return;
    }
    public static void useDevCard(){
        return;
    }

    public static void trade(){
        return;
    }
    public static void steal(){
        return;
    }
    public void endTurn(Game g, Player currentPlayer){
        // Check for largest army
        if (currentPlayer.getNumbKnights() >= 3) {

            int currMax = currentPlayer.getNumbKnights();
            Player largestArmy = currentPlayer;
            Player oldLargestArmy = null;

            for (int i = 0; i < GameRunner.getNumbPlayers(); i++) {
                Player p = getPlayer(i);

                if (p.hasLargestArmy()) {
                    oldLargestArmy = p;
                }

                if (p.getNumbKnights() > currMax) {
                    largestArmy = p;
                    currMax = p.getNumbKnights();
                }
            }

            if (oldLargestArmy != null && oldLargestArmy != largestArmy) {
                oldLargestArmy.setHasLargestArmy(false);
            }
            largestArmy.setHasLargestArmy(true);
        }
        if (g.over()) {
            setWinner(g.winningPlayer());

            gameWinning();
        }

        GameRunner.nextPlayer();
        roll();
    }

    public static void gameWinning(){
        return;
    }

    public static void roll(){
        return;
    }

    public static void doNothing(){
        return;
    }


    public void firstMove(Game game){
        HashMap<VertexLocation, Integer> myMap = versRank(game);
        Map.Entry<VertexLocation,Integer> entry = myMap.entrySet().iterator().next();
        VertexLocation v = entry.getKey();
        game.getBoard().placeStructureNoRoad(v, this);

        EdgeLocation e = new EdgeLocation(v.getXCoord(),v.getYCoord(),0);
        game.placeRoad(this, e);
    }

    public static Integer getRankOfVer(VertexLocation loc, HashSet<String> resources, HashSet<Integer> nums, Game game){
        ArrayList<Tile> nighboors = game.getBoard().getAdjacentTilesStructure(loc);
        Integer rank = 0;
        int resNum = resources.size();
        int difNums = nums.size();
        resources.addAll(resources);
        for (Tile t :nighboors) {
            if (t.getNumber() != 7) {
                rank += 6 - Math.abs(t.getNumber() - 7); //good numbers
                nums.add(t.getNumber());
            }
            if (!t.getType().equals("DESERT")) {
                resources.add(t.getType());
            }
        }
        rank += resources.size()-resNum;
        rank += nums.size()-difNums;
        return rank;
    }

    public static HashMap<VertexLocation, Integer> versRank(Game game){
        HashMap<VertexLocation, Integer> myMap = new HashMap<>();
        for (int row = 1; row < 6; row++) {
            for (int col = 1; col < 6; col++) {
                for (int ori = 0; ori < 2; ori++) {
                    VertexLocation myV = new VertexLocation(row, col, ori);
                    if (game.getBoard().canPlaceSettlementNoRoads(myV)){
                        HashSet<String> shit = new HashSet<>();
                        HashSet<Integer> shit2 = new HashSet<>();
                        myMap.put(myV, getRankOfVer(myV, shit, shit2,game));
                    }
                }
            }
        }
        HashMap<VertexLocation, Integer> sortedMap = sortByValue(myMap);
        //System.out.println(sortedMap);
        return sortedMap;
    }

    public static HashMap<VertexLocation, Integer> sortByValue(HashMap<VertexLocation, Integer> hm)
    {
        // Create a list from elements of HashMap
        List<Map.Entry<VertexLocation, Integer> > list =
                new LinkedList<Map.Entry<VertexLocation, Integer> >(hm.entrySet());

        // Sort the list
        Collections.sort(list, new Comparator<Map.Entry<VertexLocation, Integer> >() {
            public int compare(Map.Entry<VertexLocation, Integer> o1,
                               Map.Entry<VertexLocation, Integer> o2)
            {
                return (-1)*(o1.getValue()).compareTo(o2.getValue());
            }
        });

        // put data from sorted list to hashmap
        HashMap<VertexLocation, Integer> temp = new LinkedHashMap<VertexLocation, Integer>();
        for (Map.Entry<VertexLocation, Integer> aa : list) {
            temp.put(aa.getKey(), aa.getValue());
        }
        return temp;
    }

    public void rollStage(Game g){
		if (g.over()) {
			GameRunner.setWinner(g.winningPlayer());
			//System.out.println(g.winningPlayer().getName() + "won");
		}
		int roll = g.roll(g.getCurrentPlayer());
		//System.out.println("rolled" + roll);
	}

	public boolean makeOneMove(String move, Game game){
		if(move.startsWith("SNR")){
			VertexLocation place = findLocation(move.substring(3,5));
			return(addSettlementNoRoad(game,place));
		}
		if(move.startsWith("S")){
			VertexLocation place = findLocation(move.substring(1,3));
			return(addSettlement(game,place));
		}
		if(move.startsWith("C")){
			VertexLocation place = findLocation(move.substring(1,3));
			return(addCity(game,place));
		}
		if(move.startsWith("R")){
			int location = Integer.parseInt(move.substring(1,3));
			EdgeLocation place = new EdgeLocation(location/100,(location%100)/10,location%10);
			return(addRoad(game,place));
		}
		if(move.equals("N")){
			return true;
		}
		if(move.equals("BDv")){
		    return(addDevCard(game));
        }
		if(move.startsWith("T")){
		    //printResources(this);
			int i1,i2;
			String resource = new String();
			i1 = Integer.parseInt(String.valueOf(move.charAt(2)));
			i2 = Integer.parseInt(String.valueOf(move.charAt(3)));

			if(i2==1){
                resource = "BRICK";
            }
            else if(i2==2) {
                resource = "WOOL";
            }
            else if(i2==3) {
                resource = "ORE";
            }
            else if(i2==4) {
                resource = "GRAIN";
            }
            else{
                resource = "LUMBER";
            }
			if(move.startsWith("T2")){
				switch (i1){
					case 1:
						game.npcTrade(this,resource,twoBricks);
					case 2:
						game.npcTrade(this,resource,twoWool);
					case 3:
						game.npcTrade(this,resource,twoOre);
					case 4:
						game.npcTrade(this,resource,twoGrain);
					case 5:
						game.npcTrade(this,resource,twoLumber);
				}
			}
			else if(move.startsWith("T3")){
				switch (i1){
					case 1:
						game.npcTrade(this,resource,threeBricks);
					case 2:
						game.npcTrade(this,resource,threeWool);
					case 3:
						game.npcTrade(this,resource,threeOre);
					case 4:
						game.npcTrade(this,resource,threeGrain);
					case 5:
						game.npcTrade(this,resource,threeLumber);
				}
			}
			else if(move.startsWith("T4")){
				switch (i1){
					case 1:
						game.npcTrade(this,resource,fourBricks);
					case 2:
						game.npcTrade(this,resource,fourWool);
					case 3:
						game.npcTrade(this,resource,fourOre);
					case 4:
						game.npcTrade(this,resource,fourGrain);
					case 5:
						game.npcTrade(this,resource,fourLumber);
				}

			}
            //printResources(this);
		}
		return false;
	}

	private VertexLocation findLocation(String string){
		int location = Integer.parseInt(string);
		return new VertexLocation(location/100,(location%100)/10,location%10);
	}

	public boolean randomMove(Game game){
		HashSet<String> possibleMoves = this.possibleMoves(game);
		return makeOneMove(possibleMoves.iterator().next(),game);
	}

	public boolean makeOneMoveRandom(Game game) {
        int i = randInt(1, 11);
        for(int k=0;k<game.getPlayers().size();k++){
            if(game.getPlayers().get(k).tooMuch()){
                boolean tradeFour = false;
                while(tradeFour){
                    HashSet<String> possibleTrade = new HashSet<>();
                    possibleTrade = possibleTradeWithStock(possibleTrade);
                    if (possibleTrade.iterator().hasNext()) {
                        String trade = possibleTrade.iterator().next();
                        makeOneMove(trade, game);
                        return true;
                    }
                }
            }
        }
        if (i == 1) {
            return true;
        } else if (i <= 4 && i > 1) {
            //buy settlement
            HashSet<VertexLocation> placesForSett = game.getBoard().availablePlacesSet(this);
            if (placesForSett.iterator().hasNext()) {
                VertexLocation place = placesForSett.iterator().next();
                if (addSettlementNoRoad(game, place)) {
                    //System.out.println("Sett placed");
                    return true;
                }
            }
            makeOneMoveRandom(game);
        } else if (i==5) {
            //PLACE ROAD
            HashSet<EdgeLocation> placesForRoads = game.getBoard().availablePlacesRoad(this);
            HashSet<VertexLocation> placesForSet = game.getBoard().availablePlacesSet(this);
            HashSet<VertexLocation> placesForCiti = game.getBoard().availablePlacesCity(this);
            if (placesForRoads.iterator().hasNext()) {
                EdgeLocation place = placesForRoads.iterator().next();
                if (addRoad(game, place)) {
                    //System.out.println("Road place");
                    return true;
                }
            }
            makeOneMoveRandom(game);
        } else if (i < 9 && 5 < i) {
            //PLACE CITY
            HashSet<VertexLocation> placesForCities = game.getBoard().availablePlacesCity(this);
            if (placesForCities.size() > 0 && placesForCities.iterator().hasNext()) {
                VertexLocation place = placesForCities.iterator().next();
                if (addCity(game, place)) {
                    return true;
                }
                makeOneMoveRandom(game);
            }
        } else if (i < 10 && 9 <= i) {
            //DO TRADE
            HashSet<String> possibleTrade = new HashSet<>();
            possibleTrade = possibleTradeWithStock(possibleTrade);
            if (possibleTrade.iterator().hasNext()) {
                String trade = possibleTrade.iterator().next();
                ///System.out.println(trade + "TTT");
                makeOneMove(trade, game);
                return true;
            }
            makeOneMoveRandom(game);
        } else if (i == 11) {
            //BUT DEV CARD{
            if (game.canBuyDevCard(this) == 0) {
                makeOneMove("BDv", game);
                return true;
            }
            makeOneMoveRandom(game);
        }
        return false;
	}

	public HashSet<String> possibleMoves(Game game){
		HashSet<String> possibleMoves = new HashSet<>();
		Integer num = 0;
		//do nothing
		possibleMoves.add("N");

		HashSet<VertexLocation> placesForSett = game.getBoard().availablePlacesSet(this);
		if(placesForSett.size()>0){
			for(VertexLocation placeSet: placesForSett){
				if(game.canAddSettlement(this)==0){
					num = placeSet.getXCoord()*100+placeSet.getYCoord()*10+placeSet.getOrientation();
					possibleMoves.add("S".concat(Integer.toString(num)));
				}
			}
		}

		HashSet<VertexLocation> placesForCities = game.getBoard().availablePlacesCity(this);
		if(placesForCities.size()>0){
			for(VertexLocation placeCity: placesForCities){
				if(game.canBuyCity(this)==0){
					num = placeCity.getXCoord()*100+placeCity.getYCoord()*10+placeCity.getOrientation();
					possibleMoves.add("C".concat(Integer.toString(num)));
				}
			}
		}

		HashSet<EdgeLocation> placesForRoads = game.getBoard().availablePlacesRoad(this);
		if(placesForRoads.size()>0){
			for(EdgeLocation placeRoad : placesForRoads) {
				if(game.canBuyRoad(this)==0){
					num = placeRoad.getXCoord() * 100 + placeRoad.getYCoord() * 10 + placeRoad.getOrientation();
					possibleMoves.add("R".concat(Integer.toString(num)));
				}
			}
		}
		possibleMoves = possibleTradeWithStock(possibleMoves);

		if(game.canBuyDevCard(this)==0){
		    possibleMoves.add("BDv");
        }
        //printResources(this);
		//System.out.println(possibleMoves);
		return possibleMoves;
	}

	public HashSet<String> possibleTradeWithStock(HashSet<String> possibleMoves){
		boolean[] ports = this.getPorts();
		if(!ports[0]){
            if (this.hasResources(fourBricks)&&!ports[1]) {
                possibleMoves.add("T4".concat(Integer.toString(12)));
                possibleMoves.add("T4".concat(Integer.toString(13)));
                possibleMoves.add("T4".concat(Integer.toString(14)));
                possibleMoves.add("T4".concat(Integer.toString(15)));
            }
            if (this.hasResources(fourWool)&&!ports[2]) {
                possibleMoves.add("T4".concat(Integer.toString(21)));
                possibleMoves.add("T4".concat(Integer.toString(23)));
                possibleMoves.add("T4".concat(Integer.toString(24)));
                possibleMoves.add("T4".concat(Integer.toString(25)));
            }
            if (this.hasResources(fourOre)&&!ports[3]) {
                possibleMoves.add("T4".concat(Integer.toString(31)));
                possibleMoves.add("T4".concat(Integer.toString(32)));
                possibleMoves.add("T4".concat(Integer.toString(34)));
                possibleMoves.add("T4".concat(Integer.toString(35)));
            }
            if (this.hasResources(fourGrain)&&!ports[4]) {
                possibleMoves.add("T4".concat(Integer.toString(41)));
                possibleMoves.add("T4".concat(Integer.toString(42)));
                possibleMoves.add("T4".concat(Integer.toString(43)));
                possibleMoves.add("T4".concat(Integer.toString(45)));
            }
            if (this.hasResources(fourLumber)&&!ports[5]) {
                possibleMoves.add("T4".concat(Integer.toString(51)));
                possibleMoves.add("T4".concat(Integer.toString(52)));
                possibleMoves.add("T4".concat(Integer.toString(53)));
                possibleMoves.add("T4".concat(Integer.toString(54)));
            }
        }
		if(ports[0]){
			if(this.hasResources(threeBricks)&&!ports[1]){
				possibleMoves.add("T3".concat(Integer.toString(12)));
				possibleMoves.add("T3".concat(Integer.toString(13)));
				possibleMoves.add("T3".concat(Integer.toString(14)));
				possibleMoves.add("T3".concat(Integer.toString(15)));
			}
			if(this.hasResources(threeWool)&&!ports[2]){
				possibleMoves.add("T3".concat(Integer.toString(21)));
				possibleMoves.add("T3".concat(Integer.toString(23)));
				possibleMoves.add("T3".concat(Integer.toString(24)));
				possibleMoves.add("T3".concat(Integer.toString(25)));
			}
			if(this.hasResources(threeOre)&&!ports[3]){
				possibleMoves.add("T3".concat(Integer.toString(31)));
				possibleMoves.add("T3".concat(Integer.toString(32)));
				possibleMoves.add("T3".concat(Integer.toString(34)));
				possibleMoves.add("T3".concat(Integer.toString(35)));
			}
			if(this.hasResources(threeGrain)&&!ports[4]){
				possibleMoves.add("T3".concat(Integer.toString(41)));
				possibleMoves.add("T3".concat(Integer.toString(42)));
				possibleMoves.add("T3".concat(Integer.toString(43)));
				possibleMoves.add("T3".concat(Integer.toString(45)));
			}
			if(this.hasResources(threeLumber)&&!ports[5]){
				possibleMoves.add("T3".concat(Integer.toString(51)));
				possibleMoves.add("T3".concat(Integer.toString(52)));
				possibleMoves.add("T3".concat(Integer.toString(53)));
				possibleMoves.add("T3".concat(Integer.toString(54)));
			}
		}
		if(ports[1]&&this.hasResources(twoBricks)){
			possibleMoves.add("T2".concat(Integer.toString(12)));
			possibleMoves.add("T2".concat(Integer.toString(13)));
			possibleMoves.add("T2".concat(Integer.toString(14)));
			possibleMoves.add("T2".concat(Integer.toString(15)));
		}
		if(ports[2]&&this.hasResources(twoWool)){
			possibleMoves.add("T2".concat(Integer.toString(21)));
			possibleMoves.add("T2".concat(Integer.toString(23)));
			possibleMoves.add("T2".concat(Integer.toString(24)));
			possibleMoves.add("T2".concat(Integer.toString(25)));
		}
		if(ports[3]&&this.hasResources(twoOre)){
			possibleMoves.add("T2".concat(Integer.toString(31)));
			possibleMoves.add("T2".concat(Integer.toString(32)));
			possibleMoves.add("T2".concat(Integer.toString(34)));
			possibleMoves.add("T2".concat(Integer.toString(35)));
		}
		if(ports[4]&&this.hasResources(twoGrain)){
			possibleMoves.add("T2".concat(Integer.toString(41)));
			possibleMoves.add("T2".concat(Integer.toString(42)));
			possibleMoves.add("T2".concat(Integer.toString(43)));
			possibleMoves.add("T2".concat(Integer.toString(45)));
		}
		if(ports[5]&&this.hasResources(twoLumber)){
			possibleMoves.add("T2".concat(Integer.toString(51)));
			possibleMoves.add("T2".concat(Integer.toString(52)));
			possibleMoves.add("T2".concat(Integer.toString(53)));
			possibleMoves.add("T2".concat(Integer.toString(54)));
		}
		return possibleMoves;
	}

	public static int randInt(int min, int max) {
		Random rand = new Random();
		int randomNum = rand.nextInt((max - min) + 1) + min;
		return randomNum;
	}

	public boolean firstTurn(Game game, int i){
        if(i==1){
            HashMap<VertexLocation, Integer> myMap = versRank(game);
            Map.Entry<VertexLocation,Integer> entry = myMap.entrySet().iterator().next();
            VertexLocation v = entry.getKey();
            game.getBoard().placeStructureNoRoad(v, this);
            //System.out.println("SET"+v.getXCoord()+v.getYCoord());

        }
        if(i==2){
            HashSet<EdgeLocation> placesForRoads = game.getBoard().availablePlacesRoad(this);
            for(EdgeLocation place:placesForRoads){
                if(addRoad(game,place)){
                    return true;
                }
            }
        }
        return false;
    }

    private void printResources(Player p){
        System.out.print(this.getNumberResourcesType("BRICK"));
        System.out.print(" ");
        System.out.print(this.getNumberResourcesType("WOOL"));
        System.out.print(" ");
        System.out.print(this.getNumberResourcesType("ORE"));
        System.out.print(" ");
        System.out.print(this.getNumberResourcesType("GRAIN"));
        System.out.print(" ");
        System.out.println(this.getNumberResourcesType("LUMBER"));
    }
}
