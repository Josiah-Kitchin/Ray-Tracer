#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "geo/tuples.hpp"
#include "color/color.hpp"

namespace scene {
    class Material { 
    public: 
        color::RGB color; 
        double ambient, diffuse, specular, shininess; 

        Material(); 

        Material& set_ambient(double);
        Material& set_diffuse(double);
        Material& set_specular(double);
        Material& set_shininess(double);
        Material& set_color(const color::RGB&);

    };
}


#endif