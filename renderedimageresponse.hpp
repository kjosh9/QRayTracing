#ifndef RENDEREDIMAGERESPONSE_HPP
#define RENDEREDIMAGERESPONSE_HPP

#include <QThreadPool>
#include <qquickimageprovider.h>
#include <QImage>

class RenderedImageResponse : public QQuickImageResponse
{
    Q_OBJECT
public:
    RenderedImageResponse(const QString &id, const QSize &requestedSize, QThreadPool *pool);

    QQuickTextureFactory * textureFactory() const override;

public slots:
    void handleDone(QImage image);

signals:
    void done(QImage image);

private:
    QImage image_;
};

#endif // RENDEREDIMAGERESPONSE_HPP
