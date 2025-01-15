

#include <cmath> 
#include "geo/geo.hpp"
#include "xform/xform.hpp"
#include "scene/scene.hpp"
#include "color/color.hpp"

int main() { 



    /* ----------- Spheres ------------*/


    scene::Material sphere_mat; 
    sphere_mat
        .set_ambient(0.3)
        .set_diffuse(0.7)
        .set_specular(0.3);

    scene::Sphere middle_sphere; 
    middle_sphere
        .transform(xform::translation(-0.5, 1, 1.8))
        .set_ambient(0.3)
        .set_diffuse(0.7)
        .set_specular(0.3)
        .set_transparency(0.9)
        .set_refractive_index(1.5);
        

    scene::Sphere right_sphere; 
    right_sphere
        .transform(xform::translation(-0.5, 0.5, 8))
        .transform(xform::scaling(0.5, 0.5, 0.5))
        .set_material(sphere_mat)
        .set_color(color::red());

    scene::Sphere left_sphere; 
    left_sphere
        .transform(xform::translation(-1.5, 0.33, -0.5))
        .transform(xform::scaling(0.33, 0.33, 0.33))
        .set_material(sphere_mat)
        .set_color(color::green());
    scene::Sphere sphere; 

    /* -------------- Plane -------------- */

    scene::Plane floor;
    floor 
        .set_diffuse(0.8)
        .set_ambient(0.2)
        .set_color(color::RGB(0.5, 0.5, 0.5));


    color::Checkers checkers; 
    checkers
        .set_first_color(color::black())
        .set_second_color(color::white());

    

        
    /* ------------- Light --------------- */

    scene::Light light; 
    light 
        .set_intensity(color::white())
        .set_position(geo::Point(-10, 10, -10));

    /* ------------- Scene --------------*/

    scene::Camera camera; 
    camera
        .set_horizontal_pixels(2000)
        .set_vertical_pixels(1000)
        .set_field_of_view(M_PI/3)
        .transform(xform::view_transform(geo::Point(0, 1.5, -5), geo::Point(0, 1, 0), geo::Vec(0, 1, 0)));

    scene::World world;
    world
        .set_lights({light})
        .set_objects({&floor, &middle_sphere, &right_sphere, &left_sphere})
        .set_reflection_limit(10);
    
    image::Canvas image = camera.render(world);

    image.write_to_ppm();

    return 0; 
}

    
