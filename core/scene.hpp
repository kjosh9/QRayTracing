#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "camera.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "light.hpp"

class Scene{

public:
    Scene(QString filename);
    ~Scene();

    Camera GetCamera();
    QColor GetImagePlane();
    point3D GetFocalPoint();
    std::vector<Light *> GetLights();
    std::vector<ShadedObject*> GetObjects();

private:
    Camera camera_;
    std::vector<Light*> lights_;
    std::vector<ShadedObject*> objects_;
    QColor imagePlane_;
    point3D focalPoint_;
};

#endif
