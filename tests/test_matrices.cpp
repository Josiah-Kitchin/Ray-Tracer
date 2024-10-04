
#include <gtest/gtest.h> 
#include "matrices.hpp"
#include "tuples.hpp"


TEST(Matrix, get) { 
    Matrix matrix{{1, 4, 7},
                  {2, 5, 8},
                  {3, 6, 9}};
    ASSERT_EQ(1, matrix.get(0, 0)); 
    ASSERT_EQ(2, matrix.get(1, 0)); 
    ASSERT_EQ(3, matrix.get(2, 0)); 
    ASSERT_EQ(4, matrix.get(0, 1)); 
    ASSERT_EQ(5, matrix.get(1, 1)); 
}

TEST(Matrix, set) { 
    Matrix matrix{{1, 4, 7},
                  {2, 5, 8},
                  {3, 6, 9}};
    matrix.set(1, 1) = 10; 
    ASSERT_EQ(10, matrix.get(1, 1)); 
}

TEST(Matrix, equals) { 
    Matrix matrix{{1, 4, 7},
                  {2, 5, 8},
                  {3, 6, 9}};

    Matrix matrix2{{1, 4, 7},
                  {2, 5, 8},
                  {3, 6, 9}};

    Matrix matrix3{{1, 4, 7},
                  {2, 8, 8},
                  {3, 6, 9}};
    ASSERT_EQ(matrix, matrix2); 
    ASSERT_TRUE(matrix != matrix3); 
}

TEST(Matrix, multiply4x4) { 
    Matrix matrix{{1, 2, 3, 4}, 
                  {5, 6, 7, 8}, 
                  {9, 8, 7, 6}, 
                  {5, 4, 3, 2}};

    Matrix matrix2{{-2, 1, 2, 3}, 
                   {3, 2, 1, -1}, 
                   {4, 3, 6, 5}, 
                   {1, 2, 7, 8}};

    Matrix expected{{20, 22, 50, 48}, 
                    {44, 54, 114, 108}, 
                    {40, 58, 110, 102}, 
                    {16, 26, 46, 42}};

    ASSERT_EQ(matrix * matrix2, expected); 
}

TEST(Matrix, identity) { 
    Matrix matrix{{1, 2, 3, 4}, 
                  {5, 6, 7, 8}, 
                  {9, 8, 7, 6}, 
                  {5, 4, 3, 2}};
    ASSERT_EQ(matrix * identity(), matrix);
}

TEST(Matrix, transpose) { 
    Matrix matrix{{0, 9, 3, 0}, 
                  {9, 8, 0, 8}, 
                  {1, 8, 5, 3}, 
                  {0, 0, 5, 8}}; 
    
    Matrix expected{{0, 9, 1, 0}, 
                    {9, 8, 8, 0}, 
                    {3, 0, 5, 5}, 
                    {0, 8, 3, 8}};

    ASSERT_EQ(expected, transpose(matrix));
}


TEST(Matrix, submatrix) { 
    Matrix matrix{{ 1, 5,  0}, 
                  {-3, 2,  7}, 
                  { 0, 6, -3}}; 
    
    Matrix expected{{-3, 2},
                    { 0, 6}}; 
    
    Matrix expected2{{2,  7}, 
                     {6, -3}};

    ASSERT_EQ(submatrix(matrix, 0, 2), expected); 
    ASSERT_EQ(submatrix(matrix, 0, 0), expected2); 
}

TEST(Matrix, minor) { 
    Matrix matrix{{3,  5, 0}, 
                  {2, -1, 7}, 
                  {6, -1, 5}};
    
    ASSERT_EQ(25, minor(matrix, 1, 0)); 
}

TEST(Matrix, cofactor) { 
    Matrix matrix{{3,  5,  0}, 
                  {2, -1, -7}, 
                  {6, -1,  5}};

    ASSERT_EQ(-12, cofactor(matrix, 0, 0)); 
    ASSERT_EQ(-25, cofactor(matrix, 1, 0)); 
}

TEST(Matrix, determinant) { 
    Matrix matrix{{1, 5}, 
                  {-3, 2}}; 
    ASSERT_EQ(17, determinant(matrix)); 

    Matrix matrix1{{ 1, 2,  6}, 
                  {-5, 8, -4}, 
                  { 2, 6,  4}};
    ASSERT_EQ(-196, determinant(matrix1)); 

    Matrix matrix2{{-2, -8,  3,  5}, 
                   {-3,  1,  7,  3},
                   { 1,  2, -9,  6},
                   {-6,  7,  7, -9}}; 
    ASSERT_EQ(-4071, determinant(matrix2)); 
}

TEST(Matrix, is_invertable) { 
    Matrix matrix{{6, 4, 4, 4}, 
                  {5, 5, 7, 6}, 
                  {4, -9, 3, -7}, 
                  {9, 1, 7, -6}};

    Matrix matrix2{{-4, 2, -2, -3}, 
                   {9, 6, 2, 6}, 
                   {0, -5, 1, -5}, 
                   {0, 0, 0, 0}};
    ASSERT_TRUE(is_invertable(matrix)); 
    ASSERT_FALSE(is_invertable(matrix2)); 
}

