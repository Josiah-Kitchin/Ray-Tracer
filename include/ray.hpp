

#ifndef RAY_HPP
#define RAY_HPP

#include "tuples.hpp"
#include "matrices.hpp" 

class Ray { 
public: 
    Point origin; 
    Vec direction; 

    Ray(Point, Vec);

    Point at(double);

};

Ray transform_ray(const Ray&, const Matrix&);


#endif 