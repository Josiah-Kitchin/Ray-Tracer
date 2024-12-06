

/*
Ray tracing project by Josiah Kitchin, a computer science student at the University of Oregon 
Guided by the Ray Tracer Challenge book by INSERT CREDIT HERE 


*/

#include <iostream> 
#include "tuples.hpp" 
#include "canvas.hpp" 
#include "matrices.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "light.hpp"

int main() { 
    Point ray_origin(0, 0, -5);
    double wall_z = 10; 
    double wall_size = 7; 
    double canvas_pixels = 400; 
    double pixel_size = wall_size / canvas_pixels;  
    double half = wall_size / 2; 

    Canvas canvas(canvas_pixels, canvas_pixels); 
    Color black(0, 0, 0);
    Sphere sphere; 
    sphere.material.color = Color(1, 0.2, 1); 
    sphere.material.ambient = 0.05;
    sphere.material.diffuse = 0.9 * (sqrt(2)/2);;
    sphere.material.specular = 1;

    Light light(Color(1, 1, 1), Point(-10, 10, -10));

    for (double y = 0; y < canvas_pixels; y++) { 
        double world_y = half - pixel_size * y; 
	    std::clog << "\rScanlines remaining: " << (canvas_pixels - y) << ' ' << std::flush; 

        for (double x = 0; x < canvas_pixels; x++) { 
            double world_x = -half + pixel_size * x; 
            Point position(world_x, world_y, wall_z); 

            Ray ray(ray_origin, unit_vector(position - ray_origin));
            std::vector<Intersection> intersections = sphere.intersect(ray);

            if (!intersections.empty()) { 
                //hardcoding this to spheres for now until i get the abstract hittable class to work. 
                Intersection closest_intersection = intersections.at(0); 
                Point hit_point = ray.at(closest_intersection.t);
                Color color = lighting(sphere.material, light, hit_point, -ray.direction, sphere.normal_at(hit_point));
                canvas.insert_color(color, x, y);
            } else { 
                canvas.insert_color(black, x, y);
            }
        }
    }
    canvas.write_to_ppm(); 

    return 0; 
}

    