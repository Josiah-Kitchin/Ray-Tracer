#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <vector> 
#include "ray.hpp"
#include "material.hpp"
#include "intersection.hpp"

class Hittable { 
    /* 
        The hittable abstract class is for objects that can be insersected by rays. They hold materials 
        and can be transformed 
    */
public: 

    virtual std::vector<Intersection> intersect(const Ray&) const = 0; 
    virtual Vec normal_at(const Point&) const = 0; 

    Hittable() : material(), m_transformation(identity()) {}
    virtual ~Hittable() = default; 

    Hittable& set_color(const Color&); 
    Hittable& set_ambient(double);
    Hittable& set_diffuse(double);
    Hittable& set_specular(double);
    Hittable& transform(const Matrix&);
    Hittable& set_material(const Material&);

    Material material; 

protected: 
    Matrix m_transformation; 
    
};

class Sphere : public Hittable { 

public: 

    Sphere();
    std::vector<Intersection> intersect(const Ray&) const override; 
    Vec normal_at(const Point&) const;

private: 
    Point m_origin;

};

#endif