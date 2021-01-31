#ifndef PLANE_HPP
#define PLANE_HPP

#include "shadedObject.hpp"

class Plane: public ShadedObject{

public:
    Plane();

    Plane(double lambert, point3D location, QColor color, point3D normal);

    point3D normal();

    bool intersects(const point3D start, const point3D direction, point3D &intersection, point3D &normal);

private:
    point3D _normal;
};

#endif
