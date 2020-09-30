package game;

import board.*;
import gui.GameWindow;

import java.awt.*;
import java.util.*;
import java.lang.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.concurrent.TimeUnit;

import javax.swing.SwingUtilities;

public class GameRunner {
	
	private static Player currentPlayer;
	private static int numberPlayers;
	private static GameWindow tmp;
	private static int index = 0;
	private static ArrayList<Player> players = new ArrayList<Player>();
	private static Game game;
	private static Player winner;
	private static int rounds;
	private static final int ROUNDS = 10000;
	private static boolean slowMotion = false;

	public static void main(String[] args) {



//		Player p1 = new Player("DevMaster",	Color.BLACK , 4,1,1,1,1,2,"AI");
//		players.add(p1);
		AIPlayer p2 = new AIPlayer("AI1", Color.RED);
		players.add(p2);
		AIPlayer p3 = new AIPlayer("AI2", Color.BLUE);
		players.add(p3);
		AIPlayer p4 = new AIPlayer("AI3", Color.ORANGE);
		players.add(p4);
		AIPlayer p5 = new AIPlayer("AI4", Color.BLACK);
		players.add(p5);
		numberPlayers = players.size();
		Game game = new Game(players);

		//playMonteCarlo(game,p3,0.5,10);
		System.out.println((Simulate(new Game(game),"AI2",100,false)));
//		game = (runNTurns(game, "AI2",rounds,true));

	}
	public static void playMonteCarlo(Game game,Player player,double exRate, int iterations){
		firstTurn(game,game.getPlayers());
		//runNTurns(game,player.getName(),4,true);
		//tmp = new GameWindow(game);
		int i=0;
		String action = "N";
		while(!game.over()){
			game.getPlayers().get(i).rollStage(game);
			if(game.getCurrentPlayer().getName().equals(player.getName())){
				State start = new State(game);
				if(start.getActions().size()==1&&start.getActions().contains("N")){
					game.getPlayers().get(i).makeOneMove("N",game);
					game.nextPlayer();
					continue;
				}
				MonteCarlo monteCarlo = new MonteCarlo(start,exRate,iterations);
				action = monteCarlo.UctSearch(start);
				game.getPlayers().get(i).makeOneMove(action,game);
				if (game.getPlayers().get(i).getVictoryPoints() >= 10) {
					Player cur = game.getPlayers().get(i);
					if (cur.getName().equals(player.getName())) {
						return;
					}
				}
			}
			else {
				while (!game.over() && !game.getPlayers().get(i).makeOneMoveRandom(game)) {
					if (game.getPlayers().get(i).getVictoryPoints() >= 10) {
						Player cur = game.getPlayers().get(i);
						//System.out.println(cur.getName()+"WON");
						if (cur.getName().equals(player.getName())) {
							return;
						}
					}
				}
			}
			i = (i+1)%4;
			game.nextPlayer();
		}
		tmp = new GameWindow(game);
	}

	public static int Simulate(Game game, String name, int num,boolean display){
		ArrayList<Player> players = game.getPlayers();
		int winCount = 0;
		Game newGame;
		for(int i=0;i<num;i++){
			newGame = new Game(game);
			winCount += (playSingleGame(newGame, name,display));
		}
		return winCount;
	}

	public static Player getCurrentPlayer() {
		return currentPlayer;
	}

	public static GameWindow getTmpy() {
		return tmp;
	}

	public static void nextPlayer() {
		currentPlayer = players.get((index + 1) % 4);
		index = (index + 1) % 4;
	}

	public static int playSingleGame(Game game,String name,boolean display){
		firstTurn(game, game.getPlayers());
		tmp = new GameWindow(game);
		int i = 0;
		rounds = ROUNDS;
		boolean over = false;
		while(!over&&rounds>0){
			rounds = rounds -1;
			game.getPlayers().get(i).rollStage(game);
			while(!over&&!game.getPlayers().get(i).makeOneMoveRandom(game))
			{
				if(game.getPlayers().get(i).getVictoryPoints()>=10){
					Player cur = game.getPlayers().get(i);
					if(cur.getName().equals(name)){
						if(display){
							tmp = new GameWindow(game);
						}
						return 1;
					}
				}
			}
			if(slowMotion) {
				try {
					TimeUnit.MILLISECONDS.sleep(100);
					tmp.repaint();
				} catch (InterruptedException ie) {

				}
			}
			i = (i+1)%4;
			nextPlayer();
		}
		if(display){
			tmp = new GameWindow(game);
		}
		return 0;
	}

	public static void runNTurns(Game game,String name,int n,boolean display) {
		//firstTurn(game, game.getPlayers());
		int i = 0;
		int rounds = n;
		boolean over = false;
		while (!over && rounds > 0) {
			rounds = rounds - 1;
			game.getPlayers().get(i).rollStage(game);
			while (!over && !game.getPlayers().get(i).makeOneMoveRandom(game)) {
				if (game.getPlayers().get(i).getVictoryPoints() >= 10) {
					over = true;
				}
				i = (i + 1) % 4;
				nextPlayer();
			}
			if (display) {
				tmp = new GameWindow(game);
			}
			return;
		}
		return;
	}

	public static void firstTurn(Game game, ArrayList<Player> players){
		players.get(0).firstTurn(game,1);
		players.get(0).firstTurn(game,2);
		players.get(1).firstTurn(game,1);
		players.get(1).firstTurn(game,2);
		players.get(2).firstTurn(game,1);
		players.get(2).firstTurn(game,2);
		players.get(3).firstTurn(game,1);
		players.get(3).firstTurn(game,2);
		players.get(3).firstTurn(game,1);
		players.get(3).firstTurn(game,2);
		players.get(2).firstTurn(game,1);
		players.get(2).firstTurn(game,2);
		players.get(1).firstTurn(game,1);
		players.get(1).firstTurn(game,2);
		players.get(0).firstTurn(game,1);
		players.get(0).firstTurn(game,2);
	}

	public static void prevPlayer() {
		currentPlayer = players.get((index - 1) % 4);
		index = (index - 1) % 4;
	}

	public static void setFirstPlayer() {
		currentPlayer = players.get(0);
	}

	public static void setCurrentPlayer(Player player){
		currentPlayer = player;
	}

	public static void setWinner(Player p) {
		winner = p;
	}

	public static Player getWinner() {
		return winner;
	}

	public static int getNumbPlayers() {
		return numberPlayers;
	}

	public static Player getPlayer(int i) {
		return players.get(i);
	}

	public static Game getGame(){
		return game;
	}
}
