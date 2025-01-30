
#ifndef INTERSECTION_STATE_HPP
#define INTERSECTION_STATE_HPP

#include "geo/tuples.hpp"
#include "geo/ray.hpp"
#include "scene/hittable.hpp"
#include <vector> 

namespace geo {
    class IntersectionState { 
    // Meta data of an intersection and a ray 
    public: 
        double t; // t of the ray 
        const scene::Hittable* object; // Object that the ray intersected with 
        Point point; // Point of intersection 
        Point over_point; // The point slighty moved in the direction of the surface normal, to overcome the slight rounding errors 
        Point under_point; // The piont slightly moved in the opposite direction of the surface normal 
        Vec eye; // Where the ray came from 
        Vec normal; // The normal of the ray 
        bool inside; // If the intersection occured inside a hittable object 
        Vec reflect; // The reflection of the ray 
        double n1, n2;

        IntersectionState(size_t hit_index, const std::vector<Intersection>& intersections, const Ray&);

    };
}

#endif 
