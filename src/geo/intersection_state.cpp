
#include "geo/intersection_state.hpp"
#include "geo/intersection.hpp"
#include "utils.hpp"

using geo::IntersectionState; 
using geo::Intersection; 

IntersectionState::IntersectionState(const Intersection& intersection, const Ray& ray) {
    t = intersection.t; 
    object = intersection.object; 
    point = ray.at(t);
    eye = -ray.direction; 
    normal = object->normal_at(point);
    reflect = geo::reflect(ray.direction, normal);

    //Compute if it is on the inside of an object by the dot product
    //If it is negative, the normal and eye are pointing in opposite directions => inside

    if (dot(normal, eye) < 0) { 
        inside = true; 
        normal = -normal; 
    } else { 
        inside = false;
    }

    over_point = point + normal * utils::EPSILON; 
}   

