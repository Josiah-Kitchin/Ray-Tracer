#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <vector> 

namespace scene {
    class Hittable; 
}

namespace geo { 
    class Intersection { 
    /* Represents a ray intersecting with a hittable object */ 

    public: 
        double t; 
        const scene::Hittable* object; 

        Intersection(double, const scene::Hittable*);
    };

    //Returns the index of which intersection was actually hit given a vector of intersections
    int hit_index(const std::vector<Intersection>&); 

    bool operator==(const Intersection&, const Intersection&); 

}


#endif

