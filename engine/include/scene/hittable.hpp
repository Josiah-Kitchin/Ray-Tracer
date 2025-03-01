#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "color/color.hpp"
#include "geo/intersection.hpp"
#include "geo/ray.hpp"
#include "scene/material.hpp"
#include <vector>

namespace scene {
class Hittable {
    /* The hittable abstract class is for objects that can be insersected by
     * rays. */

  public:
    // Give a vector of the intersections occured from a given ray
    virtual std::vector<geo::Intersection>
    intersect(const geo::Ray &) const = 0;
    // Get the surface normal at a given point
    virtual geo::Vec normal_at(const geo::Point &) const = 0;

    Hittable() : material(), m_transformation(xform::identity()) {}
    virtual ~Hittable() = default;

    Hittable &set_color(const color::RGB &);
    Hittable &set_ambient(double);
    Hittable &set_diffuse(double);
    Hittable &set_specular(double);
    // Transform the object with a given transformation matrix
    Hittable &transform(const xform::Matrix<4> &);
    Hittable &set_material(const Material &);
    Hittable &set_pattern(const color::Pattern *);
    Hittable &set_reflective(double);
    Hittable &set_refractive_index(double);
    Hittable &set_transparency(double);

    Material material;

    xform::Matrix<4> get_transformation() const;
    xform::Matrix<4> get_inverse_transformation() const;

  protected:
    xform::Matrix<4> m_transformation = xform::identity();
    // Store the inverse transformation so it only needs to be calculated once
    xform::Matrix<4> m_inverse_transformation =
        xform::inverse(xform::identity());
};

class Sphere : public Hittable {
  public:
    Sphere();
    std::vector<geo::Intersection> intersect(const geo::Ray &) const override;
    geo::Vec normal_at(const geo::Point &) const override;

  private:
    geo::Point m_origin;
};

class Plane : public Hittable {
  public:
    std::vector<geo::Intersection> intersect(const geo::Ray &) const override;
    geo::Vec normal_at(const geo::Point &) const override;
};

class Cube : public Hittable {
  public:
    Cube();
    std::vector<geo::Intersection> intersect(const geo::Ray &) const override;
    geo::Vec normal_at(const geo::Point &) const override;

  private:
    geo::Point m_origin;
    double m_side_length;
};
} // namespace scene

#endif
