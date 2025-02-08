

#include "build_scene.hpp"

int main(int argc, char** argv)
{ 
    if (argc != 2)
    {
        std::clog << "Usage: ./ray <scene.json> > output_file";
    }
    image::Canvas canvas = build_scene(argv[1]);
    canvas.write_to_ppm(); 

    return 0; 
}

    
