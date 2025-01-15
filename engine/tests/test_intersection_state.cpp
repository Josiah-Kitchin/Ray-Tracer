
#include <gtest/gtest.h> 

#include "geo/intersection_state.hpp"
#include "xform/matrices.hpp"
#include "scene/hittable.hpp"
#include "utils.hpp"
#include <vector> 

using namespace geo; 
using namespace scene; 

TEST(IntersectionState, init) {
    Ray ray(Point(0, 0, -5), Vec(0, 0, 1));
    Sphere sphere; 
    std::vector<Intersection>i {Intersection(4, &sphere)};
    IntersectionState state(0, i, ray);

    ASSERT_EQ(state.t, i[0].t);
    ASSERT_EQ(state.object, i[0].object);
    ASSERT_EQ(state.point, Point(0, 0, -1));
    ASSERT_EQ(state.eye, Vec(0, 0, -1));
    ASSERT_EQ(state.normal, Vec(0, 0, -1));
}

TEST(IntersectionState, inside) {
    Ray ray(Point(0, 0, -5), Vec(0, 0, 1));
    Sphere sphere; 
    std::vector<Intersection>i {Intersection(4, &sphere)};
    IntersectionState state(0, i, ray);
    ASSERT_FALSE(state.inside);
}

TEST(IntersectionState, inside_hit) {
    Ray ray(Point(0, 0, 0), Vec(0, 0, 1));
    Sphere sphere; 
    std::vector<Intersection>i {Intersection(1, &sphere)};
    IntersectionState state(0, i, ray);
    
    ASSERT_EQ(state.point, Point(0, 0, 1));
    ASSERT_EQ(state.eye, Vec(0, 0, -1));
    ASSERT_TRUE(state.inside);
    ASSERT_EQ(state.normal, Vec(0, 0, -1));
}

TEST(IntersectionState, over_point) { 
    Ray ray(Point(0, 0, -5), Vec(0, 0, 1));
    scene::Sphere shape; 
    shape
        .transform(xform::translation(0, 0, 1));

    std::vector<Intersection>i {Intersection(5, &shape)};
    IntersectionState state(0, i, ray);
    ASSERT_LT(state.over_point.z, -utils::EPSILON/2);
    ASSERT_GT(state.point.z, state.over_point.z);
}

TEST(InteresctionState, reflect) { 
    scene::Plane plane; 
    Ray ray(Point(0, 1, -1), Vec(0, -sqrt(2)/2, sqrt(2)/2));

    std::vector<Intersection>i {Intersection(sqrt(2), &plane)};
    IntersectionState state(0, i, ray);
    ASSERT_EQ(state.reflect, Vec(0, sqrt(2)/2, sqrt(2)/2));
}

TEST(IntersectionState, n1n2) { 
    scene::Material glass; 
    glass
        .set_transparency(1.0)
        .set_refractive_index(1.5);

    scene::Material glass2; 
    glass2
        .set_transparency(1.0)
        .set_refractive_index(2.0);

    scene::Material glass3; 
    glass3
        .set_transparency(1.0)
        .set_refractive_index(2.5);

    scene::Sphere sphere; 
    sphere
        .set_material(glass)
        .transform(xform::scaling(2, 2, 2));

    scene::Sphere sphere2; 
    sphere2
        .set_material(glass2)
        .transform(xform::translation(0, 0, -0.25));

    scene::Sphere sphere3; 
    sphere3
        .set_material(glass3)
        .transform(xform::translation(0, 0, 0.25));

    geo::Ray ray(geo::Point(0, 0, -4), geo::Vec(0, 0, 1));
    std::vector<Intersection> intersections { Intersection(2, &sphere), Intersection(2.75, &sphere2),
                                              Intersection(3.25, &sphere3), Intersection(4.75, &sphere2),
                                              Intersection(5.25, &sphere3), Intersection(6, &sphere)};

    IntersectionState state1(0, intersections, ray);
    ASSERT_EQ(state1.n1, 1.0);
    ASSERT_EQ(state1.n2, 1.5);

    IntersectionState state2(1, intersections, ray);
    ASSERT_EQ(state2.n1, 1.5);
    ASSERT_EQ(state2.n2, 2.0);

    IntersectionState state3(2, intersections, ray);
    ASSERT_EQ(state3.n1, 2.0);
    ASSERT_EQ(state3.n2, 2.5);

    IntersectionState state4(3, intersections, ray);
    ASSERT_EQ(state4.n1, 2.5);
    ASSERT_EQ(state4.n2, 2.5);

    IntersectionState state5(4, intersections, ray);
    ASSERT_EQ(state5.n1, 2.5);
    ASSERT_EQ(state5.n2, 1.5);
    
    IntersectionState state6(5, intersections, ray);
    ASSERT_EQ(state6.n1, 1.5);
    ASSERT_EQ(state6.n2, 1.0);
}

TEST(IntersectionState, under_point) { 
    Ray ray(geo::Point(0, 0, -5), geo::Vec(0, 0, 1));
    Sphere sphere;
    sphere
        .set_transparency(0)
        .set_refractive_index(1.52)
        .transform(xform::translation(0, 0, 1));

    Intersection i(5, &sphere);
    std::vector<Intersection> intersections{i};
    IntersectionState state(0, intersections, ray);
    ASSERT_GT(state.under_point.z, utils::EPSILON/2);
    ASSERT_LT(state.point.z, state.under_point.z);
}




