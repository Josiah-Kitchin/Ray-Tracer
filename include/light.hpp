#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "tuples.hpp"

class Light { 
public: 
    Color intensity; 
    Point position; 

    Light(const Color&, const Point&);
    
};


#endif