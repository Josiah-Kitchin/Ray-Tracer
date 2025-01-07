
#include <gtest/gtest.h> 

#define private public
#include "scene/world.hpp"
#undef private 

#include "scene/hittable.hpp"
#include "geo/tuples.hpp"
#include "geo/ray.hpp"
#include "geo/intersection.hpp"
#include "color/color.hpp"
#include "utils.hpp"

using namespace scene; 
using namespace xform; 
using namespace color; 
using namespace geo; 

TEST(World, init) {
    Sphere sphere; 
    sphere.material.color = RGB(0.8, 1, 0.6);
    sphere.material.diffuse = 0.8; 
    sphere.material.specular = 0.2; 

    Sphere sphere2; 
    sphere2.transform(scaling(0.5, 0.5, 0.5));

    World world; 
    world.m_objects = {&sphere, &sphere2};

    ASSERT_TRUE(world.m_objects.at(0)->material.color == RGB(0.8, 1, 0.6));
}

TEST(World, intersects) {
    Sphere sphere; 
    sphere.material.color = RGB(0.8, 1, 0.6);
    sphere.material.diffuse = 0.8; 
    sphere.material.specular = 0.2; 

    Sphere sphere2; 
    sphere2.transform(scaling(0.5, 0.5, 0.5));

    World world; 
    world.m_objects = {&sphere, &sphere2};
    Ray ray(Point(0, 0, -5), Vec(0, 0, 1));

    std::vector<Intersection> intersections = world.intersects(ray);
    ASSERT_EQ(intersections.size(), 4);
    ASSERT_EQ(intersections.at(0).t, 4);
    ASSERT_EQ(intersections.at(1).t, 4.5);
    ASSERT_EQ(intersections.at(2).t, 5.5);
    ASSERT_EQ(intersections.at(3).t, 6);

}

TEST(World, shade_hit) { 
    World world; 
    Ray r(Point(0, 0, -5), Vec(0, 0, 1));
    Sphere shape; 
    shape.material.ambient = 1; 
    shape.material.diffuse = 1; 
    shape.material.specular = 1; 
    world.m_objects = {&shape};
    Intersection i(4, &shape);
    std::vector<Intersection> intersections{i};
    IntersectionState state(0, intersections, r); 
    RGB shade = world.shade_hit(state, 10);
    ASSERT_EQ(shade, RGB(0.536895, 0.536895, 0.536895));
}

TEST(World, shade_hit2) {
    World world; 
    world.m_lights = {Light(RGB(1, 1, 1), Point(0, 0.25, 0))};
    Ray r(Point(0, 0, 0), Vec(0, 0, 1));
    Sphere shape; 
    shape.material.ambient = 1; 
    shape.material.diffuse = 1;
    shape.material.specular = 1; 
    Intersection i(0.5, &shape);
    std::vector<Intersection> intersections{i};
    IntersectionState state(0, intersections, r);
    RGB shade = world.shade_hit(state, 10);
    ASSERT_EQ(shade, RGB(0.894427, 0.894427, 0.894427));
}

TEST(World, shade_hit3) { 
    World world; 
    world.m_lights = {Light(RGB(1, 1, 1), Point(0, 0, -10))};

    Sphere s1; 
    Sphere s2; 
    s2.transform(xform::translation(0, 0, 10));
    world.m_objects = {&s1, &s2};
    Ray r(Point(0, 0, 5), Vec(0, 0, 1));
    Intersection i(4, &s2);
    std::vector<Intersection> intersections{i};
    IntersectionState state(0, intersections, r);
    color::RGB c = world.shade_hit(state, 10);
    ASSERT_EQ(c, color::RGB(0.1, 0.1, 0.1));
}


TEST(World, color_at) { 
    World world; 
    Ray ray(Point(0, 0, -5), Vec(0, 1, 0));
    RGB color = world.color_at(ray, 10);
    ASSERT_EQ(color, RGB(0, 0, 0)); 
}

TEST(World, is_shadowed) { 
    World world;
    Sphere sphere; 
    world.add_object(&sphere);
    Point point(0, 0, 0);
    ASSERT_FALSE(world.is_shadowed(point));
}

TEST(World, is_shadowed2) { 
    World world; 
    Sphere sphere; 
    world.add_object(&sphere);
    Point point(10, -10, 10);
    ASSERT_TRUE(world.is_shadowed(point));
}

TEST(World, is_shadowed3) { 
    World world;
    Sphere sphere; 
    world.add_object(&sphere);
    Point point(-20, 20, -20);
    ASSERT_FALSE(world.is_shadowed(point));
}

TEST(World, is_shadowed4) {
    World world;
    Sphere sphere; 
    world.add_object(&sphere);
    Point point(-2, 2, -2);
    ASSERT_FALSE(world.is_shadowed(point));
}

TEST(World, reflect_color) { 
    World world; 
    Plane plane; 
    plane
        .set_color(color::RGB(1, 1, 1))
        .set_ambient(1)
        .set_reflective(0.5)
        .transform(xform::translation(0, -1, 0));

    world.add_object(&plane);
    geo::Ray r(geo::Point(0, 0, -3), geo::Vec(0, -sqrt(2)/2, sqrt(2)/2));
    geo::Intersection i(sqrt(2), &plane);
    std::vector<Intersection> intersections{i};
    geo::IntersectionState state(0, intersections, r);
    color::RGB c = world.reflect_color(state, 10);
    ASSERT_EQ(c, color::RGB(0.19032, 0.2379, 0.14274));
}










