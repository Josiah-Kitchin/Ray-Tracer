#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "geo/tuples.hpp"
#include "scene/material.hpp"

namespace scene {

    struct Light { 
    /* A point that generates light for the scene */ 

    public: 
        Light(const color::RGB&, const geo::Point&);
        Light();
        Light& set_intensity(const color::RGB&); 
        Light& set_position(const geo::Point&);

        color::RGB m_intensity; 
        geo::Point m_position; 
    };
}

// Calculate the color given the object, light, position of the hit, the eye, the normal of the vec, and whether
// it is a shadowed point or not 
color::RGB calculate_lighting(const scene::Hittable* object, const scene::Light& light, const geo::Point& position, 
                              const geo::Vec& eye, const geo::Vec& normal, bool in_shadow);  
#endif
