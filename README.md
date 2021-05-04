# QRayTracing

![three_spheres](/scenes/three_spheres.png)

A multithreaded, ray tracing rendering application in Qt


## How to build

You can compile this program on linux with CMake

## Defining Scenes

Scenes to be ray-traced can be defined in json to be parsed by the applicaiton. All scense should have at least one:
- Light
- Object

And exactly one:
- Camera
