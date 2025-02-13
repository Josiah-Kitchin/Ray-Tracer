
#ifndef COLOR_HPP
#define COLOR_HPP

#include "geo/tuples.hpp"
#include "xform/matrices.hpp"
#include <iostream>

namespace color {

class RGB {
    /* Represent a red, green, blue color
     * Color values lie between 0 and 1 and will be converted to 256 come
     * time to display colors */
  public:
    double r, g, b;

    RGB();
    RGB(double, double, double);

    RGB &operator+=(const RGB &);
    RGB &operator+=(const geo::Point &);
    RGB &operator/=(double);

    // Set color range to 0 and 1 if outside 0 and 1
    void clamp();
    // Change rgb to 256 based
    void convert_to_256();
};

RGB black();
RGB white();
RGB red();
RGB green();
RGB blue();

RGB operator+(const RGB &, const RGB &);
RGB operator+(const RGB &, const geo::Point &);
RGB operator+(const geo::Point &, const RGB &);
RGB operator+(const RGB &, const RGB &);
bool operator==(const RGB &, const RGB &);
bool operator!=(const RGB &, const RGB &);
RGB operator*(const RGB &, const RGB &);
RGB operator*(const RGB &, double);
RGB operator*(double, const RGB &);
std::ostream &operator<<(std::ostream &, const RGB &);

} // namespace color

#endif
