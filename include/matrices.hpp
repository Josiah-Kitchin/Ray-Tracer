#ifndef MATRICES_HPP
#define MATRICES_HPP

#include <vector> 
#include <initializer_list> 
#include <iostream> 
#include "tuples.hpp"


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

Matrix transpose(const Matrix&); 
Matrix identity(); 

Matrix submatrix(const Matrix&, std::size_t, std::size_t); 
double minor(const Matrix&, std::size_t, std::size_t); 
double cofactor(const Matrix&, std::size_t, std::size_t); 

double determinant(const Matrix&); 

bool is_invertable(const Matrix&); 
Matrix inverse(const Matrix&);

Matrix translation(double, double, double); 
Matrix scaling(double, double, double); 
Matrix rotation_x(double); 
Matrix rotation_y(double); 
Matrix rotation_z(double); 
Matrix shearing(double, double, double, double, double, double);

Point operator*(const Matrix&, const Point&);
Point operator*(const Point&, const Matrix&);
Vec operator*(const Matrix&, const Vec&); 
Vec operator*(const Vec&, const Matrix&);
#endif