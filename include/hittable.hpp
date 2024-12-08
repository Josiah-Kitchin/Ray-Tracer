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
    virtual void transform(const Matrix&) = 0;
    virtual Vec normal_at(const Point&) const = 0; 

    Hittable() : material(), transformation(identity()) {}
    virtual ~Hittable() = default; 

    Material material; 
    Matrix transformation; 
};

class Sphere : public Hittable { 
private: 
    double radius; 
    Point origin; 

public: 

    Sphere();
    std::vector<Intersection> intersect(const Ray&) const override; 
    void transform(const Matrix&);
    Vec normal_at(const Point&) const;

};

#endif