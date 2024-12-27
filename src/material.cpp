
#include "material.hpp"

Material::Material() : color(Color(0, 0, 1)), ambient(0.3), diffuse(0.3), specular(0.3), shininess(1) {}

Material& Material::set_ambient(double amb) { 
    ambient = amb;
    return *this;
}

Material& Material::set_diffuse(double diff) { 
    diffuse = diff; 
    return *this;
}

Material& Material::set_shininess(double shine) { 
    shininess = shine; 
    return *this;
}

Material& Material::set_specular(double spec) { 
    specular = spec; 
    return *this; 
}

Material& Material::set_color(const Color& col) { 
    color = col;
    return *this;
}
