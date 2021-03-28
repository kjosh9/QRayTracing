#include "scene.hpp"
#include <limits>

#include "parse.hpp"

Scene::Scene(QString filename):
    camera_(Camera()),
    lights_({}),
    objects_({})
{
    parser::parse(filename,
                  camera_,
                  lights_,
                  objects_);

    focalPoint_ = camera_.normal() * (-1 * camera_.focus());
}

Scene::~Scene()
{
}

Camera Scene::GetCamera()
{
    return camera_;
}

QColor Scene::GetImagePlane()
{
    return imagePlane_;
}

point3D Scene::GetFocalPoint()
{
    return focalPoint_;
}

std::vector<Light *> Scene::GetLights()
{
    return lights_;
}

std::vector<ShadedObject*> Scene::GetObjects()
{
    return objects_;
}
