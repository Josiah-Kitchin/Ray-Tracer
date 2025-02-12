
package com.ray_application.ui.components; 

import javax.swing.*; 
import java.awt.image.BufferedImage; 
import java.awt.*; 

import java.awt.Dimension;  
import java.awt.Graphics;



public class ImagePanel extends JPanel 
{
    private BufferedImage m_image; 
    private int m_width, m_height; 

    public ImagePanel(int width, int height)
    {
        m_image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        setPreferredSize(new Dimension(width, height));
        revalidate();
        repaint();
    }

    public ImagePanel(BufferedImage image, int setHeight)
    {
        setImage(image, setHeight);
    }

    public void setImage(BufferedImage image, int setHeight)
    {
        int originalWidth = image.getWidth(); 
        int originalHeight = image.getHeight(); 

        double aspectRatio = (double) originalWidth / originalHeight; 
        m_height = setHeight; 
        m_width = (int) (setHeight * aspectRatio);

        m_image = new BufferedImage(m_width, m_height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = m_image.createGraphics();
        g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BICUBIC);
        g2d.drawImage(image, 0, 0, m_width, m_height, null);
        g2d.dispose();
        setPreferredSize(new Dimension(m_width, m_height));
        revalidate(); 
        repaint();
    }

    public void updateImage(BufferedImage image)
    {
        setImage(image, m_height);
    }

    @Override
    protected void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        if (m_image != null)
        {
            g.drawImage(m_image, 0, 0, m_width, m_height, this);
        }
    }
}
