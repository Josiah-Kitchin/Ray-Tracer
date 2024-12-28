
# Material Class Documentation 

The `Material` class contains the following attributes:

- **Color**: The base color of the material (represented in RGB as the Color object).
- **Ambient**: The ambient reflectivity factor. Lights up an object uniformally 
- **Diffuse**: The diffuse reflectivity factor. Depends on the angle of the object relative to light source. Can give matte appearance  
- **Specular**: The specular reflectivity factor. Creates sharp highlights on shiny surfaces, depending on angle and shininess
- **Shininess**: The shininess factor for surface highlights.

Material attributes can be set with 
```c++
Material mat;
mat
    .set_color(Color(1, 1, 1))
    .set_ambient(1)
    .set_diffuse(1)
    .set_specular(1)
    .set_shininess(1);
```
Default values are 0.3


The `Material` class is stored in a Hittable subclass (spheres, etc)
They can be stored in the hittable object by
```c++
Material mat
    .set_diffuse(1)
Sphere sphere;
sphere.set_material(mat)

```
or can be directly changed by the object by 
```c++
Sphere sphere; 
sphere
    .set_ambient(1)
    .set_color(Color(1, 1, 1));

```
