#include <gtest/gtest.h> 
#include "scene/material.hpp"
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
    Point position(0, 0, 0);

    ASSERT_EQ(RGB(1.9, 1.9, 1.9), calculate_lighting(mat, light, position, eyev, normalv));
}

TEST(lighting, lighting2) { 
    Vec eyev(0, sqrt(2)/2, -sqrt(2)/2);
    Vec normalv(0, 0, -1);
    Light light(RGB(1, 1, 1), Point(0, 0, -10));
    Material mat; 
    mat.color = RGB(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9; 
    Point position(0, 0, 0);

    ASSERT_EQ(RGB(1.0, 1.0, 1.0), calculate_lighting(mat, light, position, eyev, normalv));
}

TEST(lighting, lighting3) { 
    Vec eyev(0, 0, -1); 
    Vec normalv(0, 0, -1);
    Light light(RGB(1, 1, 1), Point(0, 10, -10));
    Material mat; 
    mat.color = RGB(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9;
    mat.shininess = 1; 
    Point position(0, 0, 0);

    ASSERT_EQ(RGB(0.7364, 0.7364, 0.7364), calculate_lighting(mat, light, position, eyev, normalv));
}

TEST(lighting, lighting4) { 
    Vec eyev(0, -sqrt(2)/2, -sqrt(2)/2); 
    Vec normalv(0, 0, -1);
    Light light(RGB(1, 1, 1), Point(0, 10, -10));
    Material mat; 
    mat.color = RGB(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9; mat.specular = 0.9; 
    mat.shininess = 1;
    Point position(0, 0, 0);

    ASSERT_EQ(RGB(1.6364, 1.6364, 1.6364), calculate_lighting(mat, light, position, eyev, normalv));
}
