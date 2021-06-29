#ifndef IMAGERENDERRUNNABLE_H
#define IMAGERENDERRUNNABLE_H

#include <QObject>
#include <QString>
#include <QRunnable>

class ImageRenderRunnable : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit ImageRenderRunnable(const QString &id,
                                 const int thread_count,
                                 QObject *parent = nullptr);

    void run() override;

signals:
    void done(QImage image);

private:
    QString id_;
    int thread_count_{4};

};

#endif // IMAGERENDERRUNNABLE_H
