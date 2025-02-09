
package com.ray_application.ui; 

import com.ray_application.ui.components.*; 

import javax.swing.*; 
import java.awt.*; 
import java.awt.image.BufferedImage; 


public class MainUI
{
    
    public static void main(BufferedImage renderedImage)
    {
        SwingUtilities.invokeLater(() -> {;
            // Window setup
            JFrame frame = new JFrame("Ray Tracer");
            int frameWidth = 2000, frameHeight = 2000; 
            frame.setSize(frameWidth, frameHeight);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setLayout(new FlowLayout());
            frame.getContentPane().setBackground(new Color(30, 30, 30));

            addImageContainer(renderedImage, frame);
            addButtonsContainer(frame);

            frame.setVisible(true);
        }); 
    }


    private static void addImageContainer(BufferedImage imageBuffer, JFrame frame)
    {
        // Upper panel meant for viewing the rendered image 
        ImagePanel image = new ImagePanel(imageBuffer, imageBuffer.getWidth(), imageBuffer.getHeight());
        image.resize(600);

        JPanel imageContainer = new JPanel(); 
        imageContainer.setPreferredSize(new Dimension(frame.getWidth(), frame.getHeight() / 3));
        imageContainer.setBorder(BorderFactory.createLineBorder(new Color(10, 10, 10), 4));
        imageContainer.setBackground(new Color(20, 20, 20));
        imageContainer.add(image);
        frame.add(imageContainer);
    }

    private static void addButtonsContainer(JFrame frame)
    {
        // Control panel for creating the scene and rendering 
        JPanel buttonContainer = new JPanel(); 
        buttonContainer.setPreferredSize(new Dimension(frame.getWidth(), frame.getHeight() / 3));
        buttonContainer.setBackground(new Color(30, 30, 30));

        JButton button = new RayButton("Render", 100, 50);
        buttonContainer.add(button);

        frame.add(buttonContainer);

    }
}

