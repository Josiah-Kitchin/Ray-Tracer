

/*
Ray tracing project by Josiah Kitchin, a computer science student at the University of Oregon 
Guided by the Ray Tracer Challenge book by INSERT CREDIT HERE 


*/

#include <iostream> 
#include "tuples.hpp" 
#include "canvas.hpp" 
#include "matrices.hpp"
#include "hittable.hpp"


int main() { 
    Point ray_origin(0, 0, -5);
    double wall_z = 10; 
    double wall_size = 7; 
    double canvas_pixels = 100; 
    double pixel_size = wall_size / canvas_pixels;  
    double half = wall_size / 2; 

    Canvas canvas(canvas_pixels, canvas_pixels); 
    Color red(1, 0, 0);
    Color black(0, 0, 0);
    Sphere sphere; 
    sphere.transform(scaling(1, 0.5, 1) * rotation_z(M_PI / 4) * scaling(3, 1, 1));

    for (double y = 0; y < canvas_pixels; y++) { 
        double world_y = half - pixel_size * y; 

        for (double x = 0; x < canvas_pixels; x++) { 
            double world_x = -half + pixel_size * x; 
            Point position(world_x, world_y, wall_z); 

            Ray ray(ray_origin, unit_vector(position - ray_origin));
            std::vector<Intersection> intersections = sphere.intersect(ray);

            if (!intersections.empty()) { 
                canvas.insert_color(red, x, y);
            } else { 
                canvas.insert_color(black, x, y);
            }
        }
    }
    canvas.write_to_ppm(); 

    return 0; 
}

    