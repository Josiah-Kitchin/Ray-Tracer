#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <vector> 
#include <array> 
#include <initializer_list> 
#include <iostream> 
#include "geo/tuples.hpp"

/*
    The cursed matrix class. utilizes templates to speed up all matrix operations

    --The template is so it can have a variable sized array instead of a vector to keep memory on the stack 
    --The only matrices that will be used is 4, 3, and 2 (representing 4x4, 3x3, etc)

    This results in the matrix operations being very fast with a downside of less readable code 

*/


namespace xform { 

    template <std::size_t N> 
    class Matrix { 
    private: 
        std::array<double, N * N> m_data; 

    public: 
        Matrix(); 
        Matrix(const std::array<double, N * N>&);
        Matrix(const Matrix<N>&); 
        Matrix<N>& operator=(const Matrix<N>& other);

        double get(int, int) const;  
        void set(double, int, int); 

    };

    template <std::size_t N> 
    bool operator==(const Matrix<N>&, const Matrix<N>&); 
    template <std::size_t N> 
    bool operator!=(const Matrix<N>&, const Matrix<N>&); 
    
    Matrix<4> operator*(const Matrix<4>&, const Matrix<4>&); 

    template <std::size_t N> 
    std::ostream& operator<<(std::ostream&, const Matrix<N>&); 


    template <std::size_t N> 
    Matrix<N> inverse(const Matrix<N>&);  
    template <std::size_t N> 
    Matrix<N> transpose(const Matrix<N>&); 

    Matrix<4> identity(); 

    Matrix<4> translation(double, double, double); 
    Matrix<4> scaling(double, double, double); 
    Matrix<4> rotation_x(double); 
    Matrix<4> rotation_y(double); 
    Matrix<4> rotation_z(double); 
    Matrix<4> shearing(double, double, double, double, double, double);
    Matrix<4> view_transform(const geo::Point&, const geo::Point&, const geo::Vec&);

    geo::Point operator*(const Matrix<4>&, const geo::Point&);
    geo::Point operator*(const geo::Point&, const Matrix<4>&);
    geo::Vec operator*(const Matrix<4>&, const geo::Vec&); 
    geo::Vec operator*(const geo::Vec&, const Matrix<4>&);

}

template <std::size_t N> 
double cofactor(const xform::Matrix<N>& matrix, size_t delete_row, size_t delete_column);  
template <std::size_t N> 
double minor(const xform::Matrix<N>& matrix, size_t delete_row, size_t delete_column);  
template <std::size_t N> 
double determinant(const xform::Matrix<N>& matrix);  
template <std::size_t N> 
xform::Matrix<N - 1> submatrix(const xform::Matrix<N>& matrix, size_t delete_row, size_t delete_col);  
template <std::size_t N> 
bool is_invertable(const xform::Matrix<N>& matrix);  





/*--------------------------------- IMPLEMETATION ------------------------------------*/

#include "utils.hpp"
#include <cassert> 
#include <cmath> 

using std::vector; 
using std::initializer_list; 
using std::size_t; 

/* ----------------- Matrix Class ------------------ */

template <std::size_t N> 
xform::Matrix<N>::Matrix() {
    m_data.fill(0);
}  

template <std::size_t N> 
xform::Matrix<N>::Matrix(const std::array<double, N * N>& in_data) {
    m_data = in_data; 
}

template <std::size_t N> 
xform::Matrix<N>::Matrix(const Matrix<N>& other) {
    m_data = other.m_data;
}

template <std::size_t N> 
xform::Matrix<N>& xform::Matrix<N>::operator=(const Matrix<N>& other) {
    m_data = other.m_data;
    return *this; 
}
    
template <std::size_t N> 
double inline xform::Matrix<N>::get(int row, int col) const { 
    return m_data[row * N + col];
}

template <std::size_t N> 
void inline xform::Matrix<N>::set(double value, int row, int col) { 
    m_data[row * N + col] = value;
}

/* ------------------- Matrix manipulation ----------------------- */

template <std::size_t N> 
xform::Matrix<N> xform::transpose(const xform::Matrix<N>& matrix) { 
    //returns a matrix with flipped rows and columns of the given matrix
    xform::Matrix<N> result; 
    for (size_t row = 0; row < N; row++) { 
        for (size_t col = 0; col < N; col++) { 
            result.set(matrix.get(col, row), row, col); 
        }
    }
    return result; 
}

template <std::size_t N> 
xform::Matrix<N> xform::inverse(const xform::Matrix<N>& matrix) { 
    assert(is_invertable(matrix)); 

    xform::Matrix<N> result_matrix;
    for (size_t row = 0; row < N; row++) { 
        for (size_t col = 0; col < N; col++) { 
            //column row accomplishes the transpose operation 
            result_matrix.set(cofactor(matrix, row, col) / determinant(matrix), col, row); 
        }
    }
    return result_matrix; 
}


