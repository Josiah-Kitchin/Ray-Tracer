
#ifndef INTERSECTION_STATE_HPP
#define INTERSECTION_STATE_HPP

#include "geo/tuples.hpp"
#include "geo/ray.hpp"
#include "scene/hittable.hpp"

namespace geo {
    class IntersectionState { 
    public: 
        double t; 
        const scene::Hittable* object; 
        Point point; 
        Point over_point; //the point slighty in the direction of the surface normal, to overcome the slight rounding errors 
        Vec eye; 
        Vec normal; 
        bool inside; 
        Vec reflect; 

        IntersectionState(const Intersection&, const Ray&);

    };
}

#endif 
