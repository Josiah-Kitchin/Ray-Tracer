
#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "color/color.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

namespace image {

class Canvas {
    /* Holds a matrix of colors, used to generate the image */

  public:
    Canvas(int, int);

    color::RGB &pixel_at(int, int);
    void insert_color(color::RGB, int, int);
    // Write a ppm file to standard output
    void write_to_ppm(std::ostream &);
    // Return a frame buffer of r, g, b, a, used for displaying the image in a
    // window
    std::vector<uint8_t> write_to_frame_buffer();

  private:
    std::vector<color::RGB> color_matrix;
    int m_width;
    int m_height;
};

} // namespace image

#endif
