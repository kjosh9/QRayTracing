#include "shadedObject.hpp"

ShadedObject::ShadedObject():
    _lambert{0},
    _center{0,0,0},
    _color{Color()}
{
}

ShadedObject::ShadedObject(double lambert, point3D location, Color color):
    _lambert{lambert},
    _center{location},
    _color{color}
{
}

double ShadedObject::lambert(){
    return _lambert;
}

point3D ShadedObject::center(){
    return _center;
}

Color ShadedObject::color(){
    return _color;
}
