
#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream> 
#include <geo/tuples.hpp> 

namespace color {

class RGB { 
    public: 
        double r, g, b; 

        RGB();
        RGB(double, double, double); 

        RGB& operator+=(const RGB&); 
        RGB& operator+=(const geo::Point&); 

        void clamp(); 
        void convert_to_256(); 
    };
}

color::RGB operator+(const color::RGB&, const color::RGB&);  
color::RGB operator+(const color::RGB&, const geo::Point&); 
color::RGB operator+(const color::RGB&, const color::RGB&);
bool operator==(const color::RGB&, const color::RGB&);
bool operator!=(const color::RGB&, const color::RGB&); 
color::RGB operator*(const color::RGB&, const color::RGB&);
color::RGB operator*(const color::RGB&, double);
color::RGB operator*(double, const color::RGB&);
std::ostream& operator<<(std::ostream&, const color::RGB&);

#endif
