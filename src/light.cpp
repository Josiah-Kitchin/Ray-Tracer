
#include "light.hpp"


Light::Light(const Color& intensity, const Point& position) : intensity(intensity), position(position) {}
Light::Light() : intensity(Color()), position(Point()) {}

Light& Light::set_intensity(const Color& in_intensity) { 
    intensity = in_intensity; 
    return *this; 
}

Light& Light::set_position(const Point& in_position) { 
    position = in_position; 
    return *this; 
}

Color calculate_lighting(const Material& mat, const Light& light, const Point& position, const Vec& eye, const Vec& normal) { 
    /* Phong Reflection Model */

    Color ambient, diffuse, specular; 

    Color effective_color = mat.color * light.intensity; 

    Vec light_direction = unit_vector(light.position - position);

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
            specular = light.intensity * mat.specular * factor; 
        }
    }
    return ambient + diffuse + specular; 
}
