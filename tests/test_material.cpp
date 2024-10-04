#include <gtest/gtest.h> 
#include "material.hpp"
#include "tuples.hpp"
#include "light.hpp"


TEST(lighting, lighting) { 
    Vec eyev(0, 0, -1);
    Vec normalv(0, 0, -1);
    Light light(Color(1, 1, 1), Point(0, 0, -10));
    Material mat; 
    mat.color = Color(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9; mat.specular=0.9;
    Point position(0, 0, 0);

    ASSERT_EQ(Color(1.9, 1.9, 1.9), lighting(mat, light, position, eyev, normalv));
}

TEST(lighting, lighting2) { 
    Vec eyev(0, sqrt(2)/2, -sqrt(2)/2);
    Vec normalv(0, 0, -1);
    Light light(Color(1, 1, 1), Point(0, 0, -10));
    Material mat; 
    mat.color = Color(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9; 
    Point position(0, 0, 0);

    ASSERT_EQ(Color(1.0, 1.0, 1.0), lighting(mat, light, position, eyev, normalv));
}

TEST(lighting, lighting3) { 
    Vec eyev(0, 0, -1); 
    Vec normalv(0, 0, -1);
    Light light(Color(1, 1, 1), Point(0, 10, -10));
    Material mat; 
    mat.color = Color(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9 * (sqrt(2)/2);
    Point position(0, 0, 0);

    ASSERT_EQ(Color(0.7364, 0.7364, 0.7364), lighting(mat, light, position, eyev, normalv));
}

TEST(lighting, lighting4) { 
    Vec eyev(0, -sqrt(2)/2, -sqrt(2)/2); 
    Vec normalv(0, 0, -1);
    Light light(Color(1, 1, 1), Point(0, 10, -10));
    Material mat; 
    mat.color = Color(1,1,1);
    mat.ambient = 0.1; mat.diffuse = 0.9 * (sqrt(2)/2); mat.specular = 0.9; 
    Point position(0, 0, 0);

    ASSERT_EQ(Color(1.6364, 1.6364, 1.6364), lighting(mat, light, position, eyev, normalv));
}
