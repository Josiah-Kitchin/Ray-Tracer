
#include <gtest/gtest.h> 
#include "geo/tuples.hpp" 
#include "color/color.hpp"

using namespace geo; 
using namespace color; 

TEST(Vec, add) { 
    Vec actual = Vec(1,1,1) + Vec(1,1,1);  
    ASSERT_EQ(Vec(2,2,2), actual); 
}

TEST(Vec, subtract) { 
    Vec actual = Vec(1, 1, 1); 
    ASSERT_EQ(Vec(0, 0, 0), actual - actual); 
}

TEST(Vec, multiply) { 
    Vec actual = Vec(2, 2, 2); 
    ASSERT_EQ(Vec(4, 4, 4), actual * 2); 
    ASSERT_EQ(Vec(4, 4, 4), 2 * actual); 
    ASSERT_EQ(Vec(4, 4, 4), actual * Vec(2, 2, 2)); 
}

TEST(Vec, divide) { 
    Vec actual = Vec(4, 4, 4); 
    ASSERT_EQ(Vec(2, 2, 2), actual / 2); 
}

TEST(Vec, negative) { 
    ASSERT_EQ(-Vec(1,1,1), Vec(-1,-1,-1)); 
    ASSERT_EQ(-Vec(-1,-1,-1), Vec(1,1,1)); 
}

TEST(Vec, plus_equal) { 
    Vec actual = Vec(1,1,1); 
    actual += Vec(2,2,2); 
    ASSERT_EQ(Vec(3,3,3), actual); 
}

TEST(Vec, multiply_equal) { 
    Vec actual1 = Vec(2,2,2);
    actual1 *= Vec(4,4,4); 

    Vec actual2 = Vec(2,2,2); 
    actual2 *= 4; 
    ASSERT_EQ(Vec(8,8,8), actual1);
    ASSERT_EQ(Vec(8,8,8), actual2); 
}

TEST(Vec, divide_equal) { 
    Vec actual = Vec(4, 4, 4); 
    actual /= 2; 
    ASSERT_EQ(Vec(2,2,2), actual); 
}

TEST(Vec, length_squared) { 
    double actual = Vec(4,4,4).length_squared(); 
    ASSERT_EQ(16 + 16 + 16, actual); 
}

TEST(Vec, length) { 
    double actual = Vec(4,4,4).length(); 
    ASSERT_EQ(std::sqrt(16 + 16 + 16), actual); 
}

TEST(Vec, cross) { 
    Vec actual = cross(Vec(1,2,3), Vec(3,2,1)); 
    ASSERT_EQ(Vec(-4, 8, -4), actual); 
}

TEST(Vec, dot) { 
    double actual = dot(Vec(1, 2, 3), Vec(3, 2, 1)); 
    ASSERT_EQ(10, actual); 
}

TEST(Vec, unit_vector) { 
    Vec actual = unit_vector(Vec(2,2,2)); 
    ASSERT_EQ((Vec(2,2,2) / Vec(2,2,2).length()), actual); 
}

TEST(Vec, reflect) { 
    ASSERT_EQ(Vec(1, 1, 0), reflect(Vec(1, -1, 0), Vec(0, 1, 0)));
    ASSERT_EQ(Vec(1, 0, 0), reflect(Vec(0, -1, 0), Vec(sqrt(2)/2, sqrt(2)/2, 0)));
}

TEST(Point, plus_equals) { 
    Point actual(1, 1, 1); 
    actual += Vec(2, 2, 2); 
    ASSERT_EQ(Point(3, 3, 3), actual);
}

TEST(Point, add) { 
    Point actual = Vec(1, 1, 1) + Point(1, 1, 1); 
    ASSERT_EQ(Point(2, 2, 2), actual); 
}

TEST(Point, subtract) {
    Vec actual = Point(3, 3, 3) - Point(2, 2, 2); 
    ASSERT_EQ(Vec(1, 1, 1), actual); 
}  

TEST(RGB, plus_equals) { 
    RGB actual(0.5 ,0.5, 0.5); 
    actual += RGB(0.5, 0.5, 0.5); 
    ASSERT_EQ(RGB(1, 1, 1), actual); 
    actual += Point(1, 1, 1); 
    ASSERT_EQ(RGB(2, 2, 2), actual); 
}

TEST(RGB, add) { 
    RGB actual = RGB(1, 1, 1) + RGB(1, 1, 1); 
    ASSERT_EQ(RGB(2, 2, 2), actual); 
    actual = RGB(1, 1, 1) + Point(1, 1, 1); 
    ASSERT_EQ(RGB(2, 2, 2), actual); 
}

TEST(RGB, clamp) { 
    RGB actual(50, 24, 21); 
    actual.clamp(); 
    ASSERT_EQ(actual, RGB(1, 1, 1)); 
    actual = RGB(-1, -1, -1); 
    actual.clamp(); 
    ASSERT_EQ(actual, RGB(0, 0, 0)); 
}

TEST(RGB, conert_to_256) { 
    RGB actual(1, 1, 1); 
    actual.convert_to_256(); 
    ASSERT_EQ(RGB(255, 255, 255), actual);
}



