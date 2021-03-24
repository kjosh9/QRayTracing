#ifndef SCENE_HPP
#define SCENE_HPP

#include <QVector>
#include <QImage>
#include <QPainter>
#include <QGenericMatrix>

#include "camera.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "light.hpp"

class Scene{

public:
    Scene();

    Scene(Camera * camera, 
          QVector<Light*> lights, 
          QVector<ShadedObject*> objects, 
          int threads);

    ~Scene();

    point3D getPixel(const int &i, const int &j);

    QImage renderScene();


private:
    Camera * _camera;
    QVector<Light*> _lights;
    QVector<ShadedObject*> _objects;
    QColor * imagePlane;
    point3D focalPoint;
    int _threads;
};

#endif
