#include <QGuiApplication>
#include <QtQuick>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "Controller/EvDispatcher.h"
#include "Common/EvVideoCapture.h"
#include "View/EvVideoCaptureView.h"

#include "opencv2/opencv.hpp"

#define SAFE_RELEASE(x) { if(x != nullptr) delete x; x = nullptr; }
int main(int argc, char *argv[])
{
    EvDispatcher* gEvDispatcher = new EvDispatcher();
    EvVideoCapture* gEvVideoCapture = new EvVideoCapture();
    EvVideoCaptureView* gEvVideoCaptureView = new EvVideoCaptureView();

    gEvVideoCapture->registEvVideoCaptureView(gEvVideoCaptureView);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickView viewer;

    viewer.engine()->addImageProvider("img",gEvVideoCapture->getEvShowFrame());
    viewer.rootContext()->setContextProperty("dispatcher", gEvDispatcher);
   // viewer.rootContext()->setContextProperty("EvVideoCapture", gEvVideoCapture);
    viewer.rootContext()->setContextProperty("EvVideoCaptureView", gEvVideoCaptureView);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    viewer.setSource(url);
    viewer.show();

    //gEvVideoCapture->slotVideoCaptureProcess();
    gEvVideoCapture->startVideoCaptureProcess();

    return app.exec();
}
