#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QObject>
#include "gui/image_provider.hpp"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    app.setOrganizationDomain("Josh Labs");
    app.setApplicationName("QRayTracing");
    QQuickView * view = new QQuickView;
    QQmlEngine * engine = view->engine();
    QObject::connect(engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);
    engine->addImageProvider(QLatin1String("rendered_image"), new image_provider);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view->setSource(url);
    view->show();
    return app.exec();
}
