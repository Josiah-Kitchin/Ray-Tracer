

#include "canvas.hpp" 

/* The canvas class holds a matrix of colors with methods to write the colors to an image format output*/

Canvas::Canvas(int width, int height) : m_width(width), m_height(height) {
    color_matrix.reserve(height);
    for (int line = 0; line < height; line++) { 
        color_matrix.emplace_back(width, Color(1, 1, 1)); 
    }
}     

Color& Canvas::pixel_at(int line, int color_idx) { 
    return color_matrix.at(line).at(color_idx); 
}

void Canvas::insert_color(Color color, int color_idx, int line) { 
    color_matrix.at(line).at(color_idx) = color;  
}

void Canvas::write_to_ppm() { 
    std::cout << "P3\n" << m_width << ' ' << m_height << "\n255\n"; 
    for (int line = 0; line < m_height; line++) { 
	
        for (int pixel = 0; pixel < m_width; pixel++) { 
            Color color = pixel_at(line, pixel); 
            color.convert_to_256(); 

            std::cout << color.r << ' ' << color.g << ' ' << color.b << '\n';
        }
    }
}



