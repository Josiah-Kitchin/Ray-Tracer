
#include "gtest/gtest.h"

#define private public
#include "scene/hittable.hpp"
#undef private



TEST(plane, intersect) { 
    scene::Plane plane;
    geo::Ray ray(geo::Point(0, 10, 0), geo::Vec(0, 0, 1));
    std::vector<geo::Intersection> intersections = plane.intersect(ray);
    ASSERT_TRUE(intersections.empty());
}
TEST(plane, intersect2) { 
    scene::Plane plane;
    geo::Ray ray(geo::Point(0, 0, 0), geo::Vec(0, 0, 1));
    auto intersections = plane.intersect(ray);
    ASSERT_TRUE(intersections.empty());
}

TEST(plane, intersect3) { 
    scene::Plane plane;
    geo::Ray ray(geo::Point(0, 1, 0), geo::Vec(0, -1, 0));
    auto intersections = plane.intersect(ray);
    ASSERT_EQ(intersections.size(), 1);
    ASSERT_EQ(intersections.at(0).t, 1);
    ASSERT_EQ(intersections.at(0).object, &plane);
}

TEST(plane, intersect4) { 
    scene::Plane plane;
    geo::Ray ray(geo::Point(0, -1, 0), geo::Vec(0, 1, 0));
    auto intersections = plane.intersect(ray);
    ASSERT_EQ(intersections.size(), 1);
    ASSERT_EQ(intersections.at(0).t, 1);
    ASSERT_EQ(intersections.at(0).object, &plane);
}
