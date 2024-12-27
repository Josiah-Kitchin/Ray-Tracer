#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "tuples.hpp"

class Material { 
public: 
    Color color; 
    double ambient, diffuse, specular, shininess; 

    Material(); 

    Material& set_ambient(double);
    Material& set_diffuse(double);
    Material& set_specular(double);
    Material& set_shininess(double);
    Material& set_color(const Color&);

};


#endif