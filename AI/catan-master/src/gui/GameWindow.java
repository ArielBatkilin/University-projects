package gui;

import board.Board;
import game.*;

import java.awt.Button;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.awt.event.*;
import java.util.ArrayList;

import javax.swing.*;

import lib.GraphPaperLayout;


public class GameWindow {
		
    CatanBoard board;
	public final static int INTERVAL = 20;
	
	
	final static int SCRSIZE = 1000; //TODO specify
	
	
	public GameWindow(ArrayList<Player> players) {
		board = new CatanBoard(players);
		createAndShowGUI();

		Timer timer = new Timer(INTERVAL,
				new ActionListener() {
					public void actionPerformed(ActionEvent evt) {
						// Refresh the board
						board.repaint(); //TODO fix validate
					}
				});

		timer.start();
	}

    public GameWindow(Game game) {
	    board = new CatanBoard(game);
        createAndShowGUI();
        repaint();
    }
	
	private void createAndShowGUI() {
		
		JFrame frame = new JFrame("Catan");
		frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		Dimension d = new Dimension(4,4);

		frame.setSize(SCRSIZE+200, SCRSIZE+200);
		//frame.setLayout(new GraphPaperLayout(d));
		Container content = frame.getContentPane();
		content.setLayout(new GraphPaperLayout(d));
		//content.add(board);
		content.add(board,new Rectangle(0,0,4,4));

		
		frame.setResizable(true);
		frame.setLocationRelativeTo(null);
		
		frame.setVisible(true);
		
		board.repaint();
	}
	
	public CatanBoard getBoard() {
		return board;
	}

	public void repaint(){
		board.repaint();
	}
}
