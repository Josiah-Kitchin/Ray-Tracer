
#ifndef CANVAS_HPP
#define CANVAS_HPP


#include <vector>
#include "color/color.hpp"

namespace image {

    class Canvas { 
    public: 

        Canvas(int, int); 

        color::RGB& pixel_at(int, int); 
        void insert_color(color::RGB, int, int); 
        void write_to_ppm(); 
    private:
        std::vector<std::vector<color::RGB>> color_matrix; 
        int m_width; 
        int m_height; 
        
    };

}


#endif
