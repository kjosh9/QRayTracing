#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QPair>
#include "point3d.hpp"

class Camera {

public:
    Camera();

    Camera(point3D center, point3D normal, int focus, QPair<int, int> size, QPair<double, double> resolution);

    void setSize(int width, int height);

    void setResolution(double first, double second);

    void setCenter(point3D center);

    void setNormal(point3D normal);

    void setCenter(double x, double y, double z);

    void setFocus(int focus);

    QPair<int, int> size();

    point3D center();

    point3D normal();

    int focus();

    QPair<double, double> resolution();

private:
    point3D _center;
    point3D _normal;
    int _focus;
    QPair<int, int> _size;
    QPair<double, double> _resolution;
};

#endif
