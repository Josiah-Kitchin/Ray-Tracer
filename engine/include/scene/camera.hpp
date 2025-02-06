
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "xform/matrices.hpp"
#include "geo/ray.hpp"
#include "scene/world.hpp"
#include "image/canvas.hpp"
#include <vector> 

namespace scene 
{ 

    class Camera 
    { 
    /* The eye of the scene, where the first rays originate from.  
     * Holds data for the size of the image and field of view. 
     * The camera can be moved around by transforming with the view_transform matrix */ 

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
        xform::Matrix<4> m_inverse_transformation = xform::inverse(xform::identity());

        geo::Ray ray_to_pixel(double, double) const;
        color::RGB anti_alias(double, double, scene::World&) const; 
        void init(); //calculates pixel size, half_width, half_height

        std::vector<int> m_vertical_pixel_iterator;  //need iters to use for each parrallelisim 

    };

}

#endif
