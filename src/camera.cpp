

#include "camera.hpp"
#include <cmath> 



void Camera::init() { 
    //Initialzes half_width, half_height and pixel size after object initalization 
    //so that camera values can be set with the method chain pattern 

    double half_view = std::tan(field_of_view / 2);
    double aspect = double(horizontal_pixels) / double(vertical_pixels);

    if (aspect >= 1) { 
        half_width = half_view;  
        half_height = half_view / aspect; 
    } else { 
        half_width = half_view * aspect; 
        half_height = half_view; 
    }
    pixel_size = (half_width * 2) / horizontal_pixels;
}


Ray Camera::ray_to_pixel(int pixel_x, int pixel_y) const { 
    //Offset from edge of the canvas to the pixels center
    double x_offset = (double(pixel_x) + 0.5) * pixel_size; 
    double y_offset = (double(pixel_y) + 0.5) * pixel_size; 

    double world_x = half_width - x_offset; 
    double world_y = half_height - y_offset; 

    Point pixel = inverse(transformation) * Point(world_x, world_y, -1);
    Point origin = inverse(transformation) * Point(0, 0, 0);
    Vec direction = unit_vector(pixel - origin);

    return Ray(origin, direction);
}

void log_line(int current_line, int total) { 
	std::clog << "\rScanlines remaining: " << (total - current_line) << ' ' << std::flush; 
}

Canvas Camera::render(World& world) { 
    init();

    Canvas image(horizontal_pixels, vertical_pixels);
    for (int y = 0; y < vertical_pixels; ++y) { 
        log_line(y, vertical_pixels);
        for (int x = 0; x < horizontal_pixels; ++x) {
            Ray ray = ray_to_pixel(x, y);
            Color pixel_color = world.color_at(ray);
            image.insert_color(pixel_color, x, y);
        }
    }
    return image; 
}

/* ----------- Interface Methods ------------- */

Camera& Camera::set_horizontal_pixels(int pixels) { 
    horizontal_pixels = pixels; 
    return *this;
}
Camera& Camera::set_vertical_pixels(int pixels) { 
    vertical_pixels = pixels; 
    return *this;
}
Camera& Camera::set_field_of_view(double degrees) { 
    field_of_view = degrees; 
    return *this;
}

Camera& Camera::transform(const Matrix& new_transformation) { 
    transformation = transformation * new_transformation;
    return *this;
}

