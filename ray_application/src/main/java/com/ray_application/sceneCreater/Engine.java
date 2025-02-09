
package com.ray_application.sceneCreater; 

import java.awt.image.BufferedImage; 
import java.io.IOException;

public class Engine
{
    String engineExecutablePath; 
    public Engine(String engineExecutablePath)
    {
        this.engineExecutablePath = engineExecutablePath;
    }

    public BufferedImage render() throws IOException, InterruptedException
    {
        try { 
            String renderCommand = this.engineExecutablePath + "./ray " +
                                   this.engineExecutablePath + "scene.json";

            ProcessBuilder processBuilder = new ProcessBuilder(renderCommand.split(" "));

            System.out.println("Rendering image");
            Process process = processBuilder.start(); 
            int exitCode = process.waitFor(); 
            System.out.println("Image complete");

            return PPMReader.loadPPM("image.ppm");

        } catch (IOException | InterruptedException e) {
            e.printStackTrace(); 
            throw e; 
        }
    }
}
