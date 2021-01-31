#include "camera.hpp"
#include <iostream>
#include <QDebug>

Camera::Camera():
    _center{0,0,0},
    _normal{0,0,0},
    _focus{0},
    _size{0,0},
    _resolution{0,0}
{
}

Camera::Camera(point3D center, point3D normal, int focus, QPair<int, int> size, QPair<double, double> resolution):
    _center{center},
    _normal{normal},
    _focus{focus},
    _size{size},
    _resolution{resolution}
{
}

void Camera::setSize(int width, int height){
    _size.first = width;
    _size.second = height;
}

void Camera::setResolution(double first, double second){
    _resolution.first = first;
    _resolution.second = second;
}

void Camera::setCenter(point3D center){
    _center = center;
}

void Camera::setCenter(double x, double y, double z){
    _center = point3D(x,y,z);
}

void Camera::setNormal(point3D normal){
    _normal = normal;
}

void Camera::setFocus(int focus){
    _focus = focus;
}

QPair<int, int> Camera::size(){
    return _size;
}

point3D Camera::center(){
    return _center;
}

point3D Camera::normal(){
    return _normal;
}

int Camera::focus(){
    return _focus;
}

QPair<double, double> Camera::resolution(){
    return _resolution;
}
