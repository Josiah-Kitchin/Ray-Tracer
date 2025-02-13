

#include "build_scene.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::clog << "Usage: ./ray scene.json";
    }
    image::Canvas canvas = build_scene(argv[1]);

    std::ofstream file("image.ppm");
    if (file.is_open()) {
        canvas.write_to_ppm(file);
    } else {
        std::cerr << "Error writing to ppm\n";
    }

    return 0;
}
