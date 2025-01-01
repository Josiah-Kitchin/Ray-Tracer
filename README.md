# Ray Tracer
Author: Josiah Kitchin, Computer Science Student at the University of Oregon

A 3D ray tracer inspired by *[The Ray Tracer Challenge](https://www.oreilly.com/library/view/the-ray-tracer/9781680506778/)* by Jamis Buck. This project is a work in progress, aiming to build a 3D renderer using ray tracing techniques.



(12/27/2024) 1000 x 500, 0.7 Seconds to render 
![My Image](images/spheres.png)




## Features
- Ray tracing-based 3D rendering
- Multithreaded 
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
[Main](src/main.cpp)


See [Docs](docs) for more information on how to use the ray tracer





