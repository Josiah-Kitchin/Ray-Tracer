
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
        Vec eye; 
        Vec normal; 
        bool inside; 

        IntersectionState(const Intersection&, const Ray&);

    };
}

#endif 