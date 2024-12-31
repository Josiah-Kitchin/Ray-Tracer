#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <vector> 
#include <array> 
#include <initializer_list> 
#include <iostream> 
#include "geo/tuples.hpp"

namespace xform { 

    class Matrix { 
    private: 
        std::array<double, 4> m_data; 

    public: 
        std::size_t size; 
        
        Matrix(int); 
        Matrix(const std::initializer_list<double>&); 

        double get(int, int) const;  
        void set(double, int, int); 

    };

    bool operator==(const Matrix&, const Matrix&); 
    bool operator!=(const Matrix&, const Matrix&); 
    Matrix operator*(const Matrix&, const Matrix&); 
    std::ostream& operator<<(std::ostream&, const Matrix&); 

    Matrix inverse(const Matrix&);  
    Matrix transpose(const Matrix&); 

    Matrix identity(); 

    Matrix translation(double, double, double); 
    Matrix scaling(double, double, double); 
    Matrix rotation_x(double); 
    Matrix rotation_y(double); 
    Matrix rotation_z(double); 
    Matrix shearing(double, double, double, double, double, double);
    Matrix view_transform(const geo::Point&, const geo::Point&, const geo::Vec&);

    geo::Point operator*(const Matrix&, const geo::Point&);
    geo::Point operator*(const geo::Point&, const Matrix&);
    geo::Vec operator*(const Matrix&, const geo::Vec&); 
    geo::Vec operator*(const geo::Vec&, const Matrix&);

}

double cofactor(const xform::Matrix& matrix, size_t delete_row, size_t delete_column);  
double minor(const xform::Matrix& matrix, size_t delete_row, size_t delete_column);  
double determinant(const xform::Matrix& matrix);  
xform::Matrix submatrix(const xform::Matrix& matrix, size_t delete_row, size_t delete_col);  
bool is_invertable(const xform::Matrix& matrix);  

#endif

