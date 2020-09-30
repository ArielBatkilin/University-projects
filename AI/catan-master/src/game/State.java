package game;

import board.Deck;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;

import static game.AIPlayer.randInt;

public class State{
    private Game game;
    private int NValue;
    private HashMap<String,Integer> NAValues;
    private HashMap<String,Double> QAValues;
    private AIPlayer player;
    private HashSet<String> actions;
    private String index;

    public State(Game _game){
        this.NValue = 0;
        this.game = new Game(_game);
        this.player = new AIPlayer(game.getCurrentPlayer());
        this.actions = player.possibleMoves(game);
        System.out.println(actions);
        this.NAValues = new HashMap<>();
        this.QAValues = new HashMap<>();
        for(String action: actions){
            NAValues.put(action,0);
            QAValues.put(action,0.0);
        }
        this.index = "O";
    }

    public State(State other,String action){
        this.game = new Game(other.getGame());

        this.game.getCurrentPlayer().makeOneMove(action,this.game);

        this.game.nextPlayer();
        this.game.roll(this.game.getCurrentPlayer());
        this.game.getCurrentPlayer().makeOneMoveRandom(this.game);
        this.game.nextPlayer();
        this.game.roll(this.game.getCurrentPlayer());
        this.game.getCurrentPlayer().makeOneMoveRandom(this.game);
        this.game.nextPlayer();
        this.game.roll(this.game.getCurrentPlayer());
        this.game.getCurrentPlayer().makeOneMoveRandom(this.game);

        this.game.nextPlayer();
        this.game.roll(this.game.getCurrentPlayer());
        this.NValue = other.getNVal();
        this.player = new AIPlayer(this.game.getCurrentPlayer());
        this.actions = new HashSet<>();
        this.actions.addAll(other.getActions());
        this.NAValues = new HashMap<>();
        this.QAValues = new HashMap<>();
        for(String action1: this.actions){
            NAValues.put(action1,other.getNAVal(action1));
            QAValues.put(action1,other.getQAVal(action1));
        }
        this.index = other.getIndex().concat(action);
    }

    public void setNVal(int num){
        this.NValue = num;
    }
    public void setNAVal(String action,int num){
        this.NAValues.remove(action);
        this.NAValues.put(action,num);
    }
    public void setQAVal(String action, Double num){
        this.QAValues.remove(action);
        this.QAValues.put(action,num);
    }
    public int getNVal(){
        return this.NValue;
    }
    public int getNAVal(String action){
        return this.NAValues.get(action);

    }
    public Double getQAVal(String action){
        return this.QAValues.get(action);
    }

    public State doActions(String action){
        State newState = new State(this,action);
        Game newGame = new Game(this.game);

        newGame.getCurrentPlayer().makeOneMove(action,newState.game);

        newGame.nextPlayer();
        newGame.roll(newGame.getCurrentPlayer());
        newGame.getCurrentPlayer().makeOneMoveRandom(newGame);

        newGame.nextPlayer();
        newGame.roll(newGame.getCurrentPlayer());
        newGame.getCurrentPlayer().makeOneMoveRandom(newGame);

        newGame.nextPlayer();
        newGame.roll(newGame.getCurrentPlayer());
        newGame.getCurrentPlayer().makeOneMoveRandom(newGame);

        newGame.nextPlayer();
        newGame.roll(newGame.getCurrentPlayer());
        return newState;
    }

    public boolean isTerminal(){
        for(Player p:this.game.getPlayers()){
            if(p.getVictoryPoints()>=10){
                return true;
            }
        }
        if(this.game.isFinal()){
            return true;
        }
        return false;
    }


    public String defaultPolicy(){
        int size = this.actions.size();
        if(size>0){
            return actions.iterator().next();
        }
        return "N";
    }
    public HashSet<String> getActions(){
        return this.actions;
    }

    public Game getGame(){
        return this.game;
    }
    public Player getMyPlayer(){
        return this.player;
    }
    public String getIndex(){
        return this.index;
    }
    public String toString(){
        return index;
    }
}
