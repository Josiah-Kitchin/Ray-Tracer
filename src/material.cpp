
#include "material.hpp"

Material::Material() : color(Color(0, 0, 0)), ambient(0), diffuse(0), specular(0), shininess(0) {}


Color lighting(const Material& mat, const Light& light, const Point& position, const Vec& eye, const Vec& normal) { 
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