package game;


import gui.GameWindow;

import java.util.ArrayList;
import java.util.HashSet;

public class MonteCarlo {

	private static int number;
	private double explorationRate;
	private Node<State> searchTree;

	public MonteCarlo(State s_0,double explorationRate,int iterations){
		this.searchTree = new Node<State>(s_0);
		this.explorationRate = explorationRate;
		this.number = iterations;
	}


	public String UctSearch(State s_0){
        double R = 0.0;
        R += simulate(s_0);
        String a = UCB1(s_0);
        State s = new State(s_0,a);
		for (int i=0; i<number-1; i++){
            R += simulate(s);
            a = UCB1(s);
            s = new State(s,a);
		}
        backup(searchTree,R);
		HashSet<String> actions = s_0.getActions();
		double maxVal = 0;
		String bestAction = "N";
		for (String action: actions){
			if (s_0.getQAVal(action) > maxVal){
				maxVal = s_0.getQAVal(action);
				bestAction = action;
			}
		}
        System.out.println(bestAction+"//////");
		return bestAction;
	}

	public double simulate(State s_0){
	    GameWindow tmp = new GameWindow(s_0.getGame());
		double R = 0;
		String a = "N";
		State s_t = s_0;
		while(!s_t.isTerminal()){
			a = s_t.defaultPolicy();
			R = R + addValue(a);
		}
		if (s_t.getGame().winningPlayer().getName().equals(s_t.getMyPlayer().getName())){
			R+=1;
		}
		return R;
	}

	public double addValue(String s){
	    if(s.startsWith("C")){
	        return 2;
        }
        if(s.startsWith("S")){
            return 1;
        }
        if(s.startsWith("R")){
            return 0.5;
        }
        if(s.startsWith("T")){
            return 0.25;
        }
        if(s.startsWith("BDv")){
            return 0.5;
        }
        return 0;
    }

	public String UCB1(State s){
		HashSet<String> actions = s.getActions();
		double maxVal = 0;
		String bestAction = "N";
		for (String action: actions){
			int denominator = s.getNAVal(action);
			double val;
			if (denominator != 0){
				val = s.getQAVal(action) + explorationRate*Math.sqrt((2*(Math.log(s.getNVal())))/s.getNAVal
						(action));
			}
			else {
				val = s.getQAVal(action);
			}
			if (val > maxVal){
				maxVal = val;
				bestAction = action;
			}
		}
		return bestAction;
	}

	public void backup(Node<State> newNode, double R){
		double addedVal = 0;
		State state;
		while (!newNode.isRoot()){
            state = newNode.getData();
			HashSet<String> actions = state.getActions();
			state.setNVal(state.getNVal() + 1);
			for (String action: actions){
				if(state.getNAVal(action)!=0){
					addedVal = (R-state.getQAVal(action))/state.getNAVal(action);
				}
				state.setNAVal(action, state.getNAVal(action) + 1);
				state.setQAVal(action, (state.getQAVal(action) + addedVal));
			}
		}
	}

	public State newNode(State s){
		String a = s.defaultPolicy();
		State s_t = new State(s,a);
		Node<State> oldNode = new Node<State>(s);
		Node<State> newNode  = new Node<State>(s_t,oldNode);
		if(!searchTree.isInTree(oldNode)){
            searchTree.addChild(newNode);
        }
        return s_t;
	}
}
