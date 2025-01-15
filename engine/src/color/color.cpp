
#include "color/color.hpp"
#include "geo/tuples.hpp"
#include "utils.hpp"

using color::RGB; 

/*-------------Color-------------*/


RGB::RGB() : r(0), g(0), b(0) {}
RGB::RGB(double r, double g, double b) : r(r), g(g), b(b) {}

RGB& RGB::operator+=(const RGB& other) { 
    r += other.r; 
    g += other.g; 
    b += other.b; 
    return *this; 
}

RGB& RGB::operator+=(const geo::Point& point) { 
    r += point.x; 
    g += point.y; 
    b += point.z; 
    return *this; 
}

RGB color::operator+(const RGB& left, const RGB& right) { 
    return RGB(left.r + right.r, left.g + right.g, left.b + right.b); 
}

RGB color::operator+(const RGB& color, const geo::Point& point) { 
    return RGB(color.r + point.x, color.g + point.y, color.b + point.z); 
}

RGB color::operator+(const geo::Point& point, const RGB& color) { 
    return color + point; 
}

bool color::operator==(const RGB& left, const RGB& right) { 
    return utils::compare_doubles(left.r, right.r) && 
           utils::compare_doubles(left.g, right.g) && 
           utils::compare_doubles(left.b, right.b); 
}

bool color::operator!=(const RGB& left, const RGB& right) { 
    return !(left == right); 
}

RGB color::operator*(const RGB& left, const RGB& right) { 
    return RGB(left.r * right.r, left.g * right.g, left.b * right.b);
}

RGB color::operator*(const RGB& color, double num) { 
    return RGB(color.r * num, color.g * num, color.b * num);
}

RGB color::operator*(double num, const RGB& color) { 
    return color * num; 
}

std::ostream& color::operator<<(std::ostream& out, const RGB& color) { 
    out << "(" << color.r << ", " << color.g << ", " << color.b << ")";
    return out; 
}


void RGB::clamp() { 
    if (r > 1) r = 1; 
    if (r < 0) r = 0;  

    if (g > 1) g = 1; 
    if (g < 0) g = 0; 

    if (b > 1) b = 1;  
    if (b < 0) b = 0;  
}

void RGB::convert_to_256() { 
    clamp(); 
    r = round(255 * r); 
    g = round(255 * g); 
    b = round(255 * b); 
}

RGB color::black() { 
    return RGB(0, 0, 0);
}

RGB color::white() { 
    return RGB(1, 1, 1);
}

RGB color::blue() { 
    return RGB(0, 0, 1);
}

RGB color::red() { 
    return RGB(1, 0, 0);
}

RGB color::green() { 
    return RGB(0, 1, 0);
}
















