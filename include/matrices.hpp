#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <vector> 
#include <initializer_list> 
#include <iostream> 
#include "tuples.hpp"

namespace xform { 

    class Matrix { 
    private: 
        std::vector<std::vector<double>> matrix_data; 

    public: 
        std::size_t size; 
        
        Matrix(int); 
        Matrix(std::initializer_list<std::initializer_list<double>>); 

        double get(double, double) const;  
        double& set(double, double); 

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
    Matrix view_transform(const Point&, const Point&, const Vec&);

    Point operator*(const Matrix&, const Point&);
    Point operator*(const Point&, const Matrix&);
    Vec operator*(const Matrix&, const Vec&); 
    Vec operator*(const Vec&, const Matrix&);

}

#endif

