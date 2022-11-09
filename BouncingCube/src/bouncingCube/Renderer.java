package bouncingCube;

import java.awt.Graphics; // abstract class library

import javax.swing.JPanel;

public class Renderer extends JPanel // using Jpanel 
{

	private static final long serialVersionUID = 1L;

	@Override
	protected void paintComponent(Graphics g) // 
	{
		super.paintComponent(g); // abstract

		BouncingCube.bouncingCube.repaint(g);
	}
	
}

// Renderer Class is important for the function of our game 