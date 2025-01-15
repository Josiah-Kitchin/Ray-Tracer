

#include <gtest/gtest.h> 

#include "image/canvas.hpp" 

using namespace image; 
using namespace geo; 
using namespace color; 

TEST(Canvas, pixel_at) { 
    Canvas canvas(10, 10); 
    for (int i = 0; i < 10; i++) { 
        for (int j = 0; j < 10; j++) { 
            ASSERT_EQ(RGB(1, 1, 1), canvas.pixel_at(i, j)); 
        }
    }
}

TEST(Canvas, write_color) { 
    Canvas canvas(10, 10); 
    canvas.insert_color(RGB(1, 0, 0), 3, 3);  
    ASSERT_EQ(RGB(1, 0, 0), canvas.pixel_at(3, 3)); 
}



