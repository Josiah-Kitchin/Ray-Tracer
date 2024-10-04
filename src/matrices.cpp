

/*The matrix class holds n x n elements. It can either be initialized by giving the size for a blank matrix
  or by using initalizer lists*/

#include "matrices.hpp"
#include "utils.hpp"
#include <cassert> 
#include <cmath> 

using std::vector; 
using std::initializer_list; 
using std::size_t; 

Matrix::Matrix(int size) : size(size) {
    for (int i = 0; i < size; i++) { 
        matrix_data.push_back(vector<double>(size, 0));
    }
}   

Matrix::Matrix(initializer_list<initializer_list<double>> matrix_list) {
    size_t rows = matrix_list.size(); 
    size_t columns = matrix_list.begin()->size();  
    size = rows; 

    matrix_data.resize(rows, vector<double>(columns)); 

    int current_row = 0; 

    for (const auto& row_list : matrix_list) { 
        assert(row_list.size() == columns);
        std::copy(row_list.begin(), row_list.end(), matrix_data.at(current_row).begin());
        current_row++; 
    }
}
    
bool operator==(const Matrix& left, const Matrix& right) { 
    assert(left.size == right.size);

    for (size_t row = 0; row < left.size; row++) { 
        for (size_t col = 0; col < left.size; col++) { 
            if (!compare_doubles(left.get(row, col), right.get(row, col))) { 
                return false; 
            }
        }
    }
    return true; 
}

bool operator!=(const Matrix& left, const Matrix& right) { 
    return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) { 
    //for testing purposes 
    out << '\n';
    for (size_t row = 0; row < matrix.size; row++) { 
        for (size_t col = 0; col < matrix.size; col++) { 
            out << matrix.get(row, col) << " "; 
        }
        out << '\n';
    }
    return out; 
}

double Matrix::get(double row, double col) const { 
    return matrix_data.at(row).at(col); 
}

double& Matrix::set(double row, double col) { 
    return matrix_data.at(row).at(col); 
}

Matrix transpose(const Matrix& matrix) { 
    //returns a matrix with flipped rows and columns of the given matrix
    Matrix result(matrix.size); 
    for (size_t row = 0; row < matrix.size; row++) { 
        for (size_t col = 0; col < matrix.size; col++) { 
            result.set(row, col) = matrix.get(col, row); 
        }
    }
    return result; 
}

Matrix identity() { 
    //returns a 4x4 idenity_matrix. Returns the originial matrix when 
    //mulitiplied by the identity matrix
    return Matrix{{1, 0, 0, 0}, 
                  {0, 1, 0, 0},
                  {0, 0, 1, 0}, 
                  {0, 0, 0, 1} };
}

Matrix operator*(const Matrix& left, const Matrix& right) { 
    //Only works for 4x4 matrices 
    assert(left.size == 4 && right.size == 4); 
    
    Matrix result(4); 
    for (int row = 0; row < 4; row++) { 
        for (int col = 0; col < 4; col++) { 
            result.set(row, col) = left.get(row, 0) * right.get(0, col) + 
                                  left.get(row, 1) * right.get(1, col) + 
                                  left.get(row, 2) * right.get(2, col) + 
                                  left.get(row, 3) * right.get(3, col); 
        }
    }
    return result; 
}


Matrix submatrix(const Matrix& matrix, size_t delete_row, size_t delete_col) { 
    //Returns a matrix similar to the given matrix but has a given row and col subtracted. For example, 
    // a 4x4 matrix returns a 3x3 matrix. 
    
    Matrix result(matrix.size - 1);
    size_t matrix_row = 0, result_row = 0;

    while (result_row < result.size) {  
        size_t matrix_col = 0, result_col = 0; 
        if (result_row == delete_row) { 
            matrix_row++; 
        }
        while (result_col < result.size) { 
            if (result_col == delete_col) { 
                matrix_col++; 
            }
            result.set(result_row, result_col) = matrix.get(matrix_row, matrix_col); 
            matrix_col++; 
            result_col++; 
        }
        matrix_row++; 
        result_row++; 
    }
    return result; 
}

double minor(const Matrix& matrix, size_t delete_row, size_t delete_column) { 
    //Takes the determinant of the sub matrix
    //determinant is recursive and will continue until it reaches a 2x2 matrix

    Matrix result_submatrix = submatrix(matrix, delete_row, delete_column); 
    return determinant(result_submatrix); 
}

double cofactor(const Matrix& matrix, size_t delete_row, size_t delete_column) { 
    //negates the minor if row+col is odd
    double result_minor = minor(matrix, delete_row, delete_column); 
    if ((delete_row + delete_column) % 2 != 0) { 
        return -result_minor; 
    } 
    return result_minor; 

}

