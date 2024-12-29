#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <vector> 
#include "geo/ray.hpp"
#include "geo/tuples.hpp"

namespace scene {
    class Hittable; 
}

namespace geo { 
    class Intersection { 
    public: 
        double t; 
        const scene::Hittable* object; 

        Intersection(double, const scene::Hittable*);
    };

    Intersection hit(std::vector<Intersection>&); 
}

bool operator==(const geo::Intersection&, const geo::Intersection&); 

#endif

