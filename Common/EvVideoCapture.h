#ifndef EVVIDEOCAPTURE_H
#define EVVIDEOCAPTURE_H

#include <QObject>
#include <QThread>

#include "EvShowFrame.h"
#include "View/EvVideoCaptureView.h"
#include "opencv2/opencv.hpp"

using namespace cv;
class EvVideoCapture : public QObject {
    Q_OBJECT
public:
    EvVideoCapture();
    QThread mWorkThread;
    void startVideoCaptureProcess();
    void registEvVideoCaptureView(EvVideoCaptureView *videoCaptureView);
    EvShowFrame* getEvShowFrame() { return m_pEvShowFrame;}

private slots:
    void slotVideoCaptureProcess();

signals:
    void sigImage();

private:
    EvShowFrame* m_pEvShowFrame;
    VideoCapture m_pVideoCapture;
    Mat          m_pFrame;

    EvVideoCaptureView* m_pEvVideoCaptureView;
};

#endif // EVVIDEOCAPTURE_H
