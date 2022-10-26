package tappycube;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.ArrayList;
import java.util.Random;

import javax.swing.JFrame;
import javax.swing.Timer;


public class TappyCube implements ActionListener, MouseListener, KeyListener
{
    public static TappyCube tappycube;
    public final int WIDTH = 800, HEIGHT = 800;
    public Renderer renderer;
    public rectangle cube; // public rectangle bird
    public ArrayList<Rectangle> columns;
    public int tick, ysurfance, score; // public int ticks, yMotion, score
    public boolean youlost, start // public int gameOver, started
    public Random rand;


    public TappyCube(){
        JFrame jframe = new JFrame();
        Timer timer = new Timer(30, this);
        renderer = new Renderer();
        rand = new Random();


        jframe.add(renderer);
        jframe.setTitle("Tappy Cube");
		jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jframe.setSize(WIDTH, HEIGHT);
		jframe.addMouseListener(this);
		jframe.addKeyListener(this);
		jframe.setResizable(false);
		jframe.setVisible(true);

        cube = new Rectangle(WIDTH / 2 - 10, HEIGHT / 2 - 10, 20, 20);
		columns = new ArrayList<Rectangle>();

		addColumn(true);
		addColumn(true);
		addColumn(true);
		addColumn(true);
        
		timer.start();
        
    }
}