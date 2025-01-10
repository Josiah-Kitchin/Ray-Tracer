

#include "image/canvas.hpp" 


using image::Canvas;
/* The canvas class holds a matrix of colors with methods to write the colors to an image format output*/

Canvas::Canvas(int width, int height) : m_width(width), m_height(height) {
    color_matrix.resize(height * width, color::RGB(1, 1, 1));
}     

color::RGB& Canvas::pixel_at(int line, int color_idx) { 
    return color_matrix.at(line * m_width + color_idx); 
}

void Canvas::insert_color(color::RGB color, int color_idx, int line) { 
    color_matrix.at(line * m_width + color_idx) = color;  
}

void Canvas::write_to_ppm() { 
    std::cout << "P3\n" << m_width << ' ' << m_height << "\n255\n"; 
    for (int line = 0; line < m_height; line++) { 
	
        for (int pixel = 0; pixel < m_width; pixel++) { 
            color::RGB color = pixel_at(line, pixel); 
            color.convert_to_256(); 

            std::cout << color.r << ' ' << color.g << ' ' << color.b << '\n';
        }
    }
}

std::vector<uint8_t> Canvas::write_to_frame_buffer() { 
    std::vector<uint8_t> frame_buffer(m_width * m_height * 4, 0); 
    for (int line = 0; line < m_height; line++) { 
        for (int pixel = 0; pixel < m_width; pixel++) { 
            color::RGB color = pixel_at(line, pixel); 
            color.convert_to_256(); 

            int index = (line * m_width + pixel) * 4;
            frame_buffer[index + 0] = color.r; 
            frame_buffer[index + 1] = color.g;
            frame_buffer[index + 2] = color.b;
            frame_buffer[index + 3] = 255;
        }
    }
    return frame_buffer; 
}



