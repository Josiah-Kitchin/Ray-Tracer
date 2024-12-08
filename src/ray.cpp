

#include "ray.hpp"


Ray::Ray(Point origin, Vec direction) : origin(origin), direction(direction) {}

Point Ray::at(double t) const { 
    return origin + direction * t;  
}

Ray transform_ray(const Ray& ray, const Matrix& transform) { 
    //instead of applying a transformation to an object, apply the transformation to a ray 
    return Ray(ray.origin * transform, ray.direction * transform); 
}
