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

public void jump()
{
    if (gameOver)
    {
        cube = new Rectangle(WIDTH / 2 - 10, HEIGHT / 2 - 10, 20, 20);
        columns.clear
        ysurfance = 0;
        score = 0;

        addColumn(true);
		addColumn(true);
		addColumn(true);
		addColumn(true);
        gameOver = false;
    }
    if (!started)
    {
        started = true;
    }
    else if (!gameOver)
    {
        if (ysurfance > 0)
        {
            ysurfance = 0;
        }
        ysurface -= 10;
    }
}