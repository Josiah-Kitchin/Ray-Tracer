#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <vector> 

class Hittable; //prevents circular includes 

class Intersection { 
public: 
    double t; 
    const Hittable* object; 

    Intersection(double, const Hittable*);
};

bool operator==(const Intersection&, const Intersection&); 

Intersection hit(std::vector<Intersection>&); 






#endif