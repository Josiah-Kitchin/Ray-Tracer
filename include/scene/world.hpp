#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector> 
#include "scene/hittable.hpp"
#include "scene/light.hpp"
#include "geo/intersection.hpp"
#include "geo/intersection_state.hpp"
#include "geo/ray.hpp"
#include "geo/tuples.hpp"


namespace scene {

class World {

    public: 
        World(); 
        World& set_objects(const std::vector<scene::Hittable*>&);
        World& set_lights(const std::vector<scene::Light>&);
        World& add_object(scene::Hittable*);
        World& add_light(const scene::Light&);
        World& set_reflection_limit(int);

        friend class Camera; 

    private:
        std::vector<geo::Intersection> intersects(const geo::Ray&);
        color::RGB reflect_color(const geo::IntersectionState&, int);
        bool is_shadowed(const geo::Point&);
        color::RGB shade_hit(const geo::IntersectionState&, int); 
        color::RGB color_at(const geo::Ray&, int);
        std::vector<scene::Hittable*> m_objects;
        std::vector<scene::Light> m_lights; 

        int reflection_limit; 
    };

}




#endif
