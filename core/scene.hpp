#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <string>
#include "camera.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "light.hpp"

class Scene{

public:
    Scene(Camera camera, std::vector<Light*> lights, std::vector<ShadedObject*> objects);
    ~Scene();

    Camera GetCamera();
    Color GetImagePlane();
    point3D GetFocalPoint();
    std::vector<Light *> GetLights();
    std::vector<ShadedObject*> GetObjects();

private:
    Camera camera_;
    std::vector<Light*> lights_;
    std::vector<ShadedObject*> objects_;
    Color imagePlane_;
    point3D focalPoint_;
};

#endif
