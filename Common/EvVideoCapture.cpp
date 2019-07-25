#include "EvVideoCapture.h"
#include <QDebug>
#include <QFileInfo>
EvVideoCapture::EvVideoCapture():
    m_pEvShowFrame(nullptr),
    m_bCameraOn(false),
    m_strVideoPath("")
{
    m_pEvShowFrame = new EvShowFrame();
    this->moveToThread(&mWorkThread);
    connect(&mWorkThread, SIGNAL(started()), this, SLOT(slotVideoCaptureProcess()), Qt::QueuedConnection);
}

EvVideoCapture::~EvVideoCapture()
{
    mWorkThread.quit();
}

void EvVideoCapture::startVideoCaptureProcess()
{
    if(!m_bCameraOn) {
        m_pVideoCapture = VideoCapture(m_strVideoPath.toStdString());
    } else {
        m_pVideoCapture = VideoCapture(0);
    }
    mWorkThread.start();
}

void EvVideoCapture::registEvVideoCaptureView(EvVideoCaptureView *videoCaptureView)
{
    m_pEvVideoCaptureView = videoCaptureView;
    connect(this, SIGNAL(sigFrame()), m_pEvVideoCaptureView, SLOT(setFrame()), Qt::DirectConnection);
}

void EvVideoCapture::restartProcess(bool isCameraOn)
{
    if(isCameraOn == m_bCameraOn)
        return;
    m_bCameraOn = isCameraOn;
    if(isCameraOn) {
        mWorkThread.quit();
        m_pVideoCapture = VideoCapture(0);
        mWorkThread.start();
    } else {
        mWorkThread.quit();
        m_pVideoCapture = VideoCapture("/Users/Bean/WorkSpace/1.mp4");
        mWorkThread.start();
    }
}

void EvVideoCapture::closeProcess()
{
    m_pVideoCapture.release();
    mWorkThread.quit();
}

void EvVideoCapture::setVideoPath(QString videoPath)
{
    m_strVideoPath = videoPath;
}

void EvVideoCapture::setCameraOn(bool isCameraOn)
{
    m_bCameraOn = isCameraOn;
}

void EvVideoCapture::slotVideoCaptureProcess()
{
    int count = 0;
    while(1) {
        if(!m_pVideoCapture.isOpened()) {
            break;
        }
        m_pVideoCapture >> m_pFrame;
        if(m_pFrame.empty())
            break;
        qDebug() << "count is " << ++count;
        m_pEvShowFrame->setFrame(m_pFrame);
        waitKey(30);
        emit sigFrame();
    }
}
