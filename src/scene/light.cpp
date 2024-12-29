
#include "scene/light.hpp"


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

color::RGB calculate_lighting(const scene::Material& mat, const Light& light, const geo::Point& position, 
                              const geo::Vec& eye, const geo::Vec& normal) { 
    /* Phong Reflection Model */

    color::RGB ambient, diffuse, specular; 

    color::RGB effective_color = mat.color * light.m_intensity; 

    geo::Vec light_direction = unit_vector(light.m_position - position);

    ambient = effective_color * mat.ambient; 

    double light_dot_normal = dot(light_direction, normal); 

    if (light_dot_normal < 0) { 
        diffuse = color::RGB(0, 0, 0); 
        specular = color::RGB(0, 0, 0);
    } else { 
        diffuse = effective_color * mat.diffuse * light_dot_normal; 
        geo::Vec reflect_direction = reflect(-light_direction, normal);
        double reflect_dot_eye = dot(reflect_direction, eye);

        if (reflect_dot_eye <= 0) { 
            specular = color::RGB(0, 0, 0);
        } else { 
            double factor = pow(reflect_dot_eye, mat.shininess);
            specular = light.m_intensity * mat.specular * factor; 
        }
    }
    return ambient + diffuse + specular; 
}

