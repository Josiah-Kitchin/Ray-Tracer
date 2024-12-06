

#include "tuples.hpp" 
#include "utils.hpp"
#include <cassert> 



/* The tuples included the classes Vec, Point, and Color. 
The Vec is a direction in 3d space, while a Point is a coordinate in 3d space 
The Color holds an r, g, and b */ 



/*-------------Vec-------------*/

Vec::Vec() : x(0), y(0), z(0) {} 
Vec::Vec(double x, double y, double z) : x(x), y(y), z(z) {}

Vec Vec::operator-() const { return Vec(-x, -y, -z); } 
    
Vec& Vec::operator+=(const Vec& other) { 
    x += other.x; 
    y += other.y; 
    z += other.z; 
    return *this; 
}

Vec& Vec::operator*=(const Vec& other) { 
    x *= other.x; 
    y *= other.y; 
    z *= other.z; 
    return *this; 
}

Vec& Vec::operator*=(double t) { 
    x *= t; 
    y *= t; 
    z *= t; 
    return *this; 
}

Vec& Vec::operator/=(double t) { 

    return *this *= 1/t; 
}


Vec operator+(const Vec& left, const Vec& right) { 
    return Vec(left.x + right.x, left.y + right.y, left.z + right.z); 
}

Vec operator-(const Vec& left, const Vec& right) { 
    return Vec(left.x - right.x, left.y - right.y, left.z - right.z); 
}

Vec operator*(const Vec& left, const Vec& right) { 
    return Vec(left.x * right.x, left.y * right.y, left.z * right.z); 
}

Vec operator*(const Vec& left, double t) { 
    return Vec(left.x * t, left.y * t, left.z * t); 
}

Vec operator*(double t, const Vec& right) { 
    return right * t; 
}

Vec operator/(const Vec& right, double t) { 
    return (1/t) * right; 
}

bool operator==(const Vec& left, const Vec& right) { 
    return compare_doubles(left.x, right.x) && 
           compare_doubles(left.y, right.y) && 
           compare_doubles(left.z, right.z); 
}

bool operator!=(const Vec& left, const Vec& right) { 
    return !(left == right); 
}

std::ostream& operator<<(std::ostream& out, const Vec& vec) { 
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out; 
}

double Vec::length_squared() const { 
    return x*x + y*y + z*z; 
}

double Vec::length() const { 
    return std::sqrt(length_squared()); 
}

Vec cross(const Vec& v1, const Vec& v2) { 
    //Provides the vector perpendicular to where two vectors cross
    return Vec(v1.y * v2.z - v1.z * v2.y, 
               v1.z * v2.x - v1.x * v2.z, 
               v1.x * v2.y - v1.y * v2.x); 
}

Vec unit_vector(const Vec& v) { 
    //The unit vector is meant to provide direction without changing magnitude 
    return v / v.length(); 
}

double dot(const Vec& v1, const Vec& v2) { 
    //The extent to which to vectors point in the same direction 
    //positive is pointing to the same general direcition, 
    //negative the opposite direction, and 0 is perpindicular
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

bool Vec::near_zero() const { 
    // Return true if the vector is close to zero in all dimensions.
    auto s = 1e-8;
    return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
}

Vec reflect(const Vec& in, const Vec& normal) { 
    //Takes a vector and the normal, than returns the vector that is reflected 
    //off of the normal 
    return in - normal * 2 * dot(in, normal); 
}
/*------------- Point -------------*/

Point::Point() : x(0), y(0), z(0) {} 
Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

Point& Point::operator+=(const Vec& v) { 
    x += v.x; 
    y += v.y; 
    z += v.z; 
    return *this; 
}

Point operator+(const Point& point, const Vec& vec) { 
    return Point(point.x + vec.x, point.y + vec.y, point.z + vec.z); 
}

Point operator+(const Vec& v, const Point& p) { 
    return p + v; 
}

Vec operator-(const Point& left, const Point& right) {
    return Vec(left.x - right.x, left.y - right.y, left.z - right.z);
}

bool operator==(const Point& left, const Point& right) {
    return compare_doubles(left.x, right.x) && 
           compare_doubles(left.y, right.y) && 
           compare_doubles(left.z, right.z); 
}

bool operator!=(const Point& left, const Point& right) { 
    return !(left == right); 
}

std::ostream& operator<<(std::ostream& out, const Point& point) { 
    out << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    return out; 
}



/*-------------Color-------------*/

Color::Color() : r(0), g(0), b(0) {}
Color::Color(double r, double g, double b) : r(r), g(g), b(b) {}

Color& Color::operator+=(const Color& other) { 
    r += other.r; 
    g += other.g; 
    b += other.b; 
    return *this; 
}

Color& Color::operator+=(const Point& point) { 
    r += point.x; 
    g += point.y; 
    b += point.z; 
    return *this; 
}

Color operator+(const Color& left, const Color& right) { 
    return Color(left.r + right.r, left.g + right.g, left.b + right.b); 
}

Color operator+(const Color& color, const Point& point) { 
    return Color(color.r + point.x, color.g + point.y, color.b + point.z); 
}

Color operator+(const Point& point, const Color& color) { 
    return color + point; 
}

bool operator==(const Color& left, const Color& right) { 
    return compare_doubles(left.r, right.r) && 
           compare_doubles(left.g, right.g) && 
           compare_doubles(left.b, right.b); 
}

bool operator!=(const Color& left, const Color& right) { 
    return !(left == right); 
}

Color operator*(const Color& left, const Color& right) { 
    return Color(left.r * right.r, left.g * right.g, left.b * right.b);
}

Color operator*(const Color& color, double num) { 
    return Color(color.r * num, color.g * num, color.b * num);
}

Color operator*(double num, const Color& color) { 
    return color * num; 
}

std::ostream& operator<<(std::ostream& out, const Color& color) { 
    out << "(" << color.r << ", " << color.g << ", " << color.b << ")";
    return out; 
}


void Color::clamp() { 
    if (r > 1) r = 1; 
    if (r < 0) r = 0;  

    if (g > 1) g = 1; 
    if (g < 0) g = 0; 

    if (b > 1) b = 1;  
    if (b < 0) b = 0;  
}

void Color::convert_to_256() { 
    clamp(); 
    r = round(255 * r); 
    g = round(255 * g); 
    b = round(255 * b); 
}












