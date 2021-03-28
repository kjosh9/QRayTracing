#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <utility>
#include "point3d.hpp"

class Camera {

public:
    Camera();

    Camera(point3D center, point3D normal, int focus, std::pair<int, int> size, std::pair<double, double> resolution);

    void setSize(int width, int height);

    void setResolution(double first, double second);

    void setCenter(point3D center);

    void setNormal(point3D normal);

    void setCenter(double x, double y, double z);

    void setFocus(int focus);

    std::pair<int, int> size();

    point3D center();

    point3D normal();

    int focus();

    std::pair<double, double> resolution();

private:
    point3D _center;
    point3D _normal;
    int _focus;
    std::pair<int, int> _size;
    std::pair<double, double> _resolution;
};

#endif
