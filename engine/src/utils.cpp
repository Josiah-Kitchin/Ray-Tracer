

#include "utils.hpp"
#include <cmath>

const double utils::EPSILON = 0.00001;

bool utils::compare_doubles(double x, double y) {
    if (fabs(x - y) < utils::EPSILON)
        return true;

    return false;
}
