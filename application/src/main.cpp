

#include <cmath> 
#include "geo/geo.hpp"
#include "xform/xform.hpp"
#include "scene/scene.hpp"
#include "color/color.hpp"
#include <SFML/Graphics.hpp> 

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
        .set_diffuse(0.4)
        .set_specular(0.8)
        .set_transparency(1)
        .set_color(color::red())
        .set_refractive_index(2);
        
    color::Stripes stripes; 
    stripes
        .set_first_color(color::red())
        .set_second_color(color::green())
        .transform(xform::scaling(0.3, 0.3, 0.3));

    scene::Sphere right_sphere; 
    right_sphere
        .transform(xform::translation(1.5, 1, -0.5))
        .transform(xform::scaling(0.5, 0.5, 0.5))
        .set_material(sphere_mat)
        .set_pattern(&stripes);

    color::Gradient gradient; 
    gradient
        .set_first_color(color::red())
        .set_second_color(color::blue())
        .transform(xform::scaling(1.2, 1.2, 1.2));

    


    /* -------------- Plane -------------- */

    color::Checkers checkers; 
    checkers
        .set_first_color(color::white())
        .set_second_color(color::black());

    scene::Plane floor;
    floor 
        .set_diffuse(0.8)
        .set_ambient(0.2)
        .set_pattern(&checkers);



        
    /* --------- Cube ---------- */
    scene::Cube cube; 
    cube
        .transform(xform::translation(-1.5, 0.33, -0.5))
        .transform(xform::scaling(0.33, 0.33, 0.33))
        .set_material(sphere_mat)
        .set_pattern(&gradient);

    /* ------------- Light --------------- */

    scene::Light light; 
    light 
        .set_intensity(color::white())
        .set_position(geo::Point(-10, 10, -10));


    /* ------------- Scene --------------*/
    int horizontal_pixels = 2000; 
    int vertical_pixels = 1000; 

    scene::Camera camera; 
    camera
        .set_horizontal_pixels(horizontal_pixels)
        .set_vertical_pixels(vertical_pixels)
        .set_field_of_view(M_PI/3)
        .transform(xform::view_transform(geo::Point(0, 1, -5), geo::Point(0, 1, 0), geo::Vec(0, 1, 0)));

    scene::World world;
    world
        .set_lights({light})
        .set_objects({&floor, &middle_sphere, &right_sphere, &cube})
        .set_reflection_limit(50);
    
    image::Canvas canvas = camera.render(world);

    std::vector<uint8_t> frame_buffer = canvas.write_to_frame_buffer(); 

    sf::Image image; 
    image.create(horizontal_pixels, vertical_pixels, frame_buffer.data());

    sf::Texture texture; 
    texture.loadFromImage(image);

    sf::Sprite sprite(texture);
    sf::RenderWindow window(sf::VideoMode(horizontal_pixels, vertical_pixels), "Ray Tracer Output");

    while (window.isOpen()) 
    { 
        sf::Event event; 
        while (window.pollEvent(event)) 
        { 
            if (event.type == sf::Event::Closed) 
                window.close(); 
        }
        window.clear(); 
        window.draw(sprite);
        window.display(); 
    }


    return 0; 
}

    
