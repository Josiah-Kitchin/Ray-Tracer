

#ifndef RAY_HPP
#define RAY_HPP

#include "geo/tuples.hpp"
#include "xform/matrices.hpp" 

namespace geo {

    class Ray { 
    public: 
        Point origin; 
        Vec direction; 

        Ray(Point, Vec);

        Point at(double) const;
    };
}

geo::Ray transform_ray(const geo::Ray&, const xform::Matrix<4>&);


#endif 