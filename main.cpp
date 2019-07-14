#include <QGuiApplication>
#include <QtQuick>
#include <QQuickView>
#include <QQmlContext>

#include "Controller/EvDispatcher.h"

#include "opencv2/opencv.hpp"

int main(int argc, char *argv[])
{
    EvDispatcher* gEvDispatcher = new EvDispatcher();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickView viewer;

    viewer.rootContext()->setContextProperty("dispatcher", gEvDispatcher);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    viewer.setSource(url);
    viewer.show();

    return app.exec();
}
