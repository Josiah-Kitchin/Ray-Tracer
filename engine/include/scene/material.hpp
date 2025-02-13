#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color/color.hpp"
#include "color/pattern.hpp"

namespace scene {
class Material {
    /* The material for a hittable object,
     * holds the color, pattern and material data */

  public:
    color::RGB color;
    const color::Pattern *m_pattern = nullptr;
    double ambient, diffuse, specular, shininess, reflective, refractive_index,
        transparency;

    Material();

    Material &set_ambient(double);
    Material &set_diffuse(double);
    Material &set_specular(double);
    Material &set_shininess(double);
    Material &set_reflective(double);
    Material &set_color(const color::RGB &);
    Material &set_pattern(const color::Pattern *);
    Material &set_refractive_index(double);
    Material &set_transparency(double);
};

Material glass();

} // namespace scene

#endif
