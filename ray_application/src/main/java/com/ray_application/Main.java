
package com.ray_application; 
import com.ray_application.ui.MainUI; 
import com.ray_application.sceneCreater.Engine; 

import java.awt.image.BufferedImage; 

public class Main
{
    public static void main(String[] args)
    {
        Engine engine = new Engine("resources/");
        try { 
            BufferedImage image = engine.render(); 
            MainUI.main(image);
        } catch (Exception e) { 
            e.printStackTrace(); 
        } 
    }
}
