#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector> 
#include "hittable.hpp"
#include "light.hpp"
#include "intersection.hpp"
#include "ray.hpp"

class World {

public: 
    std::vector<Hittable*> objects;
    std::vector<Light> lights; 

    World(); 
    
    std::vector<Intersection> intersects(const Ray&);

};




#endif