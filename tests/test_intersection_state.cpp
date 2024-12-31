
#include <gtest/gtest.h> 

#include "geo/intersection_state.hpp"

using namespace geo; 
using namespace scene; 

TEST(IntersectionState, init) {
    Ray ray(Point(0, 0, -5), Vec(0, 0, 1));
    Sphere sphere; 
    Intersection i(4, &sphere);
    IntersectionState state(i, ray);

    ASSERT_EQ(state.t, i.t);
    ASSERT_EQ(state.object, i.object);
    ASSERT_EQ(state.point, Point(0, 0, -1));
    ASSERT_EQ(state.eye, Vec(0, 0, -1));
    ASSERT_EQ(state.normal, Vec(0, 0, -1));
}

TEST(IntersectionState, inside) {
    Ray ray(Point(0, 0, -5), Vec(0, 0, 1));
    Sphere sphere; 
    Intersection i(4, &sphere);
    IntersectionState state(i, ray);
    ASSERT_FALSE(state.inside);
}

TEST(IntersectionState, inside_hit) {
    Ray ray(Point(0, 0, 0), Vec(0, 0, 1));
    Sphere sphere; 
    Intersection i(1, &sphere);
    IntersectionState state(i, ray);
    
    ASSERT_EQ(state.point, Point(0, 0, 1));
    ASSERT_EQ(state.eye, Vec(0, 0, -1));
    ASSERT_TRUE(state.inside);
    ASSERT_EQ(state.normal, Vec(0, 0, -1));
}