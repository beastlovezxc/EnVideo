#include "EvVideoCapture.h"
#include <QDebug>
#include <QFileInfo>
EvVideoCapture::EvVideoCapture()
{
    m_pEvShowFrame = new EvShowFrame();
    m_bCameraOn = false;
    m_pVideoCapture = VideoCapture("/Users/Bean/WorkSpace/1.mp4");
    this->moveToThread(&mWorkThread);
    connect(&mWorkThread, SIGNAL(started()), this, SLOT(slotVideoCaptureProcess()), Qt::QueuedConnection);
}

EvVideoCapture::~EvVideoCapture()
{
    mWorkThread.quit();
}

void EvVideoCapture::startVideoCaptureProcess()
{
    mWorkThread.start();
}

void EvVideoCapture::registEvVideoCaptureView(EvVideoCaptureView *videoCaptureView)
{
    m_pEvVideoCaptureView = videoCaptureView;
    connect(this, SIGNAL(sigFrame()), m_pEvVideoCaptureView, SLOT(setFrame()), Qt::QueuedConnection);
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

void EvVideoCapture::slotVideoCaptureProcess()
{
    QFileInfo file("/Users/Bean/WorkSpace/1.mp4");
    if(file.exists() == false) {
        qDebug() << "error";
        return ;
    }
    qDebug() << "Correct";

    int count = 0;
    while(1) {
        m_pVideoCapture >> m_pFrame;
        if(m_pFrame.empty())
            break;
        qDebug() << "count is " << ++count;
        m_pEvShowFrame->setFrame(m_pFrame);
        waitKey(30);
        emit sigFrame();
    }
}
