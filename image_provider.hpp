#ifndef IMAGE_PROVIDER_HPP
#define IMAGE_PROVIDER_HPP

#include <QImage>
#include <QQuickImageProvider>
#include <QString>
#include <QObject>

class image_provider :
        public QObject,
        public QQuickImageProvider
{
    Q_OBJECT

public:

    image_provider(QObject* parent=0);

    ~image_provider();

    QImage requestImage(const QString & id,
                        QSize * size,
                        const QSize &requestedSize) override;

public slots:
    void saveImage(QString filename);

private:
    QString scene_filename_;
    QImage scene_image_;
};

#endif // IMAGE_PROVIDER_HPP
