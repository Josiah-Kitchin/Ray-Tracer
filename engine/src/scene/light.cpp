
#include "scene/light.hpp"
#include "scene/hittable.hpp"

using scene::Light; 
Light::Light(const color::RGB& intensity, const geo::Point& position) : m_intensity(intensity), m_position(position) {}
Light::Light() : m_intensity(color::RGB()), m_position(geo::Point()) {}

Light& Light::set_intensity(const color::RGB& intensity) { 
    m_intensity = intensity; 
    return *this; 
}

Light& Light::set_position(const geo::Point& position) { 
    m_position = position; 
    return *this; 
}

color::RGB calculate_lighting(const scene::Hittable* object, const Light& light, const geo::Point& position, 
                              const geo::Vec& eye, const geo::Vec& normal, bool in_shadow) { 
    /* Phong Reflection Model */

    scene::Material mat = object->material; 

    color::RGB color; 
    if (mat.m_pattern != nullptr) { 
        color = mat.m_pattern->color_at_object(object, position);
    } else { 
        color = mat.color; 
    } 

    color::RGB ambient, diffuse, specular; 

    color::RGB effective_color = color * light.m_intensity; 

    geo::Vec light_direction = geo::unit_vector(light.m_position - position);

    ambient = effective_color * mat.ambient; 
    if (in_shadow) { 
        return ambient;
    }

    double light_dot_normal = geo::dot(light_direction, normal); 

    if (light_dot_normal < 0) { 
        diffuse = color::RGB(0, 0, 0); 
        specular = color::RGB(0, 0, 0);
    } else { 
        diffuse = effective_color * mat.diffuse * light_dot_normal; 
        geo::Vec reflect_direction = geo::reflect(-light_direction, normal);
        double reflect_dot_eye = geo::dot(reflect_direction, eye);

        if (reflect_dot_eye <= 0) { 
            specular = color::RGB(0, 0, 0);
        } else { 
            double factor = pow(reflect_dot_eye, mat.shininess);
            specular = light.m_intensity * mat.specular * factor; 
        }
    }
    return ambient + diffuse + specular; 
}

