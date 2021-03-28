#include "point3d.hpp"
#include <stdlib.h>
#include <cmath>

point3D::point3D():
    _xPos{0},
    _yPos{0},
    _zPos{0}
{
}

point3D::point3D(double x, double y, double z):
    _xPos{x},
    _yPos{y},
    _zPos{z}
{
}

point3D::point3D(const point3D& rhs){
    _xPos = rhs._xPos;
    _yPos = rhs._yPos;
    _zPos = rhs._zPos;
}

point3D::~point3D() {

}

bool point3D::operator==(const point3D& rhs) {
    return rhs._xPos == _xPos &&
            rhs._yPos == _yPos &&
            rhs._zPos == _zPos;
}

point3D& point3D::operator=(const point3D& rhs) {
    if(this == &rhs){
        return *this;
    }

    _xPos = rhs._xPos;
    _yPos = rhs._yPos;
    _zPos = rhs._zPos;
    return *this;
}

double point3D::x() {
    return _xPos;
}

double point3D::y() {
    return _yPos;
}

double point3D::z() {
    return _zPos;
}

void point3D::set_x(double x)
{
    _xPos = x;
}

void point3D::set_y(double y)
{
    _yPos = y;
}

void point3D::set_z(double z)
{
    _zPos = z;
}

point3D point3D::operator-(const point3D &rhs) {
    return point3D(_xPos - rhs._xPos, _yPos - rhs._yPos, _zPos - rhs._zPos);
}

point3D point3D::operator+(const point3D &rhs) {
    return point3D(_xPos + rhs._xPos, _yPos + rhs._yPos, _zPos + rhs._zPos);
}

point3D point3D::operator*(const point3D &rhs) {
    return point3D(_xPos * rhs._xPos, _yPos * rhs._yPos, _zPos * rhs._zPos);
}

double point3D::dot(const point3D &rhs) {
    return _xPos*rhs._xPos + _yPos*rhs._yPos + _zPos*rhs._zPos;
}

point3D point3D::norm() {
    double mag = sqrt(_xPos*_xPos + _yPos*_yPos + _zPos*_zPos);
    return point3D(_xPos/mag, _yPos/mag, _zPos/mag);
}

point3D point3D::operator *(double scalar) {
    return point3D(_xPos*scalar, _yPos*scalar, _zPos*scalar);
}
