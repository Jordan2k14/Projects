

// 
// Bouncing Cube Java Project IST Module - INSA LYON
// By Jordan Ukawoko, Daniel Bodlund & Wilmer Gunnarson
// Created in VSCODE and Java Eclipse 
// All References will be put in our documentation 
package bouncingCube; // We need to package our file first

// These imports are very important for the characteristics of the games. These are our
// Abstract Classes & Interfaces. We used library imports for the game
import java.awt.Color; // For Colour
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
import javax.swing.JFrame; // This is our GUI
import javax.swing.Timer;

// All of these imports give flavour to our game 

public class BouncingCube implements ActionListener, MouseListener, KeyListener, addColumn, jump // implementing abstract classes
{

	public static BouncingCube bouncingCube;
	public final int WIDTH = 800, HEIGHT = 800;

	
	// We are setting the shapes
	public Renderer renderer;
	public Rectangle cube; // the shape is a cube
	
	
	public ArrayList<Rectangle> columns;
	public int ticks, yvelocity, score; // needed for the speed and displaying the score
	public boolean youLost, start_game;
	public Random rand; // Randomising
	
	public BouncingCube()
	{
		JFrame jframe = new JFrame();
		Timer timer = new Timer(20, this);
		renderer = new Renderer();
		rand = new Random();

		jframe.add(renderer);
		jframe.setTitle("Bouncing Cube - Jordan, Daniel and Wilmer"); // Setting the title of the game on GUI
		jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Closing the GUI
		jframe.setSize(WIDTH, HEIGHT); // Very important to get our height and width
		jframe.addMouseListener(this);
		jframe.addKeyListener(this);
		jframe.setResizable(false);
		jframe.setVisible(true);

		cube = new Rectangle(WIDTH / 2 - 10, HEIGHT / 2 - 10, 20, 20);
		columns = new ArrayList<Rectangle>();
		newaddColumn(true);
		newaddColumn(true);
		newaddColumn(true);
		newaddColumn(true);

		timer.start();
	}

	
	
	
	public void newaddColumn(boolean start) // Adding a new column, calling from abstract class
	{   // Setting the dimensions
		int space = 300;
		int width = 100; 
		int height = 50 + rand.nextInt(300);

		if (start)
		{
			columns.add(new Rectangle(WIDTH + width + columns.size() * 300, HEIGHT - height - 120, width, height));
			columns.add(new Rectangle(WIDTH + width + (columns.size() - 1) * 300, 0, width, HEIGHT - height - space));
		}
		else
		{
			columns.add(new Rectangle(columns.get(columns.size() - 1).x + 600, HEIGHT - height - 120, width, height));
			columns.add(new Rectangle(columns.get(columns.size() - 1).x, 0, width, HEIGHT - height - space));
		}
	}

	public void paintColumn(Graphics g, Rectangle column) // We are painting the columns needed for the game
	{
		g.setColor(Color.green.darker()); // We decided to go with green for the colour
		g.fillRect(column.x, column.y, column.width, column.height);
	}

	public void newjump() // This function is so our cube can jump, we are calling from the abstract class
	{
		if (youLost)
		{
			cube = new Rectangle(WIDTH / 2 - 10, HEIGHT / 2 - 10, 20, 20);
			columns.clear();
			yvelocity = 0;
			score = 0;

			newaddColumn(true);
			newaddColumn(true);
			newaddColumn(true);
			newaddColumn(true);
			
			youLost = false;
		}

		if (!start_game)
		{
			start_game = true;
		}
		else if (!youLost)
		{
			if (yvelocity > 0)
			{
				yvelocity = 0;
			}

			yvelocity -= 10;
		}
	}

	
	
	@Override
	public void actionPerformed(ActionEvent e) // abstract class
	{
		int velocity = 8; // We will set the velocity to 8. Changing this variable can make the game harder e.g if we
		// set the velocity to 100 the cube will move very fast. Setting it to 1 can also make the game a lot easier
		// This value is modifiable. 

		ticks++;

		if (start_game)
		{
			for (int i = 0; i < columns.size(); i++)
			{
				Rectangle column = columns.get(i);

				column.x -= velocity;
			}

			if (ticks % 2 == 0 && yvelocity < 15)
			{
				yvelocity += 2;
			}

			for (int i = 0; i < columns.size(); i++)
			{
				Rectangle column = columns.get(i);

				if (column.x + column.width < 0)
				{
					columns.remove(column);

					if (column.y == 0)
					{
						newaddColumn(false);
					}
				}
			}

			cube.y += yvelocity;

			
			
			for (Rectangle column : columns)
			{
				if (column.y == 0 && cube.x + cube.width / 2 > column.x + column.width / 2 - 10 && cube.x + cube.width / 2 < column.x + column.width / 2 + 10)
				{
					score++;
				}

				if (column.intersects(cube))
				{
					youLost = true;

					if (cube.x <= column.x)
					{
						cube.x = column.x - cube.width;

					}
					else
					{
						if (column.y != 0)
						{
							cube.y = column.y - cube.height;
						}
						else if (cube.y < column.height)
						{
							cube.y = column.height;
						}
					}
				}
			}

			if (cube.y > HEIGHT - 120 || cube.y < 0)
			{
				youLost = true;
			}

			if (cube.y + yvelocity >= HEIGHT - 120)
			{
				cube.y = HEIGHT - 120 - cube.height;
				youLost = true;
			}
		}

		renderer.repaint();
	}

	public void repaint(Graphics g) // We are repainting over here (abstract class for graphics - imported)
	{
		g.setColor(Color.blue); // we decided to go with blue
		g.fillRect(0, 0, WIDTH, HEIGHT);

		g.setColor(Color.red); // we decided to go with red
		g.fillRect(0, HEIGHT - 120, WIDTH, 120);

		g.setColor(Color.green); // we decided to go with green
		g.fillRect(0, HEIGHT - 120, WIDTH, 20);

		g.setColor(Color.yellow); // we decided to go with yellow
		g.fillRect(cube.x, cube.y, cube.width, cube.height);

		for (Rectangle column : columns)
		{
			paintColumn(g, column);
		}

		g.setColor(Color.white);
		g.setFont(new Font("Arial", 1, 100));

		if (!start_game)
		{
			g.drawString("Play Now", 75, HEIGHT / 2 - 50);
		}

		if (youLost)
		{
			g.drawString("Try Again!", 100, HEIGHT / 2 - 50);
		}

		if (!youLost && start_game)
		{
			g.drawString(String.valueOf(score), WIDTH / 2 - 25, 100);
		}
	}

	public static void main(String[] args)
	{
		bouncingCube = new BouncingCube();
	}
// classes
	@Override
	public void mouseClicked(MouseEvent e)
	{
		newjump();
	}

	@Override
	public void keyReleased(KeyEvent e)
	{
		if (e.getKeyCode() == KeyEvent.VK_SPACE)
		{
			newjump();
		}
	}
	
	
	// All of these classes are needed so our game functions e.g click space for the cube to move etc etc
	@Override
	public void mousePressed(MouseEvent e)
	{
	}

	@Override
	public void mouseReleased(MouseEvent e)
	{
	}

	@Override
	public void mouseEntered(MouseEvent e)
	{
	}

	@Override
	public void mouseExited(MouseEvent e)
	{
	}

	@Override
	public void keyTyped(KeyEvent e)
	{

	}

	@Override
	public void keyPressed(KeyEvent e)
	{

	}




	@Override
	public void newaddColumn() {
		// TODO Auto-generated method stub
		
	}

}

// Finish 