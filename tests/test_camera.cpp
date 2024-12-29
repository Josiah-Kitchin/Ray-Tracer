
#include <gtest/gtest.h> 
#include "scene/camera.hpp"
#include <cmath> 
#include "utils.hpp"

using namespace scene; 
using namespace geo; 

TEST(Camera, pixel_size) { 
    Camera camera(200, 125, M_PI/2); 

    ASSERT_TRUE(compare_doubles(camera.pixel_size, 0.01));
}

TEST(Camera, pixel_size2) { 
    Camera camera(125, 200, M_PI/2); 

    ASSERT_TRUE(compare_doubles(camera.pixel_size, 0.01));
}

TEST(Camera, ray_to_pixel) { 
    Camera camera(201, 101, M_PI/2); 
    Ray expected(Point(0, 0, 0), Vec(0, 0, -1));
    Ray actual = camera.ray_to_pixel(100, 50);
    ASSERT_EQ(actual.origin, expected.origin);
    ASSERT_EQ(actual.direction, expected.direction);
}

TEST(Camera, ray_to_pixel2) { 
    Camera camera(201, 101, M_PI/2);
    Ray expected(Point(0, 0, 0), Vec(0.66519, 0.33259, -0.66851));
    Ray actual = camera.ray_to_pixel(0, 0);
    ASSERT_EQ(actual.origin, expected.origin);
    ASSERT_EQ(actual.direction, expected.direction);
}

