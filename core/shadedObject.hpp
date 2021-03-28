#ifndef SHADEDOBJECT_HPP
#define SHADEDOBJECT_HPP

#include "point3d.hpp"
#include <QColor>

//this is a base class for spheres and planes
class ShadedObject{

public:
    ShadedObject();

    ShadedObject(double lambert, point3D location, QColor color);

    double lambert();

    point3D center();

    QColor color();

    virtual bool intersects(const point3D start, const point3D direction, point3D &intersction, point3D &normal) =0;

protected:
    double _lambert;
    point3D _center;
    QColor _color;
};

#endif
