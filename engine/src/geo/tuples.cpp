

#include "geo/tuples.hpp"
#include "utils.hpp"
#include <cassert>

/* The tuples included the classes Vec, Point, and RGB.
The Vec is a direction in 3d space, while a Point is a coordinate in 3d space
The Color holds an r, g, and b */

/*-------------Vec-------------*/
using geo::Point;
using geo::Vec;

Vec::Vec() : x(0), y(0), z(0) {}
Vec::Vec(double x, double y, double z) : x(x), y(y), z(z) {}

Vec Vec::operator-() const { return Vec(-x, -y, -z); }

Vec &Vec::operator+=(const Vec &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec &Vec::operator*=(const Vec &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Vec &Vec::operator*=(double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Vec &Vec::operator/=(double t) { return *this *= 1 / t; }

Vec geo::operator+(const Vec &left, const Vec &right) {
    return Vec(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vec geo::operator-(const Vec &left, const Vec &right) {
    return Vec(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vec geo::operator*(const Vec &left, const Vec &right) {
    return Vec(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vec geo::operator*(const Vec &left, double t) {
    return Vec(left.x * t, left.y * t, left.z * t);
}

Vec geo::operator*(double t, const Vec &right) { return right * t; }

Vec geo::operator/(const Vec &right, double t) { return (1 / t) * right; }

bool geo::operator==(const Vec &left, const Vec &right) {
    return utils::compare_doubles(left.x, right.x) &&
           utils::compare_doubles(left.y, right.y) &&
           utils::compare_doubles(left.z, right.z);
}

bool geo::operator!=(const Vec &left, const Vec &right) {
    return !(left == right);
}

std::ostream &geo::operator<<(std::ostream &out, const Vec &vec) {
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
}

double Vec::length_squared() const { return x * x + y * y + z * z; }

double Vec::length() const { return std::sqrt(length_squared()); }

Vec geo::cross(const Vec &v1, const Vec &v2) {
    // Provides the vector perpendicular to where two vectors cross
    return Vec(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
               v1.x * v2.y - v1.y * v2.x);
}

Vec geo::unit_vector(const Vec &v) {
    // The unit vector is meant to provide direction without changing magnitude
    if (v.length() == 0)
        return v;

    return v / v.length();
}

double geo::dot(const Vec &v1, const Vec &v2) {
    // The extent to which to vectors point in the same direction
    // positive is pointing to the same general direcition,
    // negative the opposite direction, and 0 is perpindicular
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

bool Vec::near_zero() const {
    // Return true if the vector is close to zero in all dimensions.
    auto s = 1e-8;
    return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
}

Vec geo::reflect(const Vec &in, const Vec &normal) {
    // Takes a vector and the normal, than returns the vector that is reflected
    // off of the normal
    return in - normal * 2 * geo::dot(in, normal);
}
/*------------- Point -------------*/

Point::Point() : x(0), y(0), z(0) {}
Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

Point &Point::operator+=(const Vec &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Point geo::operator+(const Point &point, const Vec &vec) {
    return Point(point.x + vec.x, point.y + vec.y, point.z + vec.z);
}

Point geo::operator+(const Vec &v, const Point &p) { return p + v; }

Vec geo::operator-(const Point &left, const Point &right) {
    return Vec(left.x - right.x, left.y - right.y, left.z - right.z);
}

bool geo::operator==(const Point &left, const Point &right) {
    return utils::compare_doubles(left.x, right.x) &&
           utils::compare_doubles(left.y, right.y) &&
           utils::compare_doubles(left.z, right.z);
}

bool geo::operator!=(const Point &left, const Point &right) {
    return !(left == right);
}

std::ostream &geo::operator<<(std::ostream &out, const Point &point) {
    out << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    return out;
}
