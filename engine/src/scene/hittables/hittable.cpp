

#include "scene/hittable.hpp"
#include "scene/material.hpp"

using scene::Hittable;

/* ----------- Hittable Creation Methods ---------- */
Hittable &Hittable::set_color(const color::RGB &color) {
    material.color = color;
    return *this;
}

Hittable &Hittable::set_ambient(double ambient) {
    material.ambient = ambient;
    return *this;
}

Hittable &Hittable::set_diffuse(double diffuse) {
    material.diffuse = diffuse;
    return *this;
}

Hittable &Hittable::set_specular(double specular) {
    material.specular = specular;
    return *this;
}

Hittable &Hittable::set_material(const scene::Material &mat) {
    material = mat;
    return *this;
}

Hittable &Hittable::transform(const xform::Matrix<4> &new_transformation) {
    m_transformation = m_transformation * new_transformation;
    m_inverse_transformation = xform::inverse(m_transformation);
    return *this;
}

Hittable &Hittable::set_pattern(const color::Pattern *pattern) {
    material.m_pattern = pattern;
    return *this;
}

Hittable &Hittable::set_reflective(double ref) {
    material.reflective = ref;
    return *this;
}

Hittable &Hittable::set_refractive_index(double ret) {
    material.refractive_index = ret;
    return *this;
}

Hittable &Hittable::set_transparency(double trans) {
    material.transparency = trans;
    return *this;
}

xform::Matrix<4> Hittable::get_transformation() const { return m_transformation; }
xform::Matrix<4> Hittable::get_inverse_transformation() const { return m_inverse_transformation; }
