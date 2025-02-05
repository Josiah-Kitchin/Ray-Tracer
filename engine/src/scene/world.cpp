

#include "scene/world.hpp"
#include "scene/material.hpp"
#include <algorithm> 

using scene::World; 

World::World() : m_objects(std::vector<scene::Hittable*>{}), 
                 m_lights(std::vector<scene::Light>{ scene::Light(color::RGB(1, 1, 1), geo::Point(-10, 10, -10)) }), 
                 reflection_limit(50) {}



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

color::RGB World::shade_hit(const geo::IntersectionState& state, int recursive_reflection_limit) { 
    /* Calculate the color for an intersection based on the worlds lights and the intersection state */
    bool is_shadow = is_shadowed(state.over_point);
    
    color::RGB surface; 
    for (const auto& light : m_lights) { 
        surface += calculate_lighting(state.object, light, state.point, state.eye, state.normal, is_shadow);
    }

    color::RGB reflected = reflect_color(state, recursive_reflection_limit);
    color::RGB refracted = refract_color(state, recursive_reflection_limit);

    return surface + reflected + refracted; 
}

color::RGB World::color_at(const geo::Ray& ray, int recursive_reflection_limit) { 
    /* Encapuslate some of the intersection logic in one function */
    auto intersections = intersects(ray);
    int object_hit_idx = geo::hit_index(intersections);

    if (object_hit_idx == -1) { 
        return color::RGB(0, 0, 0);
    }

    geo::IntersectionState state(object_hit_idx, intersections, ray);
    return shade_hit(state, recursive_reflection_limit);
}

bool World::is_shadowed(const geo::Point& point) { 
    /* Cast a ray from the point to the lights to see if anything is hit between them 
       If so, it is shadowed */
    
    for (const auto& light: m_lights) { 
        geo::Vec point_to_light = light.m_position - point;
        double distance = point_to_light.length();
        geo::Vec direction = unit_vector(point_to_light);

        geo::Ray ray_from_point(point, direction);
        const auto intersections = intersects(ray_from_point);
        int intersected_ray_idx = geo::hit_index(intersections);
        
        if ((intersected_ray_idx == -1) || intersections[intersected_ray_idx].t >= distance) { 
            return false;
        } 
    }
    return true; 
}

color::RGB World::reflect_color(const geo::IntersectionState& state, int recursive_reflection_limit) {
    if (recursive_reflection_limit < 1) { 
        return color::black(); 
    }
    
    if (state.object->material.reflective == 0) { 
        return color::black(); 
    }
    geo::Ray reflect_ray(state.over_point, state.reflect);
    color::RGB color = color_at(reflect_ray, recursive_reflection_limit - 1);
    return color * state.object->material.reflective; 
}

color::RGB World::refract_color(const geo::IntersectionState& state, int recursive_reflection_limit) { 
    if (recursive_reflection_limit < 1) { 
        return color::black(); 
    }

    if (state.object->material.transparency == 0) { 
        return color::black(); 
    }

    double n_ratio = state.n1 / state.n2; 
    double cos_i = geo::dot(state.eye, state.normal);
    double sin2_t = (n_ratio * n_ratio) * (1 - (cos_i * cos_i));

    if (sin2_t > 1) { //total internal reflection 
        return color::black(); 
    }

    double cos_t = sqrt(1.0 - sin2_t);
    geo::Vec refract_direction = state.normal * (n_ratio * cos_i - cos_t) - state.eye * n_ratio; 
    geo::Ray refract_ray(state.under_point, refract_direction);

    color::RGB color = color_at(refract_ray, recursive_reflection_limit - 1) *
                       state.object->material.transparency;

    return color; 
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

World& World::set_reflection_limit(int limit) { 
    reflection_limit = limit; 
    return *this; 
}







    
