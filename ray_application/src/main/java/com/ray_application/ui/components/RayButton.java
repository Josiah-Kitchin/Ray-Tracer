

package com.ray_application.ui.components;

import javax.swing.*; 
import java.awt.*; 

public class RayButton extends JButton
/* Main button for the ui */ 
{
    public RayButton(String text, int width, int height)
    {
        super(text);
        this.setBackground(new Color(20, 20, 20));
        this.setForeground(Color.WHITE);
        this.setFont(new Font("Arial", Font.BOLD, 16));
        this.setFocusPainted(false);
        this.setPreferredSize(new Dimension(width, height));
    }

}
