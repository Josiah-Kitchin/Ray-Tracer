
#include "geo/intersection_state.hpp"
#include "geo/intersection.hpp"
#include "scene/hittable.hpp"
#include "utils.hpp"

using geo::Intersection;
using geo::IntersectionState;

IntersectionState::IntersectionState(size_t hit_index,
                                     const std::vector<Intersection> &intersections,
                                     const Ray &ray) {

    /* -------- Calculate the refraction -------- */

    std::vector<const scene::Hittable *> objects_not_exited;
    objects_not_exited.reserve(intersections.size());

    for (size_t i = 0; i < intersections.size(); ++i) {
        bool is_hit_object = (hit_index == i);
        const auto &intersection = intersections.at(i);
        if (is_hit_object)
            n1 = !objects_not_exited.empty() ? objects_not_exited.back()->material.refractive_index
                                             : 1.0;

        if (!objects_not_exited.empty() && objects_not_exited.back() == intersection.object) {   
            objects_not_exited.pop_back();
        } else { 
            objects_not_exited.push_back(intersection.object);
        }

        if (is_hit_object) 
            n2 = !objects_not_exited.empty() ? objects_not_exited.back()->material.refractive_index
                                             : 1.0;
    }

    /* -------- Object specific intersection data ------- */

    t = intersections.at(hit_index).t;
    object = intersections.at(hit_index).object;

    point = ray.at(t);
    eye = -ray.direction;
    normal = object->normal_at(point);
    reflect = geo::reflect(ray.direction, normal);

    // Compute if it is on the inside of an object by the dot product
    // If it is negative, the normal and eye are pointing in opposite directions
    // => inside

    if (dot(normal, eye) < 0) {
        inside = true;
        normal = -normal;
    } else {
        inside = false;
    }

    over_point = point + normal * utils::EPSILON;
    under_point = -(normal * utils::EPSILON) + point;
}
