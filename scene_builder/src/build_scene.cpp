

#include <nlohmann/json.hpp>
#include "scene/scene.hpp"
#include <string> 
#include <fstream> 

using namespace nlohmann; 

static scene::Camera build_camera(const json& camera_data)
{
    scene::Camera camera;

    int horizontal_pixels = camera_data.value("horizontal_pixels", 800);
    int vertical_pixels = camera_data.value("vertical_pixels", 600);
    double field_of_view = camera_data.value("field_of_view", M_PI / 3);

    camera.set_horizontal_pixels(horizontal_pixels)
          .set_vertical_pixels(vertical_pixels)
          .set_field_of_view(field_of_view);

    if (camera_data.contains("view_transform")) 
    {
        const json& vt = camera_data["view_transform"];
        geo::Point from(vt["from"][0], vt["from"][1], vt["from"][2]);
        geo::Point to(vt["to"][0], vt["to"][1], vt["to"][2]);
        geo::Vec up(vt["up"][0], vt["up"][1], vt["up"][2]);
        camera.transform(xform::view_transform(from, to, up));
    }
    return camera;
}

static xform::Matrix<4> build_transformation(const json& transformations_data)
{
    xform::Matrix<4> transformation = xform::identity(); 
    for (const json& transform_data : transformations_data)
    {
        const std::string& type = transform_data["type"];
        if (type == "translation")
        {
            double x = transform_data["x"];
            double y = transform_data["y"];
            double z = transform_data["z"];
            transformation = transformation * xform::translation(x, y, z);
        }
        if (type == "scaling")
        {
            double x = transform_data["x"];
            double y = transform_data["y"];
            double z = transform_data["z"];
            transformation = transformation * xform::scaling(x, y, z);
        }
        if (type == "rotation_x")
        {
            double radians = transform_data["radians"];
            transformation = transformation * xform::rotation_x(radians);
        }
        if (type == "rotation_y")
        {
            double radians = transform_data["radians"];
            transformation = transformation * xform::rotation_y(radians);
        }
        if (type == "rotation_z")
        {
            double radians = transform_data["radians"];
            transformation = transformation * xform::rotation_z(radians);
        }
        if (type == "shearing")
        {
            double x_y = transform_data["x_y"];
            double x_z = transform_data["x_z"];
            double y_x = transform_data["y_x"];
            double y_z = transform_data["y_z"];
            double z_x = transform_data["z_x"];
            double z_y = transform_data["z_y"];
            transformation = transformation * xform::shearing(x_y, x_z, y_x, y_z, z_x, z_y);
        }
    }
    return transformation; 
}

static color::Pattern* build_pattern(const json& pattern_data)
{
    const std::string& type = pattern_data["type"];
    const json& first_color_data = pattern_data["first_color"];
    const json& second_color_data = pattern_data["second_color"];
    const color::RGB first_color(first_color_data[0], first_color_data[1], first_color_data[2]); 
    const color::RGB second_color(second_color_data[0], second_color_data[1], second_color_data[2]); 
    color::Pattern* pattern = nullptr; 
    if (type == "Checkers")
    { 
        pattern = new color::Checkers(); 
        pattern->set_first_color(first_color);
        pattern->set_second_color(second_color);
    }
    if (type == "Stripes")
    {
        pattern = new color::Stripes(); 
        pattern->set_first_color(first_color);
        pattern->set_second_color(second_color);
    }
    if (type == "Rings")
    {
        pattern = new color::Rings(); 
        pattern->set_first_color(first_color);
        pattern->set_second_color(second_color);
    }
    if (type == "Gradient")
    {
        pattern = new color::Gradient(); 
        pattern->set_first_color(first_color);
        pattern->set_second_color(second_color);
    }
    if (pattern_data.contains("transformations"))
    {
        xform::Matrix<4> transformation = build_transformation(pattern_data["transformations"]);
        pattern->transform(transformation);
    }
    return pattern; 
}

static scene::Material build_material(const json& material_data)
{
    scene::Material mat; 
    if (material_data.contains("ambient"))
        mat.set_ambient(material_data["ambient"]);

    if (material_data.contains("diffuse"))
        mat.set_diffuse(material_data["diffuse"]);

    if (material_data.contains("specular"))
        mat.set_specular(material_data["specular"]);

    if (material_data.contains("shininess"))
        mat.set_shininess(material_data["shininess"]);

    if (material_data.contains("transparency"))
        mat.set_transparency(material_data["transparency"]);

    if (material_data.contains("refractive_index"))
        mat.set_refractive_index(material_data["refractive_index"]);

    if (material_data.contains("color"))
    {
        color::RGB color(material_data["color"][0], material_data["color"][1], material_data["color"][2]);
        mat.set_color(color);
    }

    if (material_data.contains("pattern"))
    {
        color::Pattern* pattern = build_pattern(material_data["pattern"]);
        mat.set_pattern(pattern);
    }
    return mat; 
}


static scene::World build_world(const json& world_data)
{
    scene::World world; 
    for (const json& object_data : world_data["objects"])
    {
        scene::Hittable* object = nullptr; 
        const std::string& type = object_data["type"];
        if (type == "Sphere")  
            object = new scene::Sphere(); 
        if (type == "Cube") 
            object = new scene::Cube(); 
        if (type == "Plane")  
            object = new scene::Plane(); 
                  
        if (object_data.contains("material"))
        {
            scene::Material mat = build_material(object_data["material"]);
            object->set_material(mat);
        }
        if (object_data.contains("transformations"))
        {
            xform::Matrix<4> transformation = build_transformation(object_data["transformations"]);
            object->transform(transformation);
        }
        world.add_object(object);
    }

    for (const json& light_data: world_data["lights"])
    {
        scene::Light light; 
        color::RGB intensity(light_data["intensity"][0], light_data["intensity"][1], light_data["intensity"][2]);
        light.set_intensity(intensity);
        geo::Point position(light_data["position"][0], light_data["position"][1], light_data["position"][2]);
        light.set_position(position);
        world.add_light(light);
    }

    world.set_reflection_limit(world_data["reflection_limit"]);
    return world; 
}


image::Canvas build_scene(const std::string& scene_json_file)
{
    std::ifstream file(scene_json_file);
    json data; 
    file >> data; 
    const json& scene = data["scene"];
    scene::Camera cam = build_camera(scene["camera"]);
    scene::World world = build_world(scene["world"]);
    image::Canvas canvas = cam.render(world);

    return canvas; 
}




