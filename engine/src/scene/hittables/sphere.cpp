

#include "scene/hittable.hpp"
#include "utils.hpp"
#include <cmath>

using scene::Sphere;
using std::vector;

Sphere::Sphere() : m_origin(geo::Point(0, 0, 0)) {}

vector<geo::Intersection> Sphere::intersect(const geo::Ray &ray) const {

    // transform the ray instead of the sphere, with the type of transformation
    // matrix being held in the hittable object. This means we have to take the
    // inverse to give the correct transformation to the ray
    geo::Ray transformed_ray = transform_ray(ray, m_inverse_transformation);
    // calculates whether a ray hits a sphere by calculating the discriminant
    geo::Vec sphere_to_ray = transformed_ray.origin - m_origin;

    double a = geo::dot(transformed_ray.direction, transformed_ray.direction);
    double b = 2 * geo::dot(transformed_ray.direction, sphere_to_ray);
    double c = geo::dot(sphere_to_ray, sphere_to_ray) - 1;

    double discriminant = b * b - 4 * a * c;

    // If the discriminant is negative, the ray has missed
    if (discriminant < 0)
        return vector<geo::Intersection>();

    double intersect_1 = (-b - sqrt(discriminant)) / (2 * a);
    double intersect_2 = (-b + sqrt(discriminant)) / (2 * a);

    geo::Intersection intersection_1(intersect_1, this);
    geo::Intersection intersection_2(intersect_2, this);

    if (utils::compare_doubles(intersect_1, intersect_2))
        return vector<geo::Intersection>{intersection_1};

    return vector<geo::Intersection>{intersection_1, intersection_2};
}

geo::Vec Sphere::normal_at(const geo::Point &world_point) const {
    // Returns the normal vector at a point.
    // Because the sphere is transformed, we must make calculations to compute
    // the normal at the transformed state.
    geo::Point object_point = m_inverse_transformation * world_point;
    geo::Vec object_normal = object_point - geo::Point(0, 0, 0);
    geo::Vec world_normal = xform::transpose(m_inverse_transformation) * object_normal;
    return unit_vector(world_normal);
}
