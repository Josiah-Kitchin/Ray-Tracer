
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
    int m_horizontal_pixels; 
    int m_vertical_pixels;
    double m_field_of_view; 

    double m_pixel_size;
    double m_half_width; 
    double m_half_height; 
    Matrix m_transformation = identity(); 

    Ray ray_to_pixel(int, int) const;
    void init(); //calculates pixel size, half_width, half_height
};



#endif