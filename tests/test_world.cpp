
#include <gtest/gtest.h> 
#include "world.hpp"
#include "hittable.hpp"
#include "tuples.hpp"
#include "ray.hpp"
#include "intersection.hpp"

TEST(World, init) {
    Sphere sphere; 
    sphere.material.color = Color(0.8, 1, 0.6);
    sphere.material.diffuse = 0.8; 
    sphere.material.specular = 0.2; 

    Sphere sphere2; 
    sphere2.transform(scaling(0.5, 0.5, 0.5));

    World world; 
    world.objects = {&sphere, &sphere2};

    ASSERT_TRUE(world.objects.at(0)->material.color == Color(0.8, 1, 0.6));
}

TEST(World, intersects) {
    Sphere sphere; 
    sphere.material.color = Color(0.8, 1, 0.6);
    sphere.material.diffuse = 0.8; 
    sphere.material.specular = 0.2; 

    Sphere sphere2; 
    sphere2.transform(scaling(0.5, 0.5, 0.5));

    World world; 
    world.objects = {&sphere, &sphere2};
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
    world.objects = {&shape};
    Intersection i(4, &shape);
    IntersectionState state(i, r); 
    Color shade = world.shade_hit(state);
    ASSERT_EQ(shade, Color(0.536895, 0.536895, 0.536895));
}

TEST(World, shade_hit2) {
    World world; 
    world.lights = {Light(Color(1, 1, 1), Point(0, 0.25, 0))};
    Ray r(Point(0, 0, 0), Vec(0, 0, 1));
    Sphere shape; 
    shape.material.ambient = 1; 
    shape.material.diffuse = 1;
    shape.material.specular = 1; 
    Intersection i(0.5, &shape);
    IntersectionState state(i, r);
    Color shade = world.shade_hit(state);
    ASSERT_EQ(shade, Color(0.894427, 0.894427, 0.894427));
}

TEST(World, color_at) { 
    World world; 
    Ray ray(Point(0, 0, -5), Vec(0, 1, 0));
    Color color = world.color_at(ray);
    ASSERT_EQ(color, Color(0, 0, 0)); 
}







