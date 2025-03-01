#ifndef WORLD_HPP
#define WORLD_HPP

#include "geo/intersection.hpp"
#include "geo/intersection_state.hpp"
#include "geo/ray.hpp"
#include "geo/tuples.hpp"
#include "scene/hittable.hpp"
#include "scene/light.hpp"
#include <vector>

namespace scene {

class World {
    /* The world holds all of the hittable objects and lights.
     * The world can be rendered by the camera */

  public:
    World();
    World &set_objects(const std::vector<scene::Hittable *> &);
    World &set_lights(const std::vector<scene::Light> &);
    World &add_object(scene::Hittable *);
    World &add_light(const scene::Light &);
    World &set_reflection_limit(int);

    friend class Camera;

  private:
    // Gets the color generated by a given ray, uses the below functions
    // for implementation
    color::RGB color_at(const geo::Ray &, int reflection_limit);

    // Returns all of the intersections from a given ray
    std::vector<geo::Intersection> intersects(const geo::Ray &);
    // Get the color of the reflection with a given reflection limit
    color::RGB reflect_color(const geo::IntersectionState &,
                             int reflection_limit);
    color::RGB refract_color(const geo::IntersectionState &,
                             int reflection_limit);
    bool is_shadowed(const geo::Point &);
    // Gets the color of an intersection with a given reflection limit
    color::RGB shade_hit(const geo::IntersectionState &, int reflection_limit);

    std::vector<scene::Hittable *> m_objects;
    std::vector<scene::Light> m_lights;

    // Levels of recursion aloud to calculate reflection
    int reflection_limit;
};

} // namespace scene

#endif
