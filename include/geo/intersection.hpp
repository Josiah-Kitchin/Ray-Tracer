#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <vector> 

namespace scene {
    class Hittable; 
}

namespace geo { 
    class Intersection { 
    public: 
        double t; 
        const scene::Hittable* object; 

        Intersection(double, const scene::Hittable*);
    };

    Intersection hit(std::vector<Intersection>&); 
    bool is_miss(const Intersection&);

    bool operator==(const Intersection&, const Intersection&); 

}


#endif

