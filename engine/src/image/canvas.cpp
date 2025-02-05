

#include "image/canvas.hpp" 


using image::Canvas;
/* The canvas class holds a matrix of colors with methods to write the colors to an image format output*/

Canvas::Canvas(int width, int height) : m_width(width), m_height(height) 
{
    color_matrix.resize(height * width, color::white());
}     

color::RGB& Canvas::pixel_at(int line, int color_idx) 
{ 
    return color_matrix.at(line * m_width + color_idx); 
}

void Canvas::insert_color(color::RGB color, int color_idx, int line) 
{ 
    color_matrix.at(line * m_width + color_idx) = color;  
}

void Canvas::write_to_ppm() 
{ 
    std::cout << "P3\n" << m_width << ' ' << m_height << "\n255\n"; 
    for (int line = 0; line < m_height; line++) 
    { 
        for (int pixel = 0; pixel < m_width; pixel++) 
        { 
            color::RGB color = pixel_at(line, pixel); 
            color.convert_to_256(); 
            std::cout << color.r << ' ' << color.g << ' ' << color.b << '\n';
        }
    }
}

std::vector<uint8_t> Canvas::write_to_frame_buffer() 
{ 
    /* Write to a frame buffer to be used for displaying the image on a SFML window */ 

    std::vector<uint8_t> frame_buffer; 
    frame_buffer.reserve(color_matrix.size() * 4);
    for (auto& color : color_matrix) 
    {
        color.convert_to_256(); 
        frame_buffer.push_back(color.r);   
        frame_buffer.push_back(color.g);  
        frame_buffer.push_back(color.b);   
        frame_buffer.push_back(255);    
    }
    return frame_buffer; 
}



