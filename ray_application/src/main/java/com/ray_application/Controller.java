

package com.ray_application; 
import com.ray_application.sceneCreater.Engine; 
import com.ray_application.ui.components.ImagePanel; 
import java.awt.image.BufferedImage; 
import javax.swing.*; 


public class Controller
{
    
    private Engine m_engine; 

    public Controller(Engine engine)
    {
        m_engine = engine; 
    }

    private BufferedImage renderImage() throws Exception
    {
        try { 
            return m_engine.render();
        } catch (Exception e) {
            throw e; 
        }   
    }

    public void setButtonToRenderImage(JButton button, ImagePanel currentImage)
    // Set the button to render the image on click 
    {
        button.addActionListener(e -> {
            new SwingWorker<BufferedImage, Void>() {
                @Override
                protected BufferedImage doInBackground() throws Exception {
                    // This runs in a background thread
                    SwingUtilities.invokeLater(() -> button.setText("Rendering..."));
                    button.setEnabled(false);
                    return renderImage();
                }

                @Override
                protected void done() {
                    try {
                        BufferedImage newImage = get(); 
                        currentImage.setImage(newImage, 750); 
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    } finally { 
                        button.setText("Render");
                        button.setEnabled(true);
                    }
                }
            }.execute(); // Start the background task
        });
    }
}
