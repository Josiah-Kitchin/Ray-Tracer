#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <vector> 
#include "geo/ray.hpp"
#include "scene/material.hpp"
#include "geo/intersection.hpp"
#include "color/color.hpp"

namespace scene {
    class Hittable { 
        /* 
            The hittable abstract class is for objects that can be insersected by rays. They hold materials 
            and can be transformed 
        */
    public: 

        virtual std::vector<geo::Intersection> intersect(const geo::Ray&) const = 0; 
        virtual geo::Vec normal_at(const geo::Point&) const = 0; 

        Hittable() : material(), m_transformation(xform::identity()) {}
        virtual ~Hittable() = default; 

        Hittable& set_color(const color::RGB&); 
        Hittable& set_ambient(double);
        Hittable& set_diffuse(double);
        Hittable& set_specular(double);
        Hittable& transform(const xform::Matrix<4>&);
        Hittable& set_material(const Material&);

        Material material; 

    protected: 
        xform::Matrix<4> m_transformation; 
        
    };

    class Sphere : public Hittable { 

    public: 

        Sphere();
        std::vector<geo::Intersection> intersect(const geo::Ray&) const override; 
        geo::Vec normal_at(const geo::Point&) const override;

    private: 
        geo::Point m_origin;

    };

    class Plane : public Hittable {

    public:

        std::vector<geo::Intersection> intersect(const geo::Ray&) const override;
        geo::Vec normal_at(const geo::Point&) const override;
        
    };
}

#endif