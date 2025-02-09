
package com.ray_application.ui.components; 

import javax.swing.*; 
import java.awt.image.BufferedImage; 

import java.awt.Dimension;  
import java.awt.Graphics;


public class ImagePanel extends JPanel 
{
    private BufferedImage image; 
    private int width, height; 

    public ImagePanel(BufferedImage image, int width, int height)
    {
        this.image = image; 
        this.width = width; 
        this.height = height; 
        setPreferredSize(new Dimension(width, height));
    }

    public void resize(int newHeight) 
    {
        this.width = (width / height) * newHeight; 
        this.height = newHeight; 
        setPreferredSize(new Dimension(width, height));
    }

    @Override
    protected void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        if (image != null)
        {
            g.drawImage(image, 0, 0, width, height, this);
        }
    }
}
