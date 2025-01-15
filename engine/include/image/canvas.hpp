
#ifndef CANVAS_HPP
#define CANVAS_HPP


#include <vector>
#include "color/color.hpp"
#include <cstdint> 

namespace image {

    class Canvas { 
    public: 

        Canvas(int, int); 

        color::RGB& pixel_at(int, int); 
        void insert_color(color::RGB, int, int); 
        void write_to_ppm(); 
        std::vector<uint8_t>write_to_frame_buffer(); 
    private:
        std::vector<color::RGB> color_matrix; 
        int m_width; 
        int m_height; 
        
    };

}


#endif