/* ---------------------- Transformation Matrices ---------------------- */

xform::Matrix<4> inline xform::identity() { 
    //returns a 4x4 idenity_matrix. Returns the originial matrix when 
    //mulitiplied by the identity matrix
    return xform::Matrix<4>({ 1, 0, 0, 0, 
                              0, 1, 0, 0,
                              0, 0, 1, 0, 
                              0, 0, 0, 1 });
}


xform::Matrix<4> inline xform::translation(double x, double y, double z) { 
    //the translation matrix is meant to be mulitpled with a point to return a point translated 
    //in the direction of x y and z (point.x += x, point.y += y, point.z += z)
    return xform::Matrix<4>({1, 0, 0, x,
                             0, 1, 0, y, 
                             0, 0, 1, z, 
                             0, 0, 0, 1}); 
}

xform::Matrix<4> inline xform::scaling(double x, double y, double z) { 
    //Scales a point when scaling is multiplied by a point. 
    return xform::Matrix<4>({x, 0, 0, 0, 
                             0, y, 0, 0, 
                             0, 0, z, 0,
                             0, 0, 0, 1});
}

xform::Matrix<4> inline xform::rotation_x(double radians) { 
    //Rotates the point along the x-axis
    return xform::Matrix<4>({1, 0, 0, 0, 
                             0, std::cos(radians), -std::sin(radians), 0,
                             0, std::sin(radians), std::cos(radians), 0, 
                             0, 0, 0, 1});

}

xform::Matrix<4> inline xform::rotation_y(double radians) { 
    return xform::Matrix<4>({std::cos(radians), 0, std::sin(radians), 0, 
                            0, 1, 0, 0, 
                            -std::sin(radians), 0, std::cos(radians), 0,
                            0, 0, 0, 1});
}

xform::Matrix<4> inline xform::rotation_z(double radians) { 
    return xform::Matrix<4>({std::cos(radians), -std::sin(radians), 0, 0,
                            std::sin(radians), std::cos(radians), 0, 0,
                            0, 0, 1, 0, 
                            0, 0, 0, 1});
}

xform::Matrix<4> inline xform::shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) {
    //Slans the point. The parameters are the values in proportion to each other. For example, 
    //x_y is the proportion of change of x to y. 
    return xform::Matrix<4>({1, x_y, x_z, 0, 
                            y_x, 1, y_z, 0,
                            z_x, z_y, 1, 0,
                            0, 0, 0, 1});
}

xform::Matrix<4> inline xform::view_transform(const geo::Point& from, const geo::Point& to, const geo::Vec& up) { 
    /*  Transforms the world, can be thought of as moving the eye 
        from: Where the eye should be in the scene
        to: where the eye will look
        up: vector indicidating which direction is up
    */

   geo::Vec foward = unit_vector(to - from);
   geo::Vec normal_up = unit_vector(up);
   geo::Vec left = cross(foward, normal_up);
   geo::Vec true_up = cross(left, foward);

   xform::Matrix<4> orientation({left.x,    left.y,    left.z,    0,
                                true_up.x, true_up.y, true_up.z, 0,
                                -foward.x, -foward.y, -foward.z, 0, 
                                0,         0,         0,         1});

    return orientation * xform::translation(-from.x, -from.y, -from.z);
}



/* ------------------- Operators ---------------- */

xform::Matrix<4> inline xform::operator*(const xform::Matrix<4>& left, const xform::Matrix<4>& right) { 
    
    xform::Matrix<4> result; 
    for (int row = 0; row < 4; row++) { 
        for (int col = 0; col < 4; col++) { 
            double product = left.get(row, 0) * right.get(0, col) + 
                             left.get(row, 1) * right.get(1, col) + 
                             left.get(row, 2) * right.get(2, col) + 
                             left.get(row, 3) * right.get(3, col); 
            result.set(product, row, col);
        }
    }
    return result; 
}

template <size_t N> 
bool xform::operator==(const xform::Matrix<N>& left, const xform::Matrix<N>& right) { 

    for (size_t row = 0; row < N; row++) { 
        for (size_t col = 0; col < N; col++) { 
            if (!utils::compare_doubles(left.get(row, col), right.get(row, col))) { 
                return false; 
            }
        }
    }
    return true; 
}

template <std::size_t N> 
bool xform::operator!=(const xform::Matrix<N>& left, const xform::Matrix<N>& right) { 
    return !(left == right);
}

template <std::size_t N> 
std::ostream& xform::operator<<(std::ostream& out, const xform::Matrix<N>& matrix) { 
    //for testing purposes 
    out << '\n';
    for (size_t row = 0; row < N; row++) { 
        for (size_t col = 0; col < N; col++) { 
            out << matrix.get(row, col) << " "; 
        }
        out << '\n';
    }
    return out; 
}


