#include <QString>
#include <QDebug>
#include <QVector>
#include <QPainter>
#include <QImage>
#include <exception>
#include <stdlib.h>
#include "image_provider.hpp"
#include "core/sphere.hpp"
#include "core/scene.hpp"
#include "core/camera.hpp"
#include "core/light.hpp"
#include "core/renderer.hpp"
#include "core/point3d.hpp"
#include "parse.hpp"
#include <vector>

image_provider::image_provider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

image_provider::~image_provider()
{
}

QImage image_provider::requestImage(const QString &id,
                                    QSize * /*size*/,
                                    const QSize & /*requestedSize*/)
{
    QString scene_file = id;
    scene_file.replace("file://", "");

    Renderer new_renderer = Renderer();
    std::vector<Light*> lights = {};
    std::vector<ShadedObject*> objects = {};
    Camera camera = Camera();

    parser::parse(scene_file.toStdString(),
                  camera,
                  lights,
                  objects);

    Scene new_scene = Scene(camera, lights, objects);
    std::vector<point3D> pixMatrix = new_renderer.RenderOnCpu(new_scene);

    //loop through the pixMatrix to create the image
    QImage new_image(new_scene.GetCamera().size().first,
                 new_scene.GetCamera().size().second,
                 QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&new_image);
    painter.fillRect(new_image.rect(), Qt::black);
    int i = 0;
    for(point3D & pixel: pixMatrix){
        QColor newColor;
        newColor.setRgb(pixel.x(), pixel.y(), pixel.z());
        new_image.setPixel((i / new_scene.GetCamera().size().first),
                       (i % new_scene.GetCamera().size().first),
                       newColor.rgb());
        i++;
    }

    return new_image;
}
