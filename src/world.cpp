

#include "world.hpp"
#include "material.hpp"
#include <algorithm> 


World::World() : m_objects(std::vector<Hittable*>{}), 
                 m_lights(std::vector<Light>{ Light(Color(1, 1, 1), Point(-10, 10, -10))}) {}



std::vector<Intersection> World::intersects(const Ray& ray) { 
    /* Return a vector of all intersections of objects in the world in sorted order*/

    std::vector<Intersection> intersections; 
    intersections.reserve(500);

    for (const auto object : m_objects) {
        auto object_intersections = object->intersect(ray);
        for (const auto& intersection : object_intersections) { 
            intersections.emplace_back(intersection);
        }
    }
    std::sort(intersections.begin(), intersections.end(), [](Intersection a, Intersection b) {
        return a.t < b.t;
    });
    return intersections; 
}

Color World::shade_hit(const IntersectionState& state) { 
    /* Calculate the color for an intersection based on the worlds lights and the intersection state */
    Color shade; 
    for (const auto& light : m_lights) { 
       shade += calculate_lighting(state.object->material, light, state.point, state.eye, state.normal);
    }
    return shade; 
}

Color World::color_at(const Ray& ray) { 
    /* Encapuslate some of the intersection logic in one function */
    auto intersections = intersects(ray);
    Intersection object_hit = hit(intersections);
    if (object_hit == Intersection(0, nullptr)) {
        return Color(0, 0, 0);
    }
    IntersectionState state(object_hit, ray);
    return shade_hit(state);
}


/* ----------------- Interface Methods ------------------ */

World& World::set_lights(const std::vector<Light>& in_lights) { 
    m_lights = in_lights; 
    return *this; 
}

World& World::set_objects(const std::vector<Hittable*>& in_objects) { 
    m_objects = in_objects; 
    return *this; 
}

World& World::add_light(const Light& light) { 
    m_lights.emplace_back(light);
    return *this; 
}

World& World::add_object(Hittable* object) { 
    m_objects.emplace_back(object);
    return *this;
}







    