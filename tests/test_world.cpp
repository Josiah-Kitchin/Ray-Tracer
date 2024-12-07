
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


