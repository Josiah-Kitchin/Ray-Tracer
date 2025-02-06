
#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "color/color.hpp"


namespace scene 
{ 
    class Hittable; 
}

namespace color 
{

    class Pattern 
    { 
    /* Apply a pattern to a hittable object 
     * Patterns can be transformed
     * Because of the pattern abstract class, patterns must be added to 
     * materials by address */ 

    public:
        virtual RGB color_at(const geo::Point&) const = 0;       
        RGB color_at_object(const scene::Hittable*, const geo::Point&) const;

        Pattern& transform(const xform::Matrix<4>&);

        Pattern& set_first_color(const color::RGB&);
        Pattern& set_second_color(const color::RGB&);

    protected:

        RGB color1 = color::black(), color2 = color::white(); 
        xform::Matrix<4> m_transformation = xform::identity(); 
    };

    //DIfferent patterns will return a different color at a given point 

    class Stripes : public Pattern 
    {
    public: 
        RGB color_at(const geo::Point&) const override; 
    };

    class Gradient : public Pattern 
    { 
    public: 
        RGB color_at(const geo::Point&) const override; 
    };

    class Rings : public Pattern 
    { 
    public:
        RGB color_at(const geo::Point&) const override; 
    };

    class Checkers : public Pattern 
    { 
    public: 
        RGB color_at(const geo::Point&) const override; 
    };
    
}

#endif 
