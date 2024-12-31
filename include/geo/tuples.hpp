
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

    Vec operator+(const Vec&, const Vec&);
    Vec operator-(const Vec&, const Vec&); 
    Vec operator*(const Vec&, const Vec&); 
    Vec operator*(const Vec&, double); 
    Vec operator*(double, const Vec&); 
    Vec operator/(const Vec&, double); 
    bool operator==(const Vec&, const Vec&); 
    bool operator!=(const Vec&, const Vec&); 
    std::ostream& operator<<(std::ostream&, const Vec&); 


    Point operator+(const Point&, const Vec&);
    Point operator+(const Vec&, const Point&);  
    Vec operator-(const Point&, const Point&); 
    bool operator==(const Point&, const Point&); 
    bool operator!=(const Point&, const Point&); 
    std::ostream& operator<<(std::ostream&, const Point&);

}

#endif 