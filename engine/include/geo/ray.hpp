

#ifndef RAY_HPP
#define RAY_HPP

#include "geo/tuples.hpp"
#include "xform/matrices.hpp"

namespace geo {

class Ray {
  public:
    Point origin; // Point of where the ray was shot from
    Vec direction;

    Ray(Point, Vec);

    Point at(double) const; // Point along the ray at a given t
};
} // namespace geo

// Transform a ray by multiplying a matrix with the ray
geo::Ray transform_ray(const geo::Ray &, const xform::Matrix<4> &);

#endif
