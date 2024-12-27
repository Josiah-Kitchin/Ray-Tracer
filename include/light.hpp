#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "tuples.hpp"
#include "material.hpp"

struct Light { 
public: 
    Light(const Color&, const Point&);
    Light();
    Light& set_intensity(const Color&); 
    Light& set_position(const Point&);

    friend Color calculate_lighting(const Material&, const Light&, const Point&, const Vec&, const Vec&);

private:
    Color intensity; 
    Point position; 

    
};


Color calculate_lighting(const Material&, const Light&, const Point&, const Vec&, const Vec&);


#endif