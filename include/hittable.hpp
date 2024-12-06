#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <vector> 
#include "ray.hpp"
#include "intersection.hpp"
#include "material.hpp"



class Hittable { 
//abstract class for hittable objects 
public: 

    virtual std::vector<Intersection> intersect(const Ray&) const = 0; 
    // virtual void transform(const Matrix&) = 0;
    // virtual Vec normal_at(const Point&) const = 0; 

    virtual ~Hittable() = default; 

};

class Sphere : public Hittable { 
private: 
    double radius; 
    Point origin; 

public: 
    Material material; 
    Matrix transformation; 

    Sphere();
    std::vector<Intersection> intersect(const Ray&) const override; 
    void transform(const Matrix&);
    Vec normal_at(const Point&) const;

};

#endif