
#include "color/color.hpp"
#include <cmath> 
#include "scene/hittable.hpp"
#include "geo/tuples.hpp"


using namespace color; 

/* ----- Base class ------*/


Pattern& Pattern::transform(const xform::Matrix<4>& transformation) { 
    m_transformation = m_transformation * transformation; 
    return *this; 
}

RGB Pattern::color_at_object(const scene::Hittable* object, const geo::Point& world_point) const { 
    geo::Point object_point = xform::inverse(object->get_transformation()) * world_point;
    geo::Point pattern_point = xform::inverse(m_transformation) * object_point;

    return color_at(pattern_point);
}

Pattern& Pattern::set_first_color(const RGB& color) { 
    color1 = color; 
    return *this; 
}

Pattern& Pattern::set_second_color(const RGB& color) { 
    color2 = color; 
    return *this; 
}



RGB Stripes::color_at(const geo::Point& point) const { 
    int rounded_x = floor(point.x);
    if (rounded_x % 2 == 0) {
        return color2; 
    }
    return color1; 
}


RGB Gradient::color_at(const geo::Point& point) const { 

    RGB distance(color2.r - color1.r, color2.g - color1.g, color2.b - color1.b);

    double fraction = point.y - floor(std::abs(point.y));

    return color1 + distance * fraction; 
} 

RGB Rings::color_at(const geo::Point& point) const { 
    int num = floor(sqrt((point.x * point.x) + (point.z * point.z)));
    if (num % 2 == 0) { 
        return color1;
    }
    return color2;
}

RGB Checkers::color_at(const geo::Point& point) const {     
    if (int((round(point.x)) + round(point.y) + round(point.z)) % 2 == 0) { 
        return color1;
    }
    return color2;
}










