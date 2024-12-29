
#include <gtest/gtest.h> 
#include "geo/intersection.hpp"
#include "scene/hittable.hpp"

using namespace geo; 
using namespace scene; 
using namespace xform; 

TEST(hit, hit1) { 
    Sphere sphere; 
    std::vector<Intersection> intersections = {Intersection(1, &sphere), Intersection(2, &sphere)};
    Intersection expected(1, &sphere);

    ASSERT_EQ(hit(intersections), expected);
}

TEST(hit, hit2) { 
    Sphere sphere; 
    std::vector<Intersection> intersections = {Intersection(1, &sphere), Intersection(-1, &sphere)};
    Intersection expected(1, &sphere); 

    ASSERT_EQ(hit(intersections), expected);
}

TEST(hit, hit3) { 
    Sphere sphere; 
    std::vector<Intersection> intersections = {Intersection(-2, &sphere), Intersection(-1, &sphere)};
    Intersection expected(0, nullptr); 

    ASSERT_EQ(hit(intersections), expected);
}

TEST(hit, hit4) { 
    Sphere sphere; 
    Intersection i1(5, &sphere); 
    Intersection i2(7, &sphere); 
    Intersection i3(-3, &sphere); 
    Intersection i4(2, &sphere); 
    std::vector<Intersection> intersections = {i1, i2, i3, i4};
    Intersection expected = i4; 

    ASSERT_EQ(hit(intersections), expected);

}

TEST(intersect, transform) { 
    Ray ray(Point(0, 0, -5), Vec(0, 0, 1));
    Sphere sphere; 
    sphere.transform(scaling(2, 2, 2));
    std::vector<Intersection> intersections = sphere.intersect(ray); 
    std::vector<Intersection> expected = {Intersection(3, &sphere), Intersection(7, &sphere)};
    ASSERT_EQ(intersections, expected); 
}

TEST(intersect, transform2) { 
    Ray ray(Point(0, 0, -5), Vec(0, 0, 1));
    Sphere sphere; 
    sphere.transform(translation(5, 0, 0));
    std::vector<Intersection> intersections = sphere.intersect(ray); 
    ASSERT_TRUE(intersections.empty());
}

