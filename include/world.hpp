#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector> 
#include "hittable.hpp"
#include "light.hpp"
#include "intersection.hpp"
#include "intersection_state.hpp"
#include "ray.hpp"
#include "tuples.hpp"

class World {

public: 
    std::vector<Hittable*> objects;
    std::vector<Light> lights; 

    World(); 
    
    std::vector<Intersection> intersects(const Ray&);
    Color shade_hit(const IntersectionState&); 
    Color color_at(const Ray&);

};





#endif