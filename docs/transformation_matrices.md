
# Transformation Matrices Documentation 

Transformation matrices are `Matrix` objects returned by transformation matrix functions:

They can transform hittable objects by calling
```c++
Sphere sphere; 
sphere
    .transform(example_matrix(2, 2, 2))
    .transform(example_matrix2(1, 1, 1));
```

The transformations will be applied in the order .transform was called 

##Matrices 
```c++
Matrix translation(double x, double y, double z); 
Matrix scaling(double x, double y, double z); 
Matrix rotation_x(double radians); 
Matrix rotation_y(double radians); 
Matrix rotation_z(double radians); 
Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);
Matrix view_transform(const Point& from, const Point& to, const Vec& up);
```





