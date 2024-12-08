
#ifndef INTERSECTION_STATE_HPP
#define INTERSECTION_STATE_HPP

#include "tuples.hpp"
#include "hittable.hpp"
#include "ray.hpp"

class IntersectionState { 
public: 
    double t; 
    const Hittable* object; 
    Point point; 
    Vec eye; 
    Vec normal; 
    bool inside; 

    IntersectionState(const Intersection&, const Ray&);

};

#endif