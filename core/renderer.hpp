#ifndef RENDERER_H
#define RENDERER_H

#include <QImage>
#include "scene.hpp"

class Renderer
{
public:
    Renderer();
    QImage RenderOnCpu(Scene & scene);


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
