#ifndef EVSHOWFRAME_H
#define EVSHOWFRAME_H

#include <QQuickImageProvider>
#include <QImage>
#include <QSize>
#include <QColor>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/opencv.hpp"

using namespace cv;

class EvShowFrame : public QQuickImageProvider
{
public:
    EvShowFrame();
    ~EvShowFrame();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    void setFrame(Mat frame);

private:
    Mat            m_pFrame;
    QImage         img;
};

#endif // EVSHOWFRAME_H
