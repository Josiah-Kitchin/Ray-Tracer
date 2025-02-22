

#include "image/canvas.hpp"

using image::Canvas;
/* The canvas class holds a matrix of colors with methods to write the colors to
 * an image format output*/

Canvas::Canvas(int width, int height) : m_width(width), m_height(height) {
    color_matrix.resize(height * width, color::white());
}

color::RGB &Canvas::pixel_at(int line, int color_idx) {
    return color_matrix.at(line * m_width + color_idx);
}

void Canvas::insert_color(color::RGB color, int color_idx, int line) {
    color_matrix.at(line * m_width + color_idx) = color;
}

void Canvas::write_to_ppm(std::ostream &out) {
    out << "P3\n" << m_width << ' ' << m_height << "\n255\n";
    for (int line = 0; line < m_height; line++) {
        for (int pixel = 0; pixel < m_width; pixel++) {
            color::RGB color = pixel_at(line, pixel);
            color.convert_to_256();
            out << color.r << ' ' << color.g << ' ' << color.b << '\n';
        }
    }
}

