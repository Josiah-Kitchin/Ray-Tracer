
# Hittable Class Documentation 

The `Hittable` class is an abstract class of hittable objects, e.g. spheres, cubes, etc:

`Hittable` objects hold a material, see [Material](material.md) for info 
`Hittable` objects can be transformed by calling 
```c++
scene::Sphere sphere; 
    sphere
        .transform(xform::scaling(2, 2, 2))
        .transform(xform::rotattion_x(5))

```
The arguments are transformation matrices, which will be applied in the order called by .transform 
See [Transformation Matrices](transformation_matrices.md) for all transformation matrices

