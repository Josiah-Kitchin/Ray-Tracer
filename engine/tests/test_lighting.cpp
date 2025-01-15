#include <gtest/gtest.h> 
#include "scene/material.hpp"
#include "scene/hittable.hpp"
#include "geo/tuples.hpp"
#include "scene/light.hpp"

using namespace geo; 
using namespace scene; 
using namespace color; 

TEST(lighting, lighting) { 
    Vec eyev(0, 0, -1);
    Vec normalv(0, 0, -1);
    Light light(RGB(1, 1, 1), Point(0, 0, -10));
    Material mat; 
    mat.color = RGB(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9; mat.specular=0.9;
    Sphere sphere; 
    sphere
        .set_material(mat);
    Point position(0, 0, 0);

    ASSERT_EQ(RGB(1.9, 1.9, 1.9), calculate_lighting(&sphere, light, position, eyev, normalv, false));
}

TEST(lighting, lighting2) { 
    Vec eyev(0, sqrt(2)/2, -sqrt(2)/2);
    Vec normalv(0, 0, -1);
    Light light(RGB(1, 1, 1), Point(0, 0, -10));
    Material mat; 
    mat.color = RGB(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9; 
    Sphere sphere; 
    sphere.set_material(mat);
    Point position(0, 0, 0);

    ASSERT_EQ(RGB(1.0, 1.0, 1.0), calculate_lighting(&sphere, light, position, eyev, normalv, false));
}

TEST(lighting, lighting3) { 
    Vec eyev(0, 0, -1); 
    Vec normalv(0, 0, -1);
    Light light(RGB(1, 1, 1), Point(0, 10, -10));
    Material mat; 
    mat.color = RGB(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9;
    mat.shininess = 1; 
    Sphere sphere; 
    sphere.set_material(mat);
    Point position(0, 0, 0);

    ASSERT_EQ(RGB(0.7364, 0.7364, 0.7364), calculate_lighting(&sphere, light, position, eyev, normalv, false));
}

TEST(lighting, lighting4) { 
    Vec eyev(0, -sqrt(2)/2, -sqrt(2)/2); 
    Vec normalv(0, 0, -1);
    Light light(RGB(1, 1, 1), Point(0, 10, -10));
    Material mat; 
    mat.color = RGB(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9; mat.specular = 0.9; 
    mat.shininess = 1;
    Sphere sphere; 
    sphere.set_material(mat);
    Point position(0, 0, 0);

    ASSERT_EQ(RGB(1.6364, 1.6364, 1.6364), calculate_lighting(&sphere, light, position, eyev, normalv, false));
}

TEST(lighting, lighting_shadow) { 
    Vec eyev(0, 0, -1);
    Vec normalv(0, 0, -1);
    Light light(RGB(1, 1, 1), Point(0, 0, -10));
    Material mat; 
    mat.color = RGB(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9; mat.specular=0.9;
    Point position(0, 0, 0);
    bool in_shadow = true;

    Sphere sphere; 
    sphere.set_material(mat);
    ASSERT_EQ(RGB(0.1, 0.1, 0.1), calculate_lighting(&sphere, light, position, eyev, normalv, in_shadow));
}

TEST(lighting, pattern) { 
    color::Stripes pattern; 
    pattern
        .set_first_color(color::white())
        .set_second_color(color::black());

    Material mat; 
    mat
        .set_pattern(&pattern)
        .set_ambient(1)
        .set_diffuse(0)
        .set_specular(0); 
    Vec eye(0, 0, -1);
    Vec normal(0, 0, -1);
    Light light;
    light
        .set_intensity(color::RGB(1, 1, 1))
        .set_position(geo::Point(0, 0, -10));

    Sphere sphere; 
    sphere.set_material(mat);

    color::RGB c1 = calculate_lighting(&sphere, light, Point(0.9, 0, 0), eye, normal, false);
    color::RGB c2 = calculate_lighting(&sphere, light, Point(1.1, 0, 0), eye, normal, false);

    ASSERT_EQ(c1, color::black());
    ASSERT_EQ(c2, color::white());
}
