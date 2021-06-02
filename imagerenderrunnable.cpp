#include <QPainter>
#include <QColor>

#include "imagerenderrunnable.hpp"
#include "core/sphere.hpp"
#include "core/scene.hpp"
#include "core/camera.hpp"
#include "core/light.hpp"
#include "core/renderer.hpp"
#include "core/point3d.hpp"
#include "parse.hpp"

ImageRenderRunnable::ImageRenderRunnable(const QString &id, QObject *parent) : QObject(parent)
  , id_{id}
{
}

void ImageRenderRunnable::run()
{
    QString scene_filename_ = id_;
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
    QImage scene_image_ = QImage(new_scene.GetCamera().size().first,
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
    emit done(scene_image_);
}
