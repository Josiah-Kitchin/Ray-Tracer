

#include <gtest/gtest.h> 
#include "scene/hittable.hpp"
#include "geo/ray.hpp"

using namespace scene; 
using namespace geo; 
using namespace xform;

TEST(Sphere, intersect) { 
    Ray ray(Point(0, 0, -5), Vec(0, 0, 1));
    Sphere sphere; 
    std::vector<Intersection> hit_list = sphere.intersect(ray); 
    std::vector<Intersection> expected = {Intersection(4.0, &sphere), Intersection(6.0, &sphere)}; 
    ASSERT_EQ(hit_list, expected);
}

TEST(Sphere, intersect2) { 
    Ray ray(Point(0, 1, -5), Vec(0, 0, 1));
    Sphere sphere; 
    std::vector<Intersection> hit_list = sphere.intersect(ray); 
    std::vector<Intersection> expected = {Intersection(5.0, &sphere)}; 
    ASSERT_EQ(hit_list, expected); 
}

TEST(Sphere, intersect3) { 
    Ray ray(Point(0, 2, -5), Vec(0, 0, 1)); 
    Sphere sphere; 
    std::vector<Intersection> hit_list = sphere.intersect(ray); 
    std::vector<Intersection> expected = {}; 
    ASSERT_EQ(hit_list, expected); 
}

TEST(Sphere, intersect4) { 
    Ray ray(Point(0, 0, 0), Vec(0, 0, 1)); 
    Sphere sphere; 
    std::vector<Intersection> hit_list = sphere.intersect(ray); 
    std::vector<Intersection> expected = {Intersection(-1.0, &sphere), Intersection(1.0, &sphere)};
    ASSERT_EQ(hit_list, expected); 
}

TEST(Sphere, intersect5) { 
    Ray ray(Point(0, 0, 5), Vec(0, 0, 1)); 
    Sphere sphere; 
    std::vector<Intersection> hit_list = sphere.intersect(ray); 
    std::vector<Intersection> expected = {Intersection(-6.0 ,&sphere), Intersection(-4.0, &sphere)}; 
    ASSERT_EQ(hit_list, expected); 
}

TEST(Sphere, normal_at) { 
    Sphere sphere; 
    ASSERT_EQ(Vec(1, 0, 0), sphere.normal_at(Point(1, 0, 0)));
    ASSERT_EQ(Vec(0, 1, 0), sphere.normal_at(Point(0, 1, 0)));
    ASSERT_EQ(Vec(0, 0, 1), sphere.normal_at(Point(0, 0, 1)));
    ASSERT_EQ(Vec(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3), sphere.normal_at(Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3)));
}

TEST(Sphere, normal_at2){ 
    Sphere sphere; 
    sphere.transform(translation(0, 1, 0));
    ASSERT_EQ(Vec(0, 0.70711, -0.70711), sphere.normal_at(Point(0, 1.70711, -0.70711)));
}

TEST(Sphere, normal_at3){ 
    Sphere sphere; 
    sphere.transform(scaling(1, 0.5, 1) * rotation_z(M_PI/5));
    ASSERT_EQ(Vec(0, 0.97014, -0.24254), sphere.normal_at(Point(0, sqrt(2)/2, -sqrt(2)/2)));
}
