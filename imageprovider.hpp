#ifndef IMAGE_PROVIDER_HPP
#define IMAGE_PROVIDER_HPP

#include <QImage>
#include <QThreadPool>
#include <QQuickImageProvider>
#include <QString>
#include <QObject>

class ImageProvider :
        public QObject,
        public QQuickAsyncImageProvider
{
    Q_OBJECT

public:
    ImageProvider(QObject* parent=0);

    ~ImageProvider();

    QQuickImageResponse * requestImageResponse(const QString & id,
                                               const QSize &requestedSize) override;

public slots:
    void cacheImage(QImage image);
    void saveImage();
    void saveImage(QString filename);

private:
    QThreadPool pool_;
    QString scene_filename_;
    QImage scene_image_;
};

#endif // IMAGE_PROVIDER_HPP
