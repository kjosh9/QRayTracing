#include <QString>
#include <QDebug>
#include <QVector>
#include <QPainter>
#include <QImage>
#include <exception>
#include <stdlib.h>
#include <vector>

#include "image_provider.hpp"
#include "core/sphere.hpp"
#include "core/scene.hpp"
#include "core/camera.hpp"
#include "core/light.hpp"
#include "core/renderer.hpp"
#include "core/point3d.hpp"
#include "parse.hpp"


image_provider::image_provider(QObject* parent)
    : QObject(parent)
    , QQuickImageProvider(QQuickImageProvider::Image)
{
}

image_provider::~image_provider()
{
}

QImage image_provider::requestImage(const QString &id,
                                    QSize * /*size*/,
                                    const QSize & /*requestedSize*/)
{
    scene_filename_ = id;
    scene_filename_.replace("file://", "");

    Renderer new_renderer = Renderer();
    std::vector<Light*> lights = {};
    std::vector<ShadedObject*> objects = {};
    Camera camera = Camera();

    parser::parse(scene_filename_.toStdString(),
                  camera,
                  lights,
                  objects);

    Scene new_scene = Scene(camera, lights, objects);
    std::vector<point3D> pixMatrix = new_renderer.RenderOnCpu(new_scene);

    //loop through the pixMatrix to create the image
    scene_image_ = QImage(new_scene.GetCamera().size().first,
                          new_scene.GetCamera().size().second,
                          QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&scene_image_);
    painter.fillRect(scene_image_.rect(), Qt::black);
    int i = 0;
    for(point3D & pixel: pixMatrix){
        QColor newColor;
        newColor.setRgb(pixel.x(), pixel.y(), pixel.z());
        scene_image_.setPixel((i / new_scene.GetCamera().size().first),
                       (i % new_scene.GetCamera().size().first),
                       newColor.rgb());
        i++;
    }
    return scene_image_;
}

void image_provider::saveImage(QString filename) {
    filename.replace("file://", "");
    if (scene_image_.save(filename)) {
        qDebug() << "Image saved to: " + filename;
    } else {
        qDebug() << "Image save unsuccessful";
    }
}
