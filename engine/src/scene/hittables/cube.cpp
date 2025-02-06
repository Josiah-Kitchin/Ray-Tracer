
#include "scene/hittable.hpp"
#include <algorithm> 

using scene::Cube;
using std::vector; 
#include <cmath> 


Cube::Cube() : m_origin(geo::Point(0, 0, 0)), m_side_length(2.0) {}

vector<geo::Intersection> Cube::intersect(const geo::Ray& ray) const 
{ 
    geo::Ray transformed_ray = transform_ray(ray, inverse(m_transformation)); 

    // Initialize t_min and t_max for intersection points
    double t_min = -std::numeric_limits<double>::infinity();
    double t_max = std::numeric_limits<double>::infinity();

    // Define half the side length of the cube
    double half_side = m_side_length / 2.0;

    // Ray components: x, y, and z of the ray
    double ray_origin_x = transformed_ray.origin.x;
    double ray_origin_y = transformed_ray.origin.y;
    double ray_origin_z = transformed_ray.origin.z;

    double ray_dir_x = transformed_ray.direction.x;
    double ray_dir_y = transformed_ray.direction.y;
    double ray_dir_z = transformed_ray.direction.z;

    // Cube bounds: min and max for each axis (x, y, z)
    double min_x = m_origin.x - half_side;
    double max_x = m_origin.x + half_side;

    double min_y = m_origin.y - half_side;
    double max_y = m_origin.y + half_side;

    double min_z = m_origin.z - half_side;
    double max_z = m_origin.z + half_side;

    // Check each axis (x, y, z) for intersections
    for (int i = 0; i < 3; ++i) {
        double origin, direction, min_bound, max_bound;

        if (i == 0) 
        {
            origin = ray_origin_x;
            direction = ray_dir_x;
            min_bound = min_x;
            max_bound = max_x;
        } 
        else if (i == 1) 
        {
            origin = ray_origin_y;
            direction = ray_dir_y;
            min_bound = min_y;
            max_bound = max_y;
        } 
        else {
            origin = ray_origin_z;
            direction = ray_dir_z;
            min_bound = min_z;
            max_bound = max_z;
        }

        // Ray direction is not zero, calculate the intersection with planes
        if (direction != 0) {
            double t1 = (min_bound - origin) / direction;
            double t2 = (max_bound - origin) / direction;

            // Ensure t1 is the smaller value
            if (t1 > t2) {
                std::swap(t1, t2);
            }

            // Update the global t_min and t_max
            t_min = std::max(t_min, t1);
            t_max = std::min(t_max, t2);

            // If t_min is greater than t_max, there's no intersection
            if (t_min > t_max) {
                return {}; 
            }
        } else {
            // If ray is parallel to the plane and doesn't intersect along this axis
            if (origin < min_bound || origin > max_bound) {
                return {}; 
            }
        }
    }

    // If we get here, the ray intersects the cube
    return { geo::Intersection(t_min, this), geo::Intersection(t_max, this) };
}

geo::Vec Cube::normal_at(const geo::Point& world_point) const 
{
    geo::Point object_point = xform::inverse(m_transformation) * world_point;
    geo::Vec object_normal;

    // Determine which face of the cube was hit and set the normal
    if (std::abs(object_point.x - m_origin.x - m_side_length / 2.0) < 1e-6) 
    {
        object_normal = geo::Vec(1, 0, 0); // Normal along positive x-axis
    } 
    else if (std::abs(object_point.x - m_origin.x + m_side_length / 2.0) < 1e-6) 
    {
        object_normal = geo::Vec(-1, 0, 0); // Normal along negative x-axis
    } 
    else if (std::abs(object_point.y - m_origin.y - m_side_length / 2.0) < 1e-6) 
    {
        object_normal = geo::Vec(0, 1, 0); // Normal along positive y-axis
    } 
    else if (std::abs(object_point.y - m_origin.y + m_side_length / 2.0) < 1e-6) 
    {
        object_normal = geo::Vec(0, -1, 0); // Normal along negative y-axis
    } 
    else if (std::abs(object_point.z - m_origin.z - m_side_length / 2.0) < 1e-6) 
    {
        object_normal = geo::Vec(0, 0, 1); // Normal along positive z-axis
    } 
    else if (std::abs(object_point.z - m_origin.z + m_side_length / 2.0) < 1e-6) 
    {
        object_normal = geo::Vec(0, 0, -1); // Normal along negative z-axis
    }

    // Transform the normal back to world coordinates
    geo::Vec world_normal = xform::transpose(xform::inverse(m_transformation)) * object_normal;
    return unit_vector(world_normal);  // Normalize the result
}


