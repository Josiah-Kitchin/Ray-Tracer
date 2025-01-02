

#include <gtest/gtest.h> 
#include "color/color.hpp"
#include "color/pattern.hpp"
#include "geo/tuples.hpp"

using namespace color; 
using namespace geo; 

TEST(Stripes, color_at) {
    Stripes stripes; 
    stripes
        .set_first_color(black())
        .set_second_color(white());

    ASSERT_EQ(stripes.color_at(Point(0, 0, 0)), white());
    ASSERT_EQ(stripes.color_at(Point(0.9, 0, 0)), white());
    ASSERT_EQ(stripes.color_at(Point(1, 0, 0)), black());
    ASSERT_EQ(stripes.color_at(Point(-0.1, 0, 0)), black());
    ASSERT_EQ(stripes.color_at(Point(-1, 0, 0)), black());
    ASSERT_EQ(stripes.color_at(Point(-1.1, 0, 0)), white());
}

TEST(Gradient, color_at) {
    Gradient gradient; 
    gradient
        .set_first_color(black())
        .set_second_color(white());

    ASSERT_EQ(gradient.color_at(geo::Point(0, 0, 0)), black());
    ASSERT_EQ(gradient.color_at(geo::Point(0.25, 0, 0)), RGB(0.25, 0.25, 0.25));
    ASSERT_EQ(gradient.color_at(geo::Point(0.5, 0, 0)), RGB(0.5, 0.5, 0.5));
    ASSERT_EQ(gradient.color_at(geo::Point(0.75, 0, 0)), RGB(0.75, 0.75, 0.75));


}