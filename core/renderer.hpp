#ifndef RENDERER_H
#define RENDERER_H

#include "point3d.hpp"
#include "scene.hpp"

class Renderer
{
public:
    Renderer();
    std::vector<point3D> RenderOnCpu(Scene & scene, const int thread_count);


private:

    static void GetRange(int start_pix,
                         int finish_pix,
                         Scene & scene,
                         std::vector<point3D> & pixMatrix);

    static point3D GetPixel(Scene & scene,
                            const int i,
                            const int j);
};

#endif // RENDERER_H
