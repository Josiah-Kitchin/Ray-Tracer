
# World Class Documentation 

The `World` class holds the lights and hittable objects of the scene 
There should only be one instance of the `World` class 

The `World` class holds a vector of lights and pointers to hittable objects, which can be set by  
```c++
Sphere sphere; 
Light light; 
World world;
    world
        .set_lights({light})
        .set_objects({&sphere});

```
Or added one by one 
```c++
Sphere sphere; 
Light light; 
World world;
    world
        .add_light(light)
        .add_object(&sphere);

```

The world class will then be rendered by the Camera in Camera.render(world) (See [Camera](camera.md))
