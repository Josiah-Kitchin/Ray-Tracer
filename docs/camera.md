
# Camera Class Documentation 

The `Camera` class represents the view origin of the scene:

The `Camera` object sets the pixel dimensions and the field of view 
These can be set by 
```c++
Camera cam; 
cam
    .set_horizontal_pixels(5);
    .set_vertical_pixels(5);
    .set_field_of_view(5);

```
The camera can be moved around the scene by calling transform and using the view transform matrix 
See [Transformation Matrices](transformation_matrices.md) for more info 
```c++
cam.transform(view_transform(Point(0, 1.5, -5), Point(0, 1, 0), Vec(0, 1, 0)));

```

The `Camera` class renders a `World` class and returns a `Canvas`
The `Canvas` can then write the colors to the standard ouput
See [World](world.md) for the `World` class docs 
```c++
Canvas canvas = cam.render(world)
canvas.write_to_ppm()

```


The arguments are transformation matrices, which will be applied in the order called by .transform 
See [Transformation Matrices](transformation_matrices.md) for all transformation matrices

