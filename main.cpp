#include <QGuiApplication>
#include <QtQuick>
#include <QQuickView>
#include <QQmlContext>

#include "Controller/EvDispatcher.h"

#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickView viewer;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    viewer.setSource(url);
    viewer.show();

    return app.exec();
}
