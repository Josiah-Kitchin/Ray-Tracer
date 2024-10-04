
#ifndef VEC_HPP
#define VEC_HPP

#include <cmath> 
#include <iostream> 


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
Vec operator+(const Vec&, const Vec&);
Vec operator-(const Vec&, const Vec&); 
Vec operator*(const Vec&, const Vec&); 
Vec operator*(const Vec&, double); 
Vec operator*(double, const Vec&); 
Vec operator/(const Vec&, double); 
bool operator==(const Vec&, const Vec&); 
bool operator!=(const Vec&, const Vec&); 
std::ostream& operator<<(std::ostream&, const Vec&); 



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
Point operator+(const Point&, const Vec&);
Point operator+(const Vec&, const Point&);  
Vec operator-(const Point&, const Point&); 
bool operator==(const Point&, const Point&); 
bool operator!=(const Point&, const Point&); 
std::ostream& operator<<(std::ostream&, const Point&);

class Color { 
public: 
    double r, g, b; 

    Color();
    Color(double, double, double); 

    Color& operator+=(const Color&); 
    Color& operator+=(const Point&); 

    void clamp(); 
    void convert_to_256(); 
};
Color operator+(const Color&, const Color&);  
Color operator+(const Color&, const Point&); 
Color operator+(const Point&, const Color&);
bool operator==(const Color&, const Color&);
bool operator!=(const Color&, const Color&); 
Color operator*(const Color&, const Color&);
Color operator*(const Color&, double);
Color operator*(double, const Color&);
std::ostream& operator<<(std::ostream&, const Color&);


#endif 

