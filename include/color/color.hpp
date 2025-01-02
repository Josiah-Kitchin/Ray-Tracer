
#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream> 
#include "geo/tuples.hpp" 
#include "xform/matrices.hpp" 


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

    RGB black(); 
    RGB white(); 
    RGB red(); 
    RGB green(); 
    RGB blue(); 

    RGB operator+(const RGB&, const RGB&);  
    RGB operator+(const RGB&, const geo::Point&); 
    RGB operator+(const geo::Point&, const RGB&);
    RGB operator+(const RGB&, const RGB&);
    bool operator==(const RGB&, const RGB&);
    bool operator!=(const RGB&, const RGB&); 
    RGB operator*(const RGB&, const RGB&);
    RGB operator*(const RGB&, double);
    RGB operator*(double, const RGB&);
    std::ostream& operator<<(std::ostream&, const RGB&);


}

#endif
