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
    ~EvVideoCapture();
    QThread mWorkThread;
    void startVideoCaptureProcess();
    void registEvVideoCaptureView(EvVideoCaptureView *videoCaptureView);
    void restartProcess(bool isCameraOn);
    void closeProcess();
    void setVideoPath(QString videoPath);
    void setCameraOn(bool isCameraOn);
    EvShowFrame* getEvShowFrame() { return m_pEvShowFrame;}

private slots:
    void slotVideoCaptureProcess();

signals:
    void sigFrame();

private:
    EvShowFrame* m_pEvShowFrame;
    VideoCapture m_pVideoCapture;
    Mat          m_pFrame;
    bool         m_bCameraOn;

    EvVideoCaptureView* m_pEvVideoCaptureView;

    QString      m_strVideoPath;
};

#endif // EVVIDEOCAPTURE_H
