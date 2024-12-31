

#include "geo/ray.hpp"

using geo::Ray; 

Ray::Ray(Point origin, Vec direction) : origin(origin), direction(direction) {}

geo::Point Ray::at(double t) const { 
    return origin + direction * t;  
}

Ray transform_ray(const Ray& ray, const xform::Matrix<4>& transform) { 
    //instead of applying a transformation to an object, apply the transformation to a ray 
    return Ray(ray.origin * transform, ray.direction * transform); 
}
