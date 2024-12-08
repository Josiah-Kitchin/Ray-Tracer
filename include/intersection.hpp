#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <vector> 
#include "ray.hpp"
#include "tuples.hpp"

class Hittable; 

class Intersection { 
public: 
    double t; 
    const Hittable* object; 

    Intersection(double, const Hittable*);
};

bool operator==(const Intersection&, const Intersection&); 

Intersection hit(std::vector<Intersection>&); 

#endif

