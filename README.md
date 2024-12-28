# Ray Tracer
Author: Josiah Kitchin, Computer Science Student at the University of Oregon

A 3D ray tracer inspired by *[A Ray Tracer Challenge](https://www.oreilly.com/library/view/the-ray-tracer/9781680506778/)* by James Buck. This project is a work in progress, aiming to build a 3D renderer using ray tracing techniques.



(12/27/2024)
![My Image](images/spheres_with_bg.png)




## Features
- Ray tracing-based 3D rendering
- Test-driven development with Google Test
- Built with CMake for easy build configuration

## Dependencies 

- Google Test 



## Build 
```bash
    sudo apt install cmake #install cmake
    git clone https://github.com/Josiah-Kitchin/Ray-Tracer-Challenge #clone the repo 
    cd Ray-Tracer-Challenge 
    cmake -S . -B build #create the make files with cmake 
    cd build
    make #compile the code to create an executable 
    ./ray > image.ppm #run the program and output a ppm file
```


## Test Build
1. Change directory to the tests directory
```bash
    cd Ray-Tracer-Challenge/tests
    git clone https://github.com/google/googletest.git
    cmake -S . -B build #create the make files with cmake 
    cd build
    make #compile the code to create an executable 
    ./ray_test #run the tests 
```

## Example main.cpp
See [Docs](docs) for more information on how to use the ray tracer
```c++
#include <iostream> 
#include <cmath> 

#include "tuples.hpp" 
#include "canvas.hpp" 
#include "hittable.hpp"
#include "material.hpp"
#include "light.hpp"
#include "camera.hpp"

int main() { 

    Material background_mat; 
    background_mat
        .set_color(Color(1, 0.9, 0.9))
        .set_specular(0);

    Sphere floor; 
    floor 
        .transform(scaling(10, 0.01, 10))
        .set_material(background_mat);

    Sphere left_wall; 
    left_wall 
        .transform(translation(0, 0, 5))
        .transform(rotation_y(-M_PI/4))
        .transform(rotation_x(M_PI/2))
        .transform(scaling(10, 0.01, 10))
        .set_material(background_mat);

    Sphere right_wall; 
    right_wall
        .transform(translation(0, 0, 5))
        .transform(rotation_y(M_PI/4))
        .transform(rotation_x(M_PI/2))
        .transform(scaling(10, 0.01, 10))
        .set_material(background_mat);


    Material sphere_mat; 
    sphere_mat
        .set_diffuse(0.7)
        .set_specular(0.3);

    Sphere middle_sphere; 
    middle_sphere
        .transform(translation(-0.5, 1, 0.5))
        .set_material(sphere_mat)
        .set_color(Color(0.1, 1, 0.5));

    Sphere right_sphere; 
    right_sphere
        .transform(translation(1.5, 0.5, -0.5))
        .transform(scaling(0.5, 0.5, 0.5))
        .set_material(sphere_mat)
        .set_color(Color(0.5, 1, 0.1));

    Sphere left_sphere; 
    left_sphere
        .transform(translation(-1.5, 0.33, -0.75))
        .transform(scaling(0.33, 0.33, 0.33))
        .set_material(sphere_mat)
        .set_color(Color(1, 0.8, 1));

    
    Light light; 
    light 
        .set_intensity(Color(1, 1, 1))
        .set_position(Point(-10, 10, -10));

    Camera camera; 
    camera
        .set_horizontal_pixels(1000)
        .set_vertical_pixels(500)
        .set_field_of_view(M_PI/3)
        .transform(view_transform(Point(0, 1.5, -5), Point(0, 1, 0), Vec(0, 1, 0)));

    World world;
    world
        .set_lights({light})
        .set_objects({&floor, &left_wall, &right_wall, &middle_sphere, &right_sphere, &left_sphere});

    Canvas image = camera.render(world);

    image.write_to_ppm();

    return 0; 
}
```




