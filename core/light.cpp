#include "light.hpp"

Light::Light():
    _intensity{0},
    _location{0,0,0}
{
}

Light::Light(double intensity, point3D location):
    _intensity{intensity},
    _location{location}
{
}

double Light::intensity(){
    return _intensity;
}

point3D Light::location(){
    return _location;
}
