#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <QImage>
#include <QQuickImageProvider>
#include <QString>
#include "camera.hpp"

class renderer : public QQuickImageProvider
{
public:
    explicit renderer();
    ~renderer();
    QImage requestImage(const QString &id,
                        QSize *size,
                        const QSize &requestedSize) override;

private:
    Camera * _camera;
    QImage _sceneImage;
};

#endif // RENDERER_HPP
