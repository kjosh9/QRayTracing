#ifndef SCENE_HPP
#define SCENE_HPP

#include <QVector>
#include <QPainter>
#include <QGenericMatrix>

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
    QVector<Light *> GetLights();
    QVector<ShadedObject*> GetObjects();

private:
    Camera camera_;
    QVector<Light*> lights_;
    QVector<ShadedObject*> objects_;
    QColor imagePlane_;
    point3D focalPoint_;
};

#endif
