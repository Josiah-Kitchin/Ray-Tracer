

#include "scene/camera.hpp"
#include <cmath> 
#include <algorithm>
#include <execution> 
#include <chrono> 

using scene::Camera; 

void Camera::init() { 
    //Initialzes half_width, half_height and pixel size after object initalization 
    //so that camera values can be set with the method chain pattern 

    double half_view = std::tan(m_field_of_view / 2);
    double aspect = double(m_horizontal_pixels) / double(m_vertical_pixels);

    if (aspect >= 1) { 
        m_half_width = half_view;  
        m_half_height = half_view / aspect; 
    } else { 
        m_half_width = half_view * aspect; 
        m_half_height = half_view; 
    }
    m_pixel_size = (m_half_width * 2) / m_horizontal_pixels;
}


geo::Ray Camera::ray_to_pixel(int pixel_x, int pixel_y) const { 
    //Offset from edge of the canvas to the pixels center
    double x_offset = (double(pixel_x) + 0.5) * m_pixel_size; 
    double y_offset = (double(pixel_y) + 0.5) * m_pixel_size; 

    double world_x = m_half_width - x_offset; 
    double world_y = m_half_height - y_offset; 

    geo::Point pixel =  xform::inverse(m_transformation) * geo::Point(world_x, world_y, -1);
    geo::Point origin = xform::inverse(m_transformation) * geo::Point(0, 0, 0);
    geo::Vec direction = unit_vector(pixel - origin);

    return geo::Ray(origin, direction);
}


/* ----------------- Interface Methods ---------------- */

image::Canvas Camera::render(scene::World& world) { 
    /* Called by the user to render a world of lights and objects 
       Iterators are used to create a multithreaded for loop */ 

    init(); //calculate some neccessary variables 

    //Initialize the iterator 
    m_vertical_pixel_iterator.resize(m_vertical_pixels);
    for (int i = 0; i < m_vertical_pixels; ++i)  
        m_vertical_pixel_iterator[i] = i; 

    image::Canvas image(m_horizontal_pixels, m_vertical_pixels);

    auto start = std::chrono::high_resolution_clock::now(); 

    std::clog << " Rendering...            \r";

    

    /* -------------- Render Loop -------------- */
    #ifdef DEBUG_BUILD //take away multithreading for easier debugging 
    std::for_each(m_vertical_pixel_iterator.begin(), m_vertical_pixel_iterator.end(), 
        [&](int y) {
            for (int x = 0; x < m_horizontal_pixels; ++x) {
                geo::Ray ray = ray_to_pixel(x, y);
                color::RGB pixel_color = world.color_at(ray);
                image.insert_color(pixel_color, x, y);
            }
        }
    );
    #else
    std::for_each(std::execution::par, m_vertical_pixel_iterator.begin(), m_vertical_pixel_iterator.end(), 
        [&](int y) {
            for (int x = 0; x < m_horizontal_pixels; ++x) {
                geo::Ray ray = ray_to_pixel(x, y);
                color::RGB pixel_color = world.color_at(ray);
                image.insert_color(pixel_color, x, y);
            }
        }
    );
    #endif
    /*-------------------------------------------*/

    auto end = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> duration = end - start; 
    std::clog << "\rImage Complete\nTime to render: " << duration.count() << '\n';  

    return image; 
}

Camera& Camera::set_horizontal_pixels(int pixels) { 
    m_horizontal_pixels = pixels; 
    return *this;
}
Camera& Camera::set_vertical_pixels(int pixels) { 
    m_vertical_pixels = pixels; 
    return *this;
}
Camera& Camera::set_field_of_view(double degrees) { 
    m_field_of_view = degrees; 
    return *this;
}

Camera& Camera::transform(const xform::Matrix<4>& new_transformation) { 
    m_transformation = m_transformation * new_transformation;
    return *this;
}

