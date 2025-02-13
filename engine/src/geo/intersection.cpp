
#include "geo/intersection.hpp"

/*The intersection class holds the t at which the intersect occurs and a pointer
to the object that was intersected*/

using geo::Intersection;

Intersection::Intersection(double t, const scene::Hittable *object)
    : t(t), object(object){};

bool geo::operator==(const Intersection &i1, const Intersection &i2) {
    return i1.t == i2.t && i1.object == i2.object;
}

int geo::hit_index(const std::vector<Intersection> &intersections) {
    // finds what gets hit out of a list of interesections by returning the
    // index of the intersection with the lowest t. If there are no hits,
    // returns -1
    if (intersections.empty())
        return -1;

    float min_t = intersections.at(0).t;
    int min_index = 0;
    for (size_t i = 0; i < intersections.size(); ++i) {
        if (intersections[i].t >= 0 &&
            (min_t < 0 || intersections[i].t < min_t)) {
            min_t = intersections[i].t;
            min_index = i;
        }
    }
    if (min_t < 0)
        return -1;

    return min_index;
}
