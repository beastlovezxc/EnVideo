#include "EvShowFrame.h"
#include <QDebug>
EvShowFrame::EvShowFrame() :
    QQuickImageProvider(QQuickImageProvider::Image)
{
}

EvShowFrame::~EvShowFrame()
{

}

QImage EvShowFrame::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return img;
}

void EvShowFrame::setFrame(Mat frame)
{
    qDebug() << "Get Image ";
    m_pFrame = frame;
    uchar *imgData = m_pFrame.data;
    img = QImage(imgData, m_pFrame.cols, m_pFrame.rows, QImage::Format_RGB888);
        //imshow("读取视频", frame);
}
