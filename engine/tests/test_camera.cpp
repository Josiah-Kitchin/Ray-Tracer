

#define private public
#include "scene/camera.hpp"
#undef private

#include <gtest/gtest.h> 
#include <cmath> 
#include "utils.hpp"

using namespace scene; 
using namespace geo; 

TEST(Camera, pixel_size) { 
    Camera camera; 
    camera
        .set_field_of_view(M_PI/2)
        .set_horizontal_pixels(200)
        .set_vertical_pixels(125);

    camera.init();

    ASSERT_TRUE(utils::compare_doubles(camera.m_pixel_size, 0.01));
}

TEST(Camera, pixel_size2) { 
    Camera camera; 
    camera 
        .set_field_of_view(M_PI/2)
        .set_horizontal_pixels(200)
        .set_vertical_pixels(125);

    camera.init();

    ASSERT_TRUE(utils::compare_doubles(camera.m_pixel_size, 0.01));
}

TEST(Camera, ray_to_pixel) { 
    Camera camera; 
    camera
        .set_field_of_view(M_PI/2)
        .set_horizontal_pixels(201)
        .set_vertical_pixels(101);

    camera.init();

    Ray expected(Point(0, 0, 0), Vec(0, 0, -1));
    Ray actual = camera.ray_to_pixel(100, 50);
    ASSERT_EQ(actual.origin, expected.origin);
    ASSERT_EQ(actual.direction, expected.direction);
}

TEST(Camera, ray_to_pixel2) { 
    Camera camera; 
    camera
        .set_field_of_view(M_PI/2)
        .set_horizontal_pixels(201)
        .set_vertical_pixels(101);

    camera.init();

    Ray expected(Point(0, 0, 0), Vec(0.66519, 0.33259, -0.66851));
    Ray actual = camera.ray_to_pixel(0, 0);
    ASSERT_EQ(actual.origin, expected.origin);
    ASSERT_EQ(actual.direction, expected.direction);
}

