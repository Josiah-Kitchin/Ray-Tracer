

#include "scene/camera.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <execution>

using scene::Camera;

void Camera::init() {
    // Initialzes half_width, half_height and pixel size after object
    // initalization so that camera values can be set with the method chain
    // pattern

    double half_view = std::tan(m_field_of_view / 2);
    double aspect = double(m_horizontal_pixels) / double(m_vertical_pixels);

    if (aspect >= 1) {
        m_half_width = half_view;
        m_half_height = half_view / aspect;
    } else {
        m_half_width = half_view * aspect;
        m_half_height = half_view;
    }
    m_pixel_size = (m_half_width * 2) / m_horizontal_pixels;
    m_transformed_origin = m_inverse_transformation * geo::Point(0, 0, 0);
}

geo::Ray Camera::ray_to_pixel(double pixel_x, double pixel_y) const {
    // Offset from edge of the canvas to the pixels center
    double x_offset = (pixel_x + 0.5) * m_pixel_size;
    double y_offset = (pixel_y + 0.5) * m_pixel_size;

    double world_x = m_half_width - x_offset;
    double world_y = m_half_height - y_offset;

    // The ray is transformed based on transformations made on the camera
    geo::Point pixel = m_inverse_transformation * geo::Point(world_x, world_y, -1);

    geo::Vec direction = unit_vector(pixel - m_transformed_origin);

    return geo::Ray(m_transformed_origin, direction);
}

color::RGB Camera::anti_alias(double pixel_x, double pixel_y, scene::World &world) const {
    // Send 9 different rays around the pixel and average the color to get the
    // final color. Used to make edges less abrupt

    constexpr int jitter_matrix_size = 8;
    std::array<double, jitter_matrix_size> jitter_matrix = {// Offsets for each pixel
                                                            -0.25, 0.25,  0.25, -0.25,
                                                            -0.75, -0.75, 0.75, 0.75};
    // Color at the exact point
    geo::Ray init_ray = ray_to_pixel(pixel_x, pixel_y);
    color::RGB pixel_color = world.color_at(init_ray, world.reflection_limit);

    for (int sample = 0; sample < jitter_matrix_size / 2; ++sample) {
        // Colors at the jittered points
        double jittered_x = pixel_x + jitter_matrix.at(2 * sample);
        double jittered_y = pixel_y + jitter_matrix.at(2 * sample + 1);
        geo::Ray ray = ray_to_pixel(jittered_x, jittered_y);
        pixel_color += world.color_at(ray, world.reflection_limit);
    }
    // Average color;
    pixel_color /= ((double(jitter_matrix_size) / 2) + 1);
    return pixel_color;
}

/* ----------------- Interface Methods ---------------- */

image::Canvas Camera::render(scene::World &world) {
    /* Called by the user to render a world of lights and objects
       Iterators are used to create a multithreaded for loop */

    init(); // Calculate some neccessary variables

    image::Canvas image(m_horizontal_pixels, m_vertical_pixels);

    auto start = std::chrono::high_resolution_clock::now();

    std::clog << " Rendering...            \r";

    /* -------------- Render Loop -------------- */
    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < m_vertical_pixels; ++y) {
        for (int x = 0; x < m_horizontal_pixels; ++x) {
            color::RGB pixel_color = anti_alias(x, y, world);
            image.insert_color(pixel_color, x, y);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::clog << "\rImage Complete\nTime to render: " << duration.count() << '\n';
    /*-------------------------------------------*/

    return image;
}

Camera &Camera::set_horizontal_pixels(int pixels) {
    m_horizontal_pixels = pixels;
    return *this;
}

Camera &Camera::set_vertical_pixels(int pixels) {
    m_vertical_pixels = pixels;
    return *this;
}

Camera &Camera::set_field_of_view(double degrees) {
    m_field_of_view = degrees;
    return *this;
}

Camera &Camera::transform(const xform::Matrix<4> &new_transformation) {
    m_transformation = m_transformation * new_transformation;
    m_inverse_transformation = xform::inverse(m_transformation);
    return *this;
}
