#include "plane.hpp"

Plane::Plane() :
    ShadedObject(){
}

Plane::Plane(double lambert, point3D location, Color color, point3D normal) :
    ShadedObject(lambert, location, color),
    _normal{normal}
{
}

point3D Plane::normal(){
    return _normal;
}

bool Plane::intersects(const point3D start, const point3D direction, point3D &intersection, point3D &normal){

    //detect if the ray passes through the plane
    point3D start2 = start;
    point3D dir2 = direction;
    double mag = _normal.dot(dir2);
    if(mag > 0.0000001){
        point3D distance = _center - start2;
        double length = distance.dot(_normal)/mag;
        intersection = start2 + dir2 * length;
        normal = _normal.norm() * -1;
        return length >= 0;
    }
    return false;
}
