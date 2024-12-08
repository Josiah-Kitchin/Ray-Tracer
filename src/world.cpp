

#include "world.hpp"
#include <algorithm> 


World::World() : objects(std::vector<Hittable*>{}), 
                 lights(std::vector<Light>{ Light(Color(1, 1, 1), Point(-10, 10, -10))}) {}



std::vector<Intersection> World::intersects(const Ray& ray) { 
    /* Return a vector of all intersections of objects in the world in sorted order*/

    std::vector<Intersection> intersections; 
    for (const auto object : objects) {
        auto object_intersections = object->intersect(ray);
        for (const auto intersection : object_intersections) { 
            intersections.push_back(intersection);
        }
    }
    std::sort(intersections.begin(), intersections.end(), [](Intersection a, Intersection b) {
        return a.t < b.t;
    });
    return intersections; 
}




    