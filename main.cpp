#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QObject>
#include "gui/renderer.hpp"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    app.setOrganizationDomain("Josh Labs");
    app.setApplicationName("kjosh9");
    QQuickView * view = new QQuickView;
    QQmlEngine * engine = view->engine();
    engine->addImageProvider(QLatin1String("rendered_image"), new renderer);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view->setSource(url);
    view->show();
    return app.exec();
}
