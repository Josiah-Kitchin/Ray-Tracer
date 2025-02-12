
package com.ray_application.ui; 

import com.ray_application.ui.components.*; 
import com.ray_application.Controller; 
import com.ray_application.sceneCreater.Engine; 

import javax.swing.*; 
import java.awt.*; 


public class MainUI
{

    private static ImagePanel imagePanel; 

    public static void main()
    {
        SwingUtilities.invokeLater(() -> {;
            // Window setup
            JFrame frame = new JFrame("Ray Tracer");
            int frameWidth = 2000, frameHeight = 2000; 
            frame.setSize(frameWidth, frameHeight);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setLayout(new FlowLayout());
            frame.getContentPane().setBackground(new Color(30, 30, 30));

            // Create an empty image 
            imagePanel = new ImagePanel(1000, 750);

            addImageContainer(imagePanel, frame);
            addButtonsContainer(frame);

            frame.setVisible(true);
        }); 
    }

    private static void addImageContainer(ImagePanel image, JFrame frame)
    {
        // Upper panel meant for viewing the rendered image 
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
        buttonContainer.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10)); // Center aligned, with spacing
        buttonContainer.setPreferredSize(new Dimension(frame.getWidth(), frame.getHeight() / 3));
        buttonContainer.setBackground(new Color(30, 30, 30));
        
        // Add Object button 
        JButton addObject = new RayButton("Add Object", 200, 50);
        buttonContainer.add(addObject);

        // Render button 
        Engine engine = new Engine("resources/");
        Controller controller = new Controller(engine); 
        JButton render = new RayButton("Render", 200, 50);
        controller.setButtonToRenderImage(render, imagePanel);
        buttonContainer.add(render);

        // Add Light button 
        JButton addLight = new RayButton("Add Light", 200, 50);
        buttonContainer.add(addLight);

        frame.add(buttonContainer);
    }
}

