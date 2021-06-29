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
    void setImage(QImage image);
    void saveImage();
    void saveImage(QString filename);
    void setThreadCount(int thread_count);

private:
    QThreadPool pool_;
    QString scene_filename_;
    QImage scene_image_;
    int thread_count_{4};
};

#endif // IMAGE_PROVIDER_HPP
