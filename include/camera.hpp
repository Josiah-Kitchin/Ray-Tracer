
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "matrices.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "canvas.hpp"

class Camera { 
public: 
    Camera& set_horizontal_pixels(int);
    Camera& set_vertical_pixels(int);
    Camera& set_field_of_view(double);
    Camera& transform(const Matrix&);

    Canvas render(World&);
    

private: 
    int horizontal_pixels; 
    int vertical_pixels;
    double field_of_view; 

    double pixel_size;
    double half_width; 
    double half_height; 

    Ray ray_to_pixel(int, int) const;
    Matrix transformation = identity(); 
    void init(); //calculates pixel size, half_width, half_height
};



#endif