
package com.ray_application.sceneCreater; 

import java.awt.image.BufferedImage; 
import java.io.*; 
import java.util.Scanner; 

public class PPMReader
{
    public static BufferedImage loadPPM(String filename) throws IOException
    {
        File file = new File(filename);
        Scanner scanner = new Scanner(file);

        String magicNumber = scanner.next(); 
        if (!magicNumber.equals("P3"))
        {
            scanner.close(); 
            throw new IOException("Unsupported PPM format. Only P3 is supported");
        }

        int width = scanner.nextInt(); 
        int height = scanner.nextInt(); 
        int maxColor = scanner.nextInt(); 


        BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int r = scanner.nextInt(); 
                int g = scanner.nextInt(); 
                int b = scanner.nextInt(); 
                int rgb = (r << 16) | (g << 8) | b; 
                image.setRGB(x, y, rgb);
            }
        }

        scanner.close(); 
        return image; 
    }
}



