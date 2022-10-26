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

@Override

public void actions(ActionEvent e)
{
    int velocity = 11;
    ticks++;

    if (started)
    {
        for (int i = 0; i < columns.size(); i++)
			{
				Rectangle column = columns.get(i);

				column.x -= velocity;
			}

            if (ticks % 2 == 0 && ysurface < 15)
            {
                ysurface += 2;
            }

            for (int i = 0; i < columns.size(); i++)
            {
                Rectangle column = columns.get(i);

                if(column.x + column.width < 0)
                {
                    columns.remove(column);
                    if (column.y == 0)
                    {
                        addColumn(false);
                    }
                }
            }

            cube.y += ysurface;

            for (Rectangle column : columns){
                if (column.y == 0 && cube.x + cube.width / 2 > column.x + column.width / 2 - 10 && cube.x + cube.width / 2 < column.x + column.width / 2 + 10)
                {
                    score++;
                }

                if (column.intersects(cube))
                {
                    gameOver = true;
                    if (cube.x <= column.x)
                }
                else{
                    if (columny != 0)
                    {
                        cube.y = column.y - cube.height;
                    }
                    else if (cube.y < column.height)
                    {
                        cube.y = column.height
                    }
                }
            }
    if (cube.y > HEIGHT - 120 || cube.y < 0)
			{
				gameOver = true;
			}

			if (bird.y + ysurface >= HEIGHT - 120)
			{
				cube.y = HEIGHT - 120 - cube.height;
				gameOver = true;
			}
        }

        renderer.paint();
    }