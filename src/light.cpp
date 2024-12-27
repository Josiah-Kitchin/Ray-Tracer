
#include "light.hpp"


Light::Light(const Color& intensity, const Point& position) : m_intensity(intensity), m_position(position) {}
Light::Light() : m_intensity(Color()), m_position(Point()) {}

Light& Light::set_intensity(const Color& intensity) { 
    m_intensity = intensity; 
    return *this; 
}

Light& Light::set_position(const Point& position) { 
    m_position = position; 
    return *this; 
}

Color calculate_lighting(const Material& mat, const Light& light, const Point& position, const Vec& eye, const Vec& normal) { 
    /* Phong Reflection Model */

    Color ambient, diffuse, specular; 

    Color effective_color = mat.color * light.m_intensity; 

    Vec light_direction = unit_vector(light.m_position - position);

    ambient = effective_color * mat.ambient; 

    double light_dot_normal = dot(light_direction, normal); 

    if (light_dot_normal < 0) { 
        diffuse = Color(0, 0, 0); 
        specular = Color(0, 0, 0);
    } else { 
        diffuse = effective_color * mat.diffuse * light_dot_normal; 
        Vec reflect_direction = reflect(-light_direction, normal);
        double reflect_dot_eye = dot(reflect_direction, eye);

        if (reflect_dot_eye <= 0) { 
            specular = Color(0, 0, 0);
        } else { 
            double factor = pow(reflect_dot_eye, mat.shininess);
            specular = light.m_intensity * mat.specular * factor; 
        }
    }
    return ambient + diffuse + specular; 
}
