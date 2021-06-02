#include "renderedimageresponse.hpp"
#include "imagerenderrunnable.hpp"

RenderedImageResponse::RenderedImageResponse(const QString &id,
                                             const QSize &requestedSize,
                                             QThreadPool *pool)
{
    Q_UNUSED(requestedSize);
    auto runnable = new ImageRenderRunnable(id);
    QObject::connect(runnable, &ImageRenderRunnable::done, this, &RenderedImageResponse::handleDone);
    pool->start(runnable);
}

QQuickTextureFactory * RenderedImageResponse::textureFactory() const
{
    return QQuickTextureFactory::textureFactoryForImage(image_);
}

void RenderedImageResponse::handleDone(QImage image)
{
    image_ = image;
    emit finished();
    emit done(image);
}
