
#ifndef VEC_HPP
#define VEC_HPP

#include <cmath> 
#include <iostream> 


namespace geo {

    class Vec { 
    public: 
        double x, y, z; 

        Vec(); 
        Vec(double, double, double); 

        Vec operator-() const; 
        Vec& operator+=(const Vec&); 
        Vec& operator*=(const Vec&); 
        Vec& operator*=(double); 
        Vec& operator/=(double); 

        bool near_zero() const; 
        double length_squared() const; 
        double length() const; 
    };


    Vec cross(const Vec&, const Vec&); 
    Vec unit_vector(const Vec&); 
    double dot(const Vec&, const Vec&);

    Vec reflect(const Vec&, const Vec&);



    class Point { 
    public:
        double x, y, z; 

        Point(); 
        Point(double, double, double); 
        
        Point& operator+=(const Vec&); 
    };
}


geo::Vec operator+(const geo::Vec&, const geo::Vec&);
geo::Vec operator-(const geo::Vec&, const geo::Vec&); 
geo::Vec operator*(const geo::Vec&, const geo::Vec&); 
geo::Vec operator*(const geo::Vec&, double); 
geo::Vec operator*(double, const geo::Vec&); 
geo::Vec operator/(const geo::Vec&, double); 
bool operator==(const geo::Vec&, const geo::Vec&); 
bool operator!=(const geo::Vec&, const geo::Vec&); 
std::ostream& operator<<(std::ostream&, const geo::Vec&); 


geo::Point operator+(const geo::Point&, const geo::Vec&);
geo::Point operator+(const geo::Vec&, const geo::Point&);  
geo::Vec operator-(const geo::Point&, const geo::Point&); 
bool operator==(const geo::Point&, const geo::Point&); 
bool operator!=(const geo::Point&, const geo::Point&); 
std::ostream& operator<<(std::ostream&, const geo::Point&);


#endif 

