
#include "intersection.hpp" 

/*The intersection class holds the t at which the intersect occurs and a pointer to the 
object that was intersected*/

Intersection::Intersection(double t, const Hittable* object) : t(t), object(object) {};  

bool operator==(const Intersection& i1, const Intersection& i2) { 
    return i1.t == i2.t && i1.object == i2.object;
}

Intersection hit(std::vector<Intersection>& intersections) { 
    //finds what gets hit out of a list of interesections by returning the intersection 
    //with the lowest t. If there are no hits, returns an intersection with a nullptr object 
    if (intersections.empty()) return Intersection(0, nullptr); 

    Intersection min = intersections.at(0);  
    for (const auto intersection : intersections) { 
        if (intersection.t >= 0 && intersection.t < min.t) { 
            min = intersection; 
        }
    }
    if (min.t < 0) { 
        return Intersection(0, nullptr);
    }
    return min;  
}




