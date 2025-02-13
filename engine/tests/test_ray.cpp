

#include "geo/ray.hpp"
#include <gtest/gtest.h>

using namespace geo;
using namespace xform;

TEST(Ray, constructor) {
    Ray ray(Point(0, 0, 0), Vec(1, 2, 3));
    ASSERT_EQ(Point(0, 0, 0), ray.origin);
    ASSERT_EQ(Vec(1, 2, 3), ray.direction);
}

TEST(Ray, at) {
    Ray ray(Point(2, 3, 4), Vec(1, 0, 0));
    ASSERT_EQ(Point(2, 3, 4), ray.at(0));
    ASSERT_EQ(Point(3, 3, 4), ray.at(1));
    ASSERT_EQ(Point(1, 3, 4), ray.at(-1));
    ASSERT_EQ(Point(4.5, 3, 4), ray.at(2.5));
}

TEST(Ray, transform) {
    Ray ray(Point(1, 2, 3), Vec(0, 1, 0));
    Matrix matrix = translation(3, 4, 5);
    Ray ray_transformed = transform_ray(ray, matrix);
    ASSERT_EQ(ray_transformed.origin, Point(4, 6, 8));
    ASSERT_EQ(ray_transformed.direction, Vec(0, 1, 0));
}

TEST(Ray, transform2) {
    Ray ray(Point(1, 2, 3), Vec(0, 1, 0));
    Matrix matrix = scaling(2, 3, 4);
    Ray ray_transformed = transform_ray(ray, matrix);
    ASSERT_EQ(ray_transformed.origin, Point(2, 6, 12));
    ASSERT_EQ(ray_transformed.direction, Vec(0, 3, 0));
}
