

#include <iostream> 
#include <cmath> 

#include "scene/scene.hpp"
#include "geo/geo.hpp"
#include "xform/xform.hpp"

int main() { 

    scene::Material background_mat; 
    background_mat
        .set_color(color::RGB(1, 0.9, 0.9))
        .set_specular(0);

    scene::Sphere floor; 
    floor 
        .transform(xform::scaling(10, 0.01, 10))
        .set_material(background_mat);

    scene::Sphere left_wall; 
    left_wall 
        .transform(xform::translation(0, 0, 5))
        .transform(xform::rotation_y(-M_PI/4))
        .transform(xform::rotation_x(M_PI/2))
        .transform(xform::scaling(10, 0.01, 10))
        .set_material(background_mat);

    scene::Sphere right_wall; 
    right_wall
        .transform(xform::translation(0, 0, 5))
        .transform(xform::rotation_y(M_PI/4))
        .transform(xform::rotation_x(M_PI/2))
        .transform(xform::scaling(10, 0.01, 10))
        .set_material(background_mat);


    scene::Material sphere_mat; 
    sphere_mat
        .set_diffuse(0.7)
        .set_specular(0.3);

    scene::Sphere middle_sphere; 
    middle_sphere
        .transform(xform::translation(-0.5, 1, 0.8))
        .set_material(sphere_mat)
        .set_color(color::RGB(0.1, 1, 0.5));

    scene::Sphere right_sphere; 
    right_sphere
        .transform(xform::translation(1.5, 0.5, -0.5))
        .transform(xform::scaling(0.5, 0.5, 0.5))
        .set_material(sphere_mat)
        .set_color(color::RGB(0.5, 1, 0.1));

    scene::Sphere left_sphere; 
    left_sphere
        .transform(xform::translation(-1.5, 0.33, -0.75))
        .transform(xform::scaling(0.33, 0.33, 0.33))
        .set_material(sphere_mat)
        .set_color(color::RGB(1, 0.8, 1));

    
    scene::Light light; 
    light 
        .set_intensity(color::RGB(1, 1, 1))
        .set_position(geo::Point(-10, 10, -10));

    scene::Camera camera; 
    camera
        .set_horizontal_pixels(1000)
        .set_vertical_pixels(500)
        .set_field_of_view(M_PI/3)
        .transform(xform::view_transform(geo::Point(0, 1.5, -5), geo::Point(0, 1, 0), geo::Vec(0, 1, 0)));

    //test
    scene::World world;
    world
        .set_lights({light})
        .set_objects({&floor, &left_wall, &right_wall, &middle_sphere, &right_sphere, &left_sphere});

    image::Canvas image = camera.render(world);

    image.write_to_ppm();

    return 0; 
}

    