#include "scene.hpp"

Scene::Scene(Camera camera,
             std::vector<Light*> lights,
             std::vector<ShadedObject*> objects):
    camera_(camera),
    lights_(lights),
    objects_(objects)
{
    focalPoint_ = camera_.normal() * (-1 * camera_.focus());
}

Scene::~Scene()
{
}

Camera Scene::GetCamera()
{
    return camera_;
}

Color Scene::GetImagePlane()
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
