#include <QString>
#include <QDebug>
#include <QVector>
#include <QStringList>
#include <QPair>
#include <QImage>
#include <exception>
#include <stdlib.h>
#include "image_provider.hpp"
#include "core/sphere.hpp"
#include "core/scene.hpp"
#include "core/renderer.hpp"

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
    Scene new_scene = Scene(scene_file);
    QImage new_image = new_renderer.RenderOnCpu(new_scene);

    return new_image;
}