TEST(Matrix, inverse) { 
    Matrix matrix {{-5, 2, 6, -8}, 
                   {1, -5, 1, 8}, 
                   {7, 7, -6, -7}, 
                   {1, -3, 7, 4}};

    Matrix expected{{0.21805,  0.45113, 0.24060, -0.04511}, 
                    {-0.80827, -1.45677, -0.44361,  0.52068}, 
                    { -0.07895, -0.22368, -0.05263, 0.19737}, 
                    { -0.52256,  -0.81391,  -0.30075, 0.30639}}; 
    ASSERT_EQ(inverse(matrix), expected);
}

TEST(Matrix, translation) { 
    Matrix transform = translation(5, -3, 2); 
    Point point(-3, 4, 5); 
    ASSERT_EQ(Point(2, 1, 7), transform * point); 

    transform = translation(5, -3, 2); 
    Matrix inv = inverse(transform); 
    ASSERT_EQ(Point(-8, 7, 3), inv * point);
    Vec vect(-3, 4, 5); 
    ASSERT_EQ(vect, transform * vect); 
}

TEST(Matrix, scaling) { 
    Matrix transform = scaling(2, 3, 4); 
    Point point(-4, 6, 8); 
    ASSERT_EQ(Point(-8, 18, 32), transform * point); 

    Vec vec(-4, 6, 8); 
    ASSERT_EQ(Vec(-8, 18, 32), transform * vec);

    Matrix inv = inverse(transform); 
    ASSERT_EQ(Vec(-2, 2, 2), inv * vec);

    Matrix reflect = scaling(-1, 1, 1); 
    point = Point(2, 3, 4); 
    ASSERT_EQ(Point(-2, 3, 4), reflect * point); 
}

TEST(Matrix, rotation_x) { 
    using std::sqrt; 
    Point point(0, 1, 0); 
    Matrix half_quarter = rotation_x(M_PI / 4);
    Matrix full_quarter = rotation_x(M_PI / 2); 
    ASSERT_EQ(Point(0, sqrt(2)/2, sqrt(2)/2), half_quarter * point); 
    ASSERT_EQ(Point(0, 0, 1), full_quarter * point); 
    Matrix inv = inverse(half_quarter); 
    ASSERT_EQ(Point(0, sqrt(2)/2, -sqrt(2)/2), inv * point);
}

TEST(Matrix, rotation_y) { 
    using std::sqrt; 
    Point point(0, 0, 1); 
    Matrix half_quarter = rotation_y(M_PI / 4);
    Matrix full_quarter = rotation_y(M_PI / 2);
    ASSERT_EQ(Point(sqrt(2)/2, 0, sqrt(2)/2), half_quarter * point);
    ASSERT_EQ(Point(1, 0, 0), full_quarter * point); 
}

TEST(Matrix, rotation_z) { 
    using std::sqrt; 
    Point point(0, 1, 0); 
    Matrix half_quarter = rotation_z(M_PI / 4); 
    Matrix full_quarter = rotation_z(M_PI / 2);
    ASSERT_EQ(Point(-sqrt(2)/2, sqrt(2)/2, 0), half_quarter * point);
    ASSERT_EQ(Point(-1, 0, 0), full_quarter * point); 
}

TEST(Matrix, shearing) { 
    Matrix transform = shearing(1, 0, 0, 0, 0, 0);
    Point point(2, 3, 4); 
    ASSERT_EQ(Point(5, 3, 4), transform * point); 
    transform = shearing(0, 1, 0, 0, 0, 0); 
    ASSERT_EQ(Point(6, 3, 4), transform * point);
    transform = shearing(0, 0, 1, 0, 0, 0); 
    ASSERT_EQ(Point(2, 5, 4), transform * point);
    transform = shearing(0, 0, 0, 1, 0, 0); 
    ASSERT_EQ(Point(2, 7, 4), transform * point);
    transform = shearing(0, 0, 0, 0, 1, 0); 
    ASSERT_EQ(Point(2, 3, 6), transform * point); 
    transform = shearing(0, 0, 0, 0, 0, 1); 
    ASSERT_EQ(Point(2, 3, 7), transform * point);
}

TEST(Matrix, transformation_sequence) { 
    Point point(1, 0, 1); 
    Matrix rotate = rotation_x(M_PI / 2);
    Matrix scale = scaling(5, 5, 5); 
    Matrix translate = translation(10, 5, 7); 
    point = point * rotate; 
    point = point * scale; 
    point = point * translate; 
    ASSERT_EQ(Point(15, 0, 7), point); 
    point = Point(1, 0, 1); 
    Matrix transform = translate * scale * rotate; 
    ASSERT_EQ(Point(15, 0, 7), point * transform); 
}




