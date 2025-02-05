
#include "scene/material.hpp"

using scene::Material; 

Material::Material() : color(color::RGB(0, 0, 0)), ambient(0), diffuse(0), specular(0), shininess(1),
                       reflective(0), refractive_index(0), transparency(0) {}

Material& Material::set_ambient(double amb) 
{ 
    ambient = amb;
    return *this;
}

Material& Material::set_diffuse(double diff) 
{ 
    diffuse = diff; 
    return *this;
}

Material& Material::set_shininess(double shine) 
{ 
    shininess = shine; 
    return *this;
}

Material& Material::set_specular(double spec) 
{ 
    specular = spec; 
    return *this; 
}

Material& Material::set_color(const color::RGB& col) 
{ 
    color = col;
    return *this;
}

Material& Material::set_pattern(const color::Pattern* pattern) 
{ 
    m_pattern = pattern; 
    return *this;
}

Material& Material::set_reflective(double ref) 
{ 
    reflective = ref; 
    return *this; 
}

Material& Material::set_refractive_index(double index) 
{ 
    refractive_index = index; 
    return *this;
}

Material& Material::set_transparency(double trans) 
{ 
    transparency = trans; 
    return *this;
}

Material scene::glass() 
{ 
    Material glass; 
    glass
        .set_refractive_index(1.52)
        .set_transparency(1);
    return glass; 
}





