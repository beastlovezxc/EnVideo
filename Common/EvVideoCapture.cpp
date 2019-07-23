#include "EvVideoCapture.h"
#include <QDebug>
#include <QFileInfo>
EvVideoCapture::EvVideoCapture()
{
    m_pEvShowFrame = new EvShowFrame();
   // m_pVideoCapture = new VideoCapture();
    this->moveToThread(&mWorkThread);
    connect(&mWorkThread, SIGNAL(started()), this, SLOT(slotVideoCaptureProcess()), Qt::QueuedConnection);
}

void EvVideoCapture::startVideoCaptureProcess()
{
    mWorkThread.start();
}

void EvVideoCapture::registEvVideoCaptureView(EvVideoCaptureView *videoCaptureView)
{
    m_pEvVideoCaptureView = videoCaptureView;
    connect(this, SIGNAL(sigImage()), m_pEvVideoCaptureView, SLOT(setFrame()), Qt::QueuedConnection);
}

void EvVideoCapture::slotVideoCaptureProcess()
{
    QFileInfo file("/Users/Bean/WorkSpace/1.mp4");
    if(file.exists() == false) {
        qDebug() << "error";
        return ;
    }
    m_pVideoCapture = VideoCapture("/Users/Bean/WorkSpace/1.mp4");
    qDebug() << "Correct";
   // m_pVideoCapture->open("/Users/Bean/WorkSpace/1.mp4");
   // m_pVideoCapture = new VideoCapture("/Users/Bean/WorkSpace/1.mp4");
//    if(!m_pVideoCapture->open("/Users/Bean/WorkSpace/1.mp4"))
//        qDebug() << "Error";
    int count = 0;
    while(1) {
        m_pVideoCapture >> m_pFrame;
       // (*m_pVideoCapture) >> (*m_pFrame);
        if(m_pFrame.empty())
            break;
        qDebug() << "count is " << ++count;
        m_pEvShowFrame->setFrame(m_pFrame);
        waitKey(30);
        emit sigImage();
    }
}
