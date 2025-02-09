
package com.ray_application.sceneCreater; 

import java.awt.image.BufferedImage; 
import java.io.IOException;

public class Engine
/* Manages the engine executable */ 
{
    String engineExecutablePath; 
    public Engine(String engineExecutablePath)
    {
        this.engineExecutablePath = engineExecutablePath;
    }

    public BufferedImage render() throws IOException, InterruptedException
    /* Spawns a process for the engine executable and waits for its completion.
     * On completion, returns the rendered image in a BufferedImage.
     * Throws an interrupt exception if the rendering is interruped  
     * Throws an IO exception if it can not find the executable or json 
     */
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
