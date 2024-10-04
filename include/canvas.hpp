
#ifndef CANVAS_HPP
#define CANVAS_HPP


#include <vector>
#include "tuples.hpp" 
#include <iostream> 

class Canvas { 
public: 
    int width; 
    int height; 

    Canvas(int, int); 

    Color& pixel_at(int, int); 
    void insert_color(Color, int, int); 
    void write_to_ppm(); 
private:
    std::vector<std::vector<Color>> color_matrix; 
    
};



#endif
