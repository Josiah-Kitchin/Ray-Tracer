

#include "scene/world.hpp"
#include "scene/material.hpp"
#include <algorithm> 

using scene::World; 

World::World() : m_objects(std::vector<scene::Hittable*>{}), 
                 m_lights(std::vector<scene::Light>{ scene::Light(color::RGB(1, 1, 1), geo::Point(-10, 10, -10)) }) {}



std::vector<geo::Intersection> World::intersects(const geo::Ray& ray) { 
    /* Return a vector of all intersections of objects in the world in sorted order*/

    std::vector<geo::Intersection> intersections; 
    intersections.reserve(m_objects.size() * 500);

    for (const auto object : m_objects) {
        auto object_intersections = object->intersect(ray);
        for (const auto& intersection : object_intersections) { 
            intersections.emplace_back(intersection);
        }
    }
    std::sort(intersections.begin(), intersections.end(), [](geo::Intersection a, geo::Intersection b) {
        return a.t < b.t;
    });
    return intersections; 
}

color::RGB World::shade_hit(const geo::IntersectionState& state) { 
    /* Calculate the color for an intersection based on the worlds lights and the intersection state */
    color::RGB shade; 
    for (const auto& light : m_lights) { 
       shade += calculate_lighting(state.object->material, light, state.point, state.eye, state.normal);
    }
    return shade; 
}

color::RGB World::color_at(const geo::Ray& ray) { 
    /* Encapuslate some of the intersection logic in one function */
    auto intersections = intersects(ray);
    geo::Intersection object_hit = geo::hit(intersections);
    if (object_hit == geo::Intersection(0, nullptr)) { 
        //Miss 
        return color::RGB(0, 0, 0);
    }
    geo::IntersectionState state(object_hit, ray);
    return shade_hit(state);
}


/* ----------------- Interface Methods ------------------ */

World& World::set_lights(const std::vector<scene::Light>& in_lights) { 
    m_lights = in_lights; 
    return *this; 
}

World& World::set_objects(const std::vector<scene::Hittable*>& in_objects) { 
    m_objects = in_objects; 
    return *this; 
}

World& World::add_light(const scene::Light& light) { 
    m_lights.emplace_back(light);
    return *this; 
}

World& World::add_object(scene::Hittable* object) { 
    m_objects.emplace_back(object);
    return *this;
}







    