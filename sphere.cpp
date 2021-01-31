#include <cmath>
#include "sphere.hpp"


Sphere::Sphere() :
    ShadedObject()
{
}

Sphere::Sphere(double lambert, point3D location, QColor color, double radius) :
    ShadedObject(lambert, location, color),
    _radius{radius}
{
}

double Sphere::radius(){
    return _radius;
}


bool Sphere::intersects(const point3D start, const point3D direction, point3D &intersection, point3D &normal){

    point3D distance = _center - start;
    double mag = distance.dot(direction);
    double distFromCenter = distance.dot(distance) - mag*mag;

    double t = sqrt(_radius*_radius - distFromCenter);

    point3D dir2 = direction;
    point3D start2 = start;
    double t0 = mag-t;
    intersection = start2 + (dir2)*t0;
    normal = (intersection - _center).norm();

    return !(mag < 0 || distFromCenter > _radius*_radius);
}

