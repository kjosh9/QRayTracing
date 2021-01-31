#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "point3d.hpp"

class Light {

public:
    Light();

    Light(double intensity, point3D location);

    double intensity();

    point3D location();

private:
    double _intensity;
    point3D _location;
};

#endif
