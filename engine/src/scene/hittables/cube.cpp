
#include "scene/hittable.hpp"
#include "scene/material.hpp"

using scene::Cube;
using std::vector; 


vector<geo::Intersection> Cube::intersect(const geo::Ray& ray) const 
{ 
    geo::Ray transformed_ray = transform_ray(ray, inverse(m_transformation));

}

geo::Vec Cube::normal_at(const geo::Point& world_point) const 
{ 

}

