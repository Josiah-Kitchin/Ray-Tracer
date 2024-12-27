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
    World(); 
    World& set_objects(const std::vector<Hittable*>&);
    World& set_lights(const std::vector<Light>&);
    World& add_object(Hittable*);
    World& add_light(const Light&);

    friend class Camera; 

private:
    std::vector<Intersection> intersects(const Ray&);
    Color shade_hit(const IntersectionState&); 
    Color color_at(const Ray&);
    std::vector<Hittable*> m_objects;
    std::vector<Light> m_lights; 
};





#endif