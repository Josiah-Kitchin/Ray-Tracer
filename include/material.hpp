#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "tuples.hpp"
#include "light.hpp"

class Material { 
public: 
    Color color; 
    double ambient, diffuse, specular, shininess; 

    Material(); 

};

Color lighting(const Material&, const Light&, const Point&, const Vec&, const Vec&);

#endif