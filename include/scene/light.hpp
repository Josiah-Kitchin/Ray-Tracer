#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "geo/tuples.hpp"
#include "scene/material.hpp"

namespace scene {

    struct Light { 
    public: 
        Light(const color::RGB&, const geo::Point&);
        Light();
        Light& set_intensity(const color::RGB&); 
        Light& set_position(const geo::Point&);

        color::RGB m_intensity; 
        geo::Point m_position; 
    };
}

color::RGB calculate_lighting(const scene::Material&, const scene::Light&, const geo::Point&, const geo::Vec&, const geo::Vec&);

#endif