//Point and vec interaction 

geo::Point inline xform::operator*(const xform::Matrix<4>& matrix, const geo::Point& point) { 

    double x_new = matrix.get(0, 0) * point.x + matrix.get(0, 1) * point.y + matrix.get(0,2) * point.z + matrix.get(0,3);
    double y_new = matrix.get(1, 0) * point.x + matrix.get(1, 1) * point.y + matrix.get(1, 2) * point.z + matrix.get(1, 3);
    double z_new = matrix.get(2, 0) * point.x + matrix.get(2, 1) * point.y + matrix.get(2, 2) * point.z + matrix.get(2, 3);

    return geo::Point(x_new, y_new, z_new);
}

geo::Point inline xform::operator*(const geo::Point& point, const xform::Matrix<4>& matrix) { 
    return matrix * point; 
}

geo::Vec inline xform::operator*(const xform::Matrix<4>& matrix, const geo::Vec& vec) { 

    double x_new = matrix.get(0, 0) * vec.x + matrix.get(0, 1) * vec.y + matrix.get(0,2)  * vec.z; 
    double y_new = matrix.get(1, 0) * vec.x + matrix.get(1, 1) * vec.y + matrix.get(1, 2) * vec.z;
    double z_new = matrix.get(2, 0) * vec.x + matrix.get(2, 1) * vec.y + matrix.get(2, 2) * vec.z;

    return geo::Vec(x_new, y_new, z_new);
}

geo::Vec inline xform::operator*(const geo::Vec& vec, const xform::Matrix<4>& matrix) { 
    return matrix * vec; 
}


/* ------------------------- Static Functions ------------------------------ */
 

template <std::size_t N> 
xform::Matrix<N - 1> submatrix(const xform::Matrix<N>& matrix, size_t delete_row, size_t delete_col) { 
    //Returns a matrix similar to the given matrix but has a given row and col subtracted. For example, 
    // a 4x4 matrix returns a 3x3 matrix. 

    xform::Matrix<N - 1>result;  
    
    int result_row = 0;  
    for (size_t row = 0; row < N; ++row) {
        if (row == delete_row) continue;  
        
        int result_col = 0;  
        for (size_t col = 0; col < N; ++col) {
            if (col == delete_col) continue; 
            
            result.set(matrix.get(row, col), result_row, result_col);  
            ++result_col;  
        }
        ++result_row;  
    }
    
    return result;
}


template <std::size_t N>
double determinant(const xform::Matrix<N>& matrix) {
    //Uses constexpr to figure out what to do for the matrix at compile time 
    if constexpr (N == 2) { // Base case for 2x2 matrix
        return matrix.get(0, 0) * matrix.get(1, 1) - 
               matrix.get(0, 1) * matrix.get(1, 0);
    } else if constexpr (N == 3) { // Handle 3x3 matrix
        return matrix.get(0, 0) * cofactor(matrix, 0, 0) -
               matrix.get(0, 1) * cofactor(matrix, 0, 1) +
               matrix.get(0, 2) * cofactor(matrix, 0, 2);
    } else if constexpr (N == 4) { // Handle 4x4 matrix
        double det = 0;
        for (size_t col = 0; col < 4; col++) {
            det += matrix.get(0, col) * cofactor(matrix, 0, col);
        }
        return det;
    }
}

template <std::size_t N>
double cofactor(const xform::Matrix<N>& matrix, size_t row, size_t col) {
    //Uses constexpr to figure out what to do for the matrix at compile time 
    if constexpr (N == 2) { // Base case for 2x2 matrix
        return ((row + col) % 2 == 0 ? 1 : -1);
    } else if constexpr (N == 3) { // Handle 3x3 matrix
        return ((row + col) % 2 == 0 ? 1 : -1) * minor(matrix, row, col);
    } else if constexpr (N == 4) { // Handle 4x4 matrix
        return ((row + col) % 2 == 0 ? 1 : -1) * minor(matrix, row, col);
    }
}

template <std::size_t N>
double minor(const xform::Matrix<N>& matrix, size_t delete_row, size_t delete_column) {
    if constexpr (N == 2) { // Base case for 2x2 matrix
        return matrix.get(1, 1);  // The remaining element after excluding the row and column
    } else if constexpr (N == 3) { // Handle 3x3 matrix
        xform::Matrix<2> sub = submatrix(matrix, delete_row, delete_column);
        return determinant(sub);
    } else if constexpr (N == 4) { // Handle 4x4 matrix
        xform::Matrix<3> sub = submatrix(matrix, delete_row, delete_column);
        return determinant(sub);
    }
}

template <std::size_t N> 
bool is_invertable(const xform::Matrix<N>& matrix) { 
    return !(determinant(matrix) == 0);
}


#endif

