#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "geo/tuples.hpp"
#include "color/color.hpp"
#include "color/pattern.hpp"


namespace scene {
    class Material { 
    public: 
        color::RGB color; 
        const color::Pattern* m_pattern = nullptr;
        double ambient, diffuse, specular, shininess, reflective; 

        Material(); 

        Material& set_ambient(double);
        Material& set_diffuse(double);
        Material& set_specular(double);
        Material& set_shininess(double);
        Material& set_reflective(double);
        Material& set_color(const color::RGB&);
        Material& set_pattern(const color::Pattern*);
    };
}


#endif