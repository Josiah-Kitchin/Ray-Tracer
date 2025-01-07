
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "xform/matrices.hpp"
#include "geo/ray.hpp"
#include "scene/world.hpp"
#include "image/canvas.hpp"
#include <vector> 

namespace scene { 

    class Camera { 
    public: 
        Camera& set_horizontal_pixels(int);
        Camera& set_vertical_pixels(int);
        Camera& set_field_of_view(double);
        Camera& transform(const xform::Matrix<4>&);

        image::Canvas render(scene::World&);
        

    private: 
        int m_horizontal_pixels; 
        int m_vertical_pixels;
        double m_field_of_view; 

        double m_pixel_size;
        double m_half_width; 
        double m_half_height; 
        xform::Matrix<4> m_transformation = xform::identity(); 

        geo::Ray ray_to_pixel(int, int) const;
        void init(); //calculates pixel size, half_width, half_height

        std::vector<int> m_vertical_pixel_iterator;  //need iters to use for each parrallelisim 

    };

}

#endif
