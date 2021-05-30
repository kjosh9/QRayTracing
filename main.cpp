#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QObject>
#include "image_provider.hpp"

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
    
    image_provider my_image_provider;
    engine->addImageProvider(QLatin1String("rendered_image"), &my_image_provider);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view->setSource(url);

    QObject* root_item = view->rootObject();
    QObject::connect(root_item, SIGNAL(saveFile(QString)),
                     &my_image_provider, SLOT(saveImage(QString)));

    view->show();
    return app.exec();
}
