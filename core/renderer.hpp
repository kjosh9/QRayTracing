#ifndef RENDERER_H
#define RENDERER_H

#include "point3d.hpp"
#include "scene.hpp"

class Renderer
{
public:
    Renderer();
    std::vector<point3D> RenderOnCpu(Scene & scene);


private:

    static void GetRange(int start_pix,
                         int finish_pix,
                         Scene & scene,
                         std::vector<point3D> & pixMatrix);

    static point3D GetPixel(Scene & scene,
                            const int i,
                            const int j);

    int available_cpu_threads_;
};

#endif // RENDERER_H
