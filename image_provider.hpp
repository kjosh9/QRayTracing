#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

#include <QImage>
#include <QQuickImageProvider>
#include <QString>

class image_provider : public QQuickImageProvider
{
public:
    explicit image_provider();
    ~image_provider();
    QImage requestImage(const QString & /*id*/,
                        QSize * size,
                        const QSize &requestedSize) override;

private:
    QImage scene_image_;
};

#endif // IMAGE_PROVIDER_H
