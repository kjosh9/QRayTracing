#include "renderedimageresponse.hpp"
#include "imagerenderrunnable.hpp"

RenderedImageResponse::RenderedImageResponse(const QString &id,
                                             const int thread_count,
                                             const QSize &requestedSize,
                                             QThreadPool *pool)
{
    Q_UNUSED(requestedSize);
    auto runnable = new ImageRenderRunnable(id, thread_count);
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
