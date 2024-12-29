
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "matrices.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "canvas.hpp"
#include <vector> 

class Camera { 
public: 
    Camera& set_horizontal_pixels(int);
    Camera& set_vertical_pixels(int);
    Camera& set_field_of_view(double);
    Camera& transform(const xform::Matrix&);

    Canvas render(World&);
    

private: 
    int m_horizontal_pixels; 
    int m_vertical_pixels;
    double m_field_of_view; 

    double m_pixel_size;
    double m_half_width; 
    double m_half_height; 
    xform::Matrix m_transformation = xform::identity(); 

    Ray ray_to_pixel(int, int) const;
    void init(); //calculates pixel size, half_width, half_height

    std::vector<int> m_vertical_pixel_iterator;  //need iters to use for each parrallelisim 

};



#endif