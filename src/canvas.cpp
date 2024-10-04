

#include "canvas.hpp" 

/* The canvas class holds a matrix of colors with methods to write the colors to an image format output*/

Canvas::Canvas(int width, int height) : width(width), height(height) {
    for (int line = 0; line < height; line++) { 
        std::vector<Color> current_line(width, Color(1, 1, 1));  
        color_matrix.push_back(current_line); 
    }
}     

Color& Canvas::pixel_at(int line, int color_idx) { 
    return color_matrix.at(line).at(color_idx); 
}

void Canvas::insert_color(Color color, int line, int color_idx) { 
    color_matrix.at(line).at(color_idx) = color;  
}

void Canvas::write_to_ppm() { 
    std::cout << "P3\n" << width << ' ' << height << "\n255\n"; 
    for (int line = 0; line < height; line++) { 
	std::clog << "\rScanlines remaining: " << (height - line) << ' ' << std::flush; 
	
        for (int pixel = 0; pixel < width; pixel++) { 
            Color color = pixel_at(line, pixel); 
            color.convert_to_256(); 

            std::cout << color.r << ' ' << color.g << ' ' << color.b << '\n';
        }
    }
    std::clog << "\rDone                        " << std::endl; 
}