double determinant(const Matrix& matrix) { 
    //Finds the determinant in any sized matrix 
    double det = 0; 

    if (matrix.size == 2){  //base case
        det = matrix.get(0, 0) * matrix.get(1, 1) - 
              matrix.get(0, 1) * matrix.get(1, 0); 

    } else { 
        for (size_t col = 0; col < matrix.size; col++) { 
            //get the element value, then recursivly get the determinant (via
            //the cofactor) and add that to the result determinant 
            det = det + matrix.get(0, col) * cofactor(matrix, 0, col);
        }
    } 
    return det; 
}

bool is_invertable(const Matrix& matrix) { 
    return !(determinant(matrix) == 0);
}

Matrix inverse(const Matrix& matrix) { 
    assert(is_invertable(matrix)); 

    Matrix result_matrix(matrix.size);
    for (size_t row = 0; row < matrix.size; row++) { 
        for (size_t col = 0; col < matrix.size; col++) { 
            //column row accomplishes the transpose operation 
            result_matrix.set(col, row) = cofactor(matrix, row, col) / determinant(matrix); 
        }
    }
    return result_matrix; 
}

Matrix translation(double x, double y, double z) { 
    //the translation matrix is meant to be mulitpled with a point to return a point translated 
    //in the direction of x y and z (point.x += x, point.y += y, point.z += z)
    return Matrix{{1, 0, 0, x},
                  {0, 1, 0, y}, 
                  {0, 0, 1, z}, 
                  {0, 0, 0, 1}}; 
}

Matrix scaling(double x, double y, double z) { 
    //Scales a point when scaling is multiplied by a point. 
    return Matrix{{x, 0, 0, 0}, 
                  {0, y, 0, 0}, 
                  {0, 0, z, 0},
                  {0, 0, 0, 1}};
}

Matrix rotation_x(double radians) { 
    //Rotates the point along the x-axis
    return Matrix{{1, 0, 0, 0}, 
                  {0, std::cos(radians), -std::sin(radians), 0},
                  {0, std::sin(radians), std::cos(radians), 0}, 
                  {0, 0, 0, 1}};

}

Matrix rotation_y(double radians) { 
    return Matrix{{std::cos(radians), 0, std::sin(radians), 0}, 
                  {0, 1, 0, 0}, 
                  {-std::sin(radians), 0, std::cos(radians), 0},
                  {0, 0, 0, 1}};
}

Matrix rotation_z(double radians) { 
    return Matrix{{std::cos(radians), -std::sin(radians), 0, 0},
                  {std::sin(radians), std::cos(radians), 0, 0},
                  {0, 0, 1, 0}, 
                  {0, 0, 0, 1}};
}

Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) {
    //Slans the point. The parameters are the values in proportion to each other. For example, 
    //x_y is the proportoin of change of x to y. 
    return Matrix{{1, x_y, x_z, 0}, 
                  {y_x, 1, y_z, 0},
                  {z_x, z_y, 1, 0},
                  {0, 0, 0, 1}};
}

//Point and Vec interaction 

Point operator*(const Matrix& matrix, const Point& point) { 
    assert(matrix.size == 4);

    double x_new = matrix.get(0, 0) * point.x + matrix.get(0, 1) * point.y + matrix.get(0,2) * point.z + matrix.get(0,3);
    double y_new = matrix.get(1, 0) * point.x + matrix.get(1, 1) * point.y + matrix.get(1, 2) * point.z + matrix.get(1, 3);
    double z_new = matrix.get(2, 0) * point.x + matrix.get(2, 1) * point.y + matrix.get(2, 2) * point.z + matrix.get(2, 3);

    return Point(x_new, y_new, z_new);
}

Point operator*(const Point& point, const Matrix& matrix) { 
    return matrix * point; 
}

Vec operator*(const Matrix& matrix, const Vec& vec) { 
    assert(matrix.size == 4);

    double x_new = matrix.get(0, 0) * vec.x + matrix.get(0, 1) * vec.y + matrix.get(0,2)  * vec.z; 
    double y_new = matrix.get(1, 0) * vec.x + matrix.get(1, 1) * vec.y + matrix.get(1, 2) * vec.z;
    double z_new = matrix.get(2, 0) * vec.x + matrix.get(2, 1) * vec.y + matrix.get(2, 2) * vec.z;

    return Vec(x_new, y_new, z_new);
}

Vec operator*(const Vec& vec, const Matrix& matrix) { 
    return matrix * vec; 
}








 
