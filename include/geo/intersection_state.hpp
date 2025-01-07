
#ifndef INTERSECTION_STATE_HPP
#define INTERSECTION_STATE_HPP

#include "geo/tuples.hpp"
#include "geo/ray.hpp"
#include "scene/hittable.hpp"
#include <vector> 

namespace geo {
    class IntersectionState { 
    public: 
        double t; 
        const scene::Hittable* object; 
        Point point; 
        Point over_point; //the point slighty in the direction of the surface normal, to overcome the slight rounding errors 
        Point under_point; 
        Vec eye; 
        Vec normal; 
        bool inside; 
        Vec reflect; 
        double n1, n2;

        IntersectionState(size_t hit_index, const std::vector<Intersection>& intersections, const Ray&);

    };
}

#endif 
