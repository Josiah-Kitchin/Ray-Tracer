

#include "scene/hittable.hpp"
#include "utils.hpp"
#include <cmath>

using scene::Plane;
using std::vector;

vector<geo::Intersection> Plane::intersect(const geo::Ray &ray) const {
    geo::Ray transformed_ray = transform_ray(ray, m_inverse_transformation);
    if (std::abs(transformed_ray.direction.y) <
        utils::EPSILON) // ray parellel with the plane
        return {};

    double t = -transformed_ray.origin.y / transformed_ray.direction.y;
    return {geo::Intersection(t, this)};
}

geo::Vec Plane::normal_at(const geo::Point &world_point) const {
    // Planes have the same normal at any point
    return geo::Vec(0, 1, 0);
}